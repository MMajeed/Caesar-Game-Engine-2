#include "GraphicManager.h"

#include <boost/numeric/ublas/io.hpp>
#include <Converter.h>
#include <InfoCommunicator\ObjectManagerOutput.h>
#include <Keys.h>
#include <3DMath.h>
#include <XNAConverter.h>
#include "DX11Helper.h"
#include "Buffers.h"
#include "SpotLight.h"
#include "DirectLight.h"
#include <algorithm>

GraphicManager::GraphicManager()
{
	this->D3DStuff.pd3dDevice			= 0;
	this->D3DStuff.pImmediateContext	= 0;
	this->D3DStuff.pSwapChain			= 0;
	this->D3DStuff.pRenderTargetView	= 0;
	this->D3DStuff.pDepthStencilBuffer	= 0;
	this->D3DStuff.pDepthStencilState	= 0;
	this->D3DStuff.pDepthStencilView	= 0;
	this->D3DStuff.IsInitialized	    = false;

	this->SceneInfo.ClearColour(0) = 0.5;
	this->SceneInfo.ClearColour(1) = 0.5;
	this->SceneInfo.ClearColour(2) = 0.5;
}

void GraphicManager::Init()
{
	this->InitDevice();
}

void GraphicManager::Update(double realTime, double deltaTime)
{
}

void GraphicManager::Work()
{
	TypedefObject::ObjectVector objects = ObjectManagerOutput::GetAllObjects();

	this->RunAllCapture(objects);
	this->SetupLight(objects);
	this->SetupScene(objects);
	this->SetupConstantBuffer(objects);
	this->ClearScreen(objects);
	this->DrawObjects(objects);
	this->Present(objects);
}

void GraphicManager::Shutdown()
{

}

void GraphicManager::RunAllCapture(TypedefObject::ObjectVector& objects)
{
	for(auto iter = this->ContinuousScreenCaptures.begin();
		iter != this->ContinuousScreenCaptures.end();
		++iter)
	{
		iter->second->Snap(objects);
	}
}
void GraphicManager::SetupLight(TypedefObject::ObjectVector& objects)
{
	std::vector<cBuffer::CLightDesc> vecLightBuffer;

	for(auto iterObj = objects.begin();
		iterObj != objects.end();
		++iterObj)
	{
		auto classTypeIter = iterObj->find(Keys::Class);
		auto lightTypeIter = iterObj->find(Keys::Light::LIGHTTYPE);
		if(	   classTypeIter == iterObj->cend()  // If it has a class type
			|| GenericObj<std::string>::GetValue(classTypeIter->second) != Keys::ClassType::Light // and that class type is NOT a light
			|| lightTypeIter == iterObj->cend()) // and it dosn't have a light type
		{// then continue
			continue;
		}

		cBuffer::CLightDesc light;
		ZeroMemory(&light, sizeof(cBuffer::CLightDesc));
		if (GenericObj<std::string>::GetValue(lightTypeIter->second) == Keys::Light::LightTypes::DIRECTIONAL)
		{
			light = DirectLight::GetInstance().GetLightDesc(*iterObj);

			//if(GenericObj<bool>::GetValue(iterObj->find(Keys::HASHADOW)->second) == true)
			/*{
				DirectLight::GetInstance().GenerateShadowTexture(*iterObj, objects);

				XMFLOAT4X4 viewShadow4x4 = CHL::Convert4x4(DirectLight::GetInstance().GetViewMatrix(*iterObj));
				XMFLOAT4X4 presShadow4x4 = CHL::Convert4x4(DirectLight::GetInstance().GetPrespectiveMatrix(*iterObj));

				XMMATRIX viewMatrix = XMLoadFloat4x4(&viewShadow4x4);
				XMMATRIX presMatrix = XMLoadFloat4x4(&presShadow4x4);

				light.lightView = viewMatrix;
				light.lightProject = presMatrix;
				light.hasShadow = true;
			}*/
		}
		else if (GenericObj<std::string>::GetValue(lightTypeIter->second) == Keys::Light::LightTypes::POINT)
		{
			CHL::Vec4& diffuse = GenericObj<CHL::Vec4>::GetValue(iterObj->find(Keys::Light::DIFFUSE)->second);
			CHL::Vec4& ambient = GenericObj<CHL::Vec4>::GetValue(iterObj->find(Keys::Light::AMBIENT)->second);
			CHL::Vec4& specular = GenericObj<CHL::Vec4>::GetValue(iterObj->find(Keys::Light::SPECULAR)->second);
			CHL::Vec4& position = GenericObj<CHL::Vec4>::GetValue(iterObj->find(Keys::Light::POSITION)->second);
			double range = GenericObj<double>::GetValue(iterObj->find(Keys::Light::RANGE)->second);
			CHL::Vec4& att = GenericObj<CHL::Vec4>::GetValue(iterObj->find(Keys::Light::ATTENUATION)->second);

			light.material.diffuse = CHL::ConvertVec4(diffuse);
			light.material.ambient = CHL::ConvertVec4(ambient);
			light.material.specular = CHL::ConvertVec4(specular);
			light.pos = CHL::ConvertVec4(position);
			light.range = (float)range;
			light.attenuation = CHL::ConvertVec4(att);
			light.type = 2;
		}
		else if (GenericObj<std::string>::GetValue(lightTypeIter->second) == Keys::Light::LightTypes::SPOT)
		{
			light = SpotLight::GetInstance().GetLightDesc(*iterObj);
			
			/*if (GenericObj<bool>::GetValue(iterObj->find(Keys::Light::HASHADOW)->second) == true)
			{
				SpotLight::GetInstance().GenerateShadowTexture(*iterObj, objects);

				XMFLOAT4X4 viewShadow4x4 = CHL::Convert4x4(SpotLight::GetInstance().GetViewMatrix(*iterObj));
				XMFLOAT4X4 presShadow4x4 = CHL::Convert4x4(SpotLight::GetInstance().GetPrespectiveMatrix(*iterObj));

				XMMATRIX viewMatrix = XMLoadFloat4x4(&viewShadow4x4);
				XMMATRIX presMatrix = XMLoadFloat4x4(&presShadow4x4);

				light.lightView = viewMatrix;
				light.lightProject = presMatrix;
				light.hasShadow = true;
			}*/
		}

		vecLightBuffer.push_back(light);
	}

	cBuffer::cbLight lightBuffer;
	ZeroMemory(&lightBuffer, sizeof(cBuffer::cbLight));

	std::size_t numberOfLights = vecLightBuffer.size();
	if (numberOfLights > 0)
	{
		unsigned int totalSize = numberOfLights * sizeof(cBuffer::CLightDesc);
	
		if (totalSize > sizeof(cBuffer::cbLight))
			totalSize = sizeof(cBuffer::cbLight);

		memcpy(&lightBuffer.lights, &vecLightBuffer.front(), totalSize);
	}

	ID3D11DeviceContext* pImmediateContext = this->D3DStuff.pImmediateContext;

	pImmediateContext->UpdateSubresource( this->D3DStuff.pCBLight, 0, NULL, &lightBuffer, 0, 0 );
	pImmediateContext->VSSetConstantBuffers( 2, 1, &(this->D3DStuff.pCBLight) );
	pImmediateContext->PSSetConstantBuffers( 2, 1, &(this->D3DStuff.pCBLight) );
}
void GraphicManager::SetupScene(TypedefObject::ObjectVector& objects)
{
	// Camera
	CHL::Vec4 vEye;
	vEye(0) = 0.0;	vEye(1) = 0.0;	vEye(2) = 0.0;	vEye(3) = 0.0;
	CHL::Vec4 vTM;
	vTM(0) = 0.0;	vTM(1) = 0.0;	vTM(2) = 1.0;	vTM(3) = 0.0;
	CHL::Vec4 vUp;
	vUp(0) = 0.0;	vUp(1) = 1.0;	vUp(2) = 0.0;	vUp(3) = 0.0;
	double pitch = 0.0;	double yaw = 0.0;	double roll = 0.0;

	if(!this->SceneInfo.CameraKeyID.empty())
	{
		TypedefObject::ObjectVector::const_iterator cameraIter;
		cameraIter = std::find_if(objects.begin(), objects.end(),
							[this](const TypedefObject::ObjectInfo& obj)
							{
								auto idIter = obj.find(Keys::ID);
								std::string ID = GenericObj<std::string>::GetValue(idIter->second);
								return (ID == this->SceneInfo.CameraKeyID);
							}); // Find Camera
		if(cameraIter != objects.cend()) // if camera found
		{
			TypedefObject::ObjectInfo camera = *cameraIter;
			vEye = GenericObj<CHL::Vec4>::GetValue(camera[Keys::Camera::EYE]);
			vTM = GenericObj<CHL::Vec4>::GetValue(camera[Keys::Camera::TARGETMAGNITUDE]);
			vUp = GenericObj<CHL::Vec4>::GetValue(camera[Keys::Camera::UP]);
			pitch = GenericObj<double>::GetValue(camera[Keys::Camera::RADIANPITCH]);
			yaw = GenericObj<double>::GetValue(camera[Keys::Camera::RADIANYAW]);
			roll = GenericObj<double>::GetValue(camera[Keys::Camera::RADIANROLL]);
		}
	}

	this->SceneInfo.CamerMatrix = CHL::ViewCalculation(vEye, vTM, vUp, pitch, yaw, roll);
	this->SceneInfo.Eye = vEye;

	// Prespective
	TypedefObject::ObjectVector::const_iterator prespectiveIter = objects.cend();

	double FovAngleY; 
	double height; double width;
	double nearZ;
	double farZ;

	if(!this->SceneInfo.PrespectiveKeyID.empty())
	{
		prespectiveIter = std::find_if(objects.begin(), objects.end(),
							[this](const TypedefObject::ObjectInfo& obj)
							{
								auto idIter = obj.find(Keys::ID);
								std::string ID = GenericObj<std::string>::GetValue(idIter->second);
								return (ID == this->SceneInfo.PrespectiveKeyID);
							}); // Find Prespectiveera
	}

	if(prespectiveIter != objects.cend()) // if prespective found
	{
		TypedefObject::ObjectInfo prespective = *prespectiveIter;
		FovAngleY = GenericObj<double>::GetValue(prespective[Keys::Prespective::FOVANGLE]);
		height = GenericObj<double>::GetValue(prespective[Keys::Prespective::SCREENHEIGHT]);
		width = GenericObj<double>::GetValue(prespective[Keys::Prespective::SCREENWIDTH]);
		nearZ = GenericObj<double>::GetValue(prespective[Keys::Prespective::MINVIEWABLE]);
		farZ = GenericObj<double>::GetValue(prespective[Keys::Prespective::MAXVIEWABLE]);
	}
	else
	{
		width = this->D3DStuff.vp.Width;
		height = this->D3DStuff.vp.Height;
		FovAngleY = 0.785398163;
		nearZ = 0.01;
		farZ = 5000.0;
	}

	this->SceneInfo.PrespectiveMatrix = CHL::PerspectiveFovLHCalculation(FovAngleY, width / height, nearZ, farZ);
}
void GraphicManager::SetupConstantBuffer(TypedefObject::ObjectVector& objects)
{
	CHL::Vec4 vEye = this->SceneInfo.Eye;

	cBuffer::cbInfo cbInfo;
	
	XMFLOAT4X4 view4x4 = CHL::Convert4x4(this->SceneInfo.CamerMatrix);;
	XMFLOAT4X4 proj4x4 = CHL::Convert4x4(this->SceneInfo.PrespectiveMatrix);;

	cbInfo.view = XMLoadFloat4x4(&view4x4);
	cbInfo.proj = XMLoadFloat4x4(&proj4x4);
	cbInfo.eye = XMFLOAT4((float)vEye(0), (float)vEye(1), (float)vEye(2), (float)vEye(3));

	ID3D11DeviceContext* pImmediateContext = this->D3DStuff.pImmediateContext;

	pImmediateContext->UpdateSubresource( this->D3DStuff.pCBInfo, 0, NULL, &cbInfo, 0, 0 );
	pImmediateContext->VSSetConstantBuffers( 1, 1, &(this->D3DStuff.pCBInfo) );
	pImmediateContext->PSSetConstantBuffers( 1, 1, &(this->D3DStuff.pCBInfo) );
}
void GraphicManager::ClearScreen(TypedefObject::ObjectVector& objects)
{
	// Clear the back buffer 
	float ClearColor[4] = {(float)this->SceneInfo.ClearColour(0), (float)this->SceneInfo.ClearColour(1), (float)this->SceneInfo.ClearColour(2), 1.0f}; // red,green,blue,alpha
	this->D3DStuff.pImmediateContext->ClearRenderTargetView( this->D3DStuff.pRenderTargetView, ClearColor );
	this->D3DStuff.pImmediateContext->ClearDepthStencilView( this->D3DStuff.pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
}
void GraphicManager::DrawObjects(TypedefObject::ObjectVector& objects)
{
	for(auto iterObj = objects.begin();
		iterObj != objects.end();
		++iterObj)
	{
		auto graphicIDIter = iterObj->find(Keys::BasicDrawable::DRAWABLEOBJ);
		if(graphicIDIter == iterObj->cend() )
		{
			continue;
		}

		std::string graphicObjectID = GenericObj<std::string>::GetValue(graphicIDIter->second);

		auto drawableIter = this->objectDrawables.find(graphicObjectID);
		
		if(drawableIter == this->objectDrawables.end())
		{
			continue;
		}// If it didn't fine then continue

		TypedefObject::ObjectInfo textures;
		for (auto iterObjInfo = iterObj->begin();
			iterObjInfo != iterObj->end();
			++iterObjInfo)
		{
			if (iterObjInfo->first.compare(0, Keys::BasicTexture::TEXTUREOBJ.size(), Keys::BasicTexture::TEXTUREOBJ) == 0)
			{
				textures.insert(*iterObjInfo);
			}
		}

		for(auto iterTexture = textures.cbegin();
			iterTexture != textures.cend();
			++iterTexture)
		{
			std::pair<std::string, int> textureInfo = GenericObj<std::pair<std::string, int>>::GetValue(iterTexture->second);
			auto texture = this->textures.find(textureInfo.first);
		
			if(texture != this->textures.cend())
			{
				texture->second->SettupTexture(textureInfo.second);
			}
		}

		drawableIter->second->Draw(*iterObj);

		for(auto iterTexture = textures.cbegin();
			iterTexture != textures.cend();
			++iterTexture)
		{
			std::pair<std::string, int> textureInfo = GenericObj<std::pair<std::string, int>>::GetValue(iterTexture->second);
			auto texture = this->textures.find(textureInfo.first);

			if(texture != this->textures.cend())
			{
				texture->second->CleanupTexture(textureInfo.second);
			}
		}
	}
}
void GraphicManager::Present(TypedefObject::ObjectVector& objects)
{
	// Present the information rendered to the back buffer to the front buffer (the screen)
	this->D3DStuff.pSwapChain->Present( 0, 0 );
}

void GraphicManager::InitDevice()
{
	TypedefObject::ObjectVector objects = ObjectManagerOutput::GetAllObjects();

	TypedefObject::ObjectVector::const_iterator windowInfoIter;
	windowInfoIter = std::find_if(objects.begin(), objects.end(),
		[](const TypedefObject::ObjectInfo& obj)
	{
		auto classTypeIter = obj.find(Keys::Class);
		if(classTypeIter != obj.end())
		{
			std::string classID = GenericObj<std::string>::GetValue(classTypeIter->second);
			return (classID == Keys::ClassType::WindowInfo);
		}
		else
			return false;
	});

	if(windowInfoIter == objects.cend())
	{
		throw std::exception("Failed to find windows info");
	}
	TypedefObject::ObjectInfo windowInfo = *windowInfoIter;

	int Width = GenericObj<int>::GetValue(windowInfo[Keys::Window::WIDTH]);
	int Height = GenericObj<int>::GetValue(windowInfo[Keys::Window::HEIGHT]);
	HWND hwnd = GenericObj<HWND>::GetValue(windowInfo[Keys::Window::HWND]);

	HRESULT hr = S_OK;

	UINT createDeviceFlags = 0;
#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE,
	};
	UINT numDriverTypes = ARRAYSIZE(driverTypes);

	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
	};
	UINT numFeatureLevels = ARRAYSIZE(featureLevels);

	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 1;
	sd.BufferDesc.Width = Width;
	sd.BufferDesc.Height = Height;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = hwnd;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;

	for(UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
	{
		this->D3DStuff.driverType = driverTypes[driverTypeIndex];
		hr = D3D11CreateDeviceAndSwapChain(NULL, this->D3DStuff.driverType, NULL, createDeviceFlags, featureLevels, numFeatureLevels,
			D3D11_SDK_VERSION, &sd, &this->D3DStuff.pSwapChain, &this->D3DStuff.pd3dDevice, &this->D3DStuff.featureLevel, &this->D3DStuff.pImmediateContext);
		if(SUCCEEDED(hr))
			break;
	}
	if(FAILED(hr))
		throw std::exception("Failed at creating device and SwapChain");

	// Create a render target view
	ID3D11Texture2D* pBackBuffer = NULL;
	hr = this->D3DStuff.pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	if(FAILED(hr))
		throw std::exception("Failed at creating back buffer");

	hr = this->D3DStuff.pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &this->D3DStuff.pRenderTargetView);
	pBackBuffer->Release();
	if(FAILED(hr))
		throw std::exception("Failed at creating Render Target view");

	// Set up depth & stencil buffer
	// Initialize the description of the depth buffer.
	D3D11_TEXTURE2D_DESC depthBufferDesc;
	ZeroMemory(&depthBufferDesc, sizeof(depthBufferDesc));

	// Set up the description of the depth buffer.
	depthBufferDesc.Width = Width;
	depthBufferDesc.Height = Height;
	depthBufferDesc.MipLevels = 1;
	depthBufferDesc.ArraySize = 1;
	depthBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthBufferDesc.SampleDesc.Count = 1;
	depthBufferDesc.SampleDesc.Quality = 0;
	depthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthBufferDesc.CPUAccessFlags = 0;
	depthBufferDesc.MiscFlags = 0;

	// Create the texture for the depth buffer using the filled out description.
	hr = this->D3DStuff.pd3dDevice->CreateTexture2D(&depthBufferDesc, NULL, &this->D3DStuff.pDepthStencilBuffer);
	if(FAILED(hr))
	{
		throw std::exception("Failed at creating dept buffer");
	}

	// Initialize the description of the stencil state.
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
	ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));

	// Set up the description of the stencil state.
	depthStencilDesc.DepthEnable = true;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;

	depthStencilDesc.StencilEnable = true;
	depthStencilDesc.StencilReadMask = 0xFF;
	depthStencilDesc.StencilWriteMask = 0xFF;

	// Stencil operations if pixel is front-facing.
	depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	// Stencil operations if pixel is back-facing.
	depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	// Create the depth stencil state.
	hr = this->D3DStuff.pd3dDevice->CreateDepthStencilState(&depthStencilDesc, &this->D3DStuff.pDepthStencilState);
	if(FAILED(hr))
	{
		throw std::exception("Failed at creating Dept stencil State");
	}

	// Set the depth stencil state.
	this->D3DStuff.pImmediateContext->OMSetDepthStencilState(this->D3DStuff.pDepthStencilState, 1);

	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
	// Initialize the depth stencil view.
	ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));

	// Set up the depth stencil view description.
	depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Texture2D.MipSlice = 0;

	// Create the depth stencil view.
	hr = this->D3DStuff.pd3dDevice->CreateDepthStencilView(this->D3DStuff.pDepthStencilBuffer, &depthStencilViewDesc, &this->D3DStuff.pDepthStencilView);
	if(FAILED(hr))
	{
		throw std::exception("Failed at creating depth stencil view");
	}

	this->D3DStuff.pImmediateContext->OMSetRenderTargets(1, &this->D3DStuff.pRenderTargetView, this->D3DStuff.pDepthStencilView);

	// Setup the viewport
	this->D3DStuff.vp.Width = (FLOAT)Width;
	this->D3DStuff.vp.Height = (FLOAT)Height;
	this->D3DStuff.vp.MinDepth = 0.0f;
	this->D3DStuff.vp.MaxDepth = 1.0f;
	this->D3DStuff.vp.TopLeftX = 0;
	this->D3DStuff.vp.TopLeftY = 0;
	this->D3DStuff.pImmediateContext->RSSetViewports(1, &(this->D3DStuff.vp));

	DX11Helper::LoadBuffer<cBuffer::cbInfo>(this->D3DStuff.pd3dDevice, &(this->D3DStuff.pCBInfo));

	DX11Helper::LoadBuffer<cBuffer::cbLight>(this->D3DStuff.pd3dDevice, &(this->D3DStuff.pCBLight));

	this->D3DStuff.IsInitialized = true;
}


void GraphicManager::InsertObjectDrawable(std::shared_ptr<Drawable> obj)
{
	this->objectDrawables[obj->ID] = obj;
}
const std::hash_map<std::string, std::shared_ptr<Drawable>> GraphicManager::AllObjectDrawables()
{
	return this->objectDrawables;
}


void GraphicManager::InsertTexture(std::shared_ptr<Texture> obj)
{
	this->textures[obj->ID] = obj;
}
const std::hash_map<std::string, std::shared_ptr<Texture>> GraphicManager::AllTexture()
{
	return this->textures;
}

void GraphicManager::InsertScreenCapture(std::shared_ptr<ScreenCapture> obj)
{
	this->ScreenCaptures[obj->ID] = obj;
}
const std::hash_map<std::string, std::shared_ptr<ScreenCapture>> GraphicManager::AllScreenCapture()
{
	return this->ScreenCaptures;
}

void GraphicManager::InsertContinuousScreenCapture(std::shared_ptr<ContinuousScreenShot> obj)
{
	this->ContinuousScreenCaptures[obj->ID] = obj;
}
const std::hash_map<std::string, std::shared_ptr<ContinuousScreenShot>> GraphicManager::AllContinuousScreenCapture()
{
	return this->ContinuousScreenCaptures;
}