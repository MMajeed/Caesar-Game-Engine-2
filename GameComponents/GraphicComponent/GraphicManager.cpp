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

GraphicManager::GraphicManager()
{
	this->direct3d.pd3dDevice			= 0;
	this->direct3d.pImmediateContext	= 0;
	this->direct3d.pSwapChain			= 0;
	this->direct3d.pRenderTargetView	= 0;
	this->direct3d.pDepthStencilBuffer	= 0;
	this->direct3d.pDepthStencilState	= 0;
	this->direct3d.pDepthStencilView	= 0;

	this->ClearColour(0) = 0.5;
	this->ClearColour(1) = 0.5;
	this->ClearColour(2) = 0.5;
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

	this->SetupLight(objects);
	this->SetupCameraNPrespective(objects);
	this->SetupConstantBuffer(objects);
	this->ClearScreen(objects);
	this->DrawObjects(objects);
	this->Present(objects);
}

void GraphicManager::Shutdown()
{

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
			|| GenericObject<std::string>::GetValue(classTypeIter->second) != Keys::ClassType::Light // and that class type is NOT a light
			|| lightTypeIter == iterObj->cend()) // and it dosn't have a light type
		{// then continue
			continue;
		}

		cBuffer::CLightDesc light;
		ZeroMemory(&light, sizeof(cBuffer::CLightDesc));
		if (GenericObject<std::string>::GetValue(lightTypeIter->second) == Keys::Light::LightTypes::DIRECTIONAL)
		{
			light = DirectLight::GetInstance().GetLightDesc(*iterObj);

			//if(GenericObject<bool>::GetValue(iterObj->find(Keys::HASHADOW)->second) == true)
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
		else if (GenericObject<std::string>::GetValue(lightTypeIter->second) == Keys::Light::LightTypes::POINT)
		{
			CHL::Vec4& diffuse = GenericObject<CHL::Vec4>::GetValue(iterObj->find(Keys::Light::DIFFUSE)->second);
			CHL::Vec4& ambient = GenericObject<CHL::Vec4>::GetValue(iterObj->find(Keys::Light::AMBIENT)->second);
			CHL::Vec4& specular = GenericObject<CHL::Vec4>::GetValue(iterObj->find(Keys::Light::SPECULAR)->second);
			CHL::Vec4& position = GenericObject<CHL::Vec4>::GetValue(iterObj->find(Keys::Light::POSITION)->second);
			double range = GenericObject<double>::GetValue(iterObj->find(Keys::Light::RANGE)->second);
			CHL::Vec4& att = GenericObject<CHL::Vec4>::GetValue(iterObj->find(Keys::Light::ATTENUATION)->second);

			light.material.diffuse = CHL::ConvertVec4(diffuse);
			light.material.ambient = CHL::ConvertVec4(ambient);
			light.material.specular = CHL::ConvertVec4(specular);
			light.pos = CHL::ConvertVec4(position);
			light.range = (float)range;
			light.attenuation = CHL::ConvertVec4(att);
			light.type = 2;
		}
		else if (GenericObject<std::string>::GetValue(lightTypeIter->second) == Keys::Light::LightTypes::SPOT)
		{
			light = SpotLight::GetInstance().GetLightDesc(*iterObj);
			
			if (GenericObject<bool>::GetValue(iterObj->find(Keys::Light::HASHADOW)->second) == true)
			{
				SpotLight::GetInstance().GenerateShadowTexture(*iterObj, objects);

				XMFLOAT4X4 viewShadow4x4 = CHL::Convert4x4(SpotLight::GetInstance().GetViewMatrix(*iterObj));
				XMFLOAT4X4 presShadow4x4 = CHL::Convert4x4(SpotLight::GetInstance().GetPrespectiveMatrix(*iterObj));

				XMMATRIX viewMatrix = XMLoadFloat4x4(&viewShadow4x4);
				XMMATRIX presMatrix = XMLoadFloat4x4(&presShadow4x4);

				light.lightView = viewMatrix;
				light.lightProject = presMatrix;
				light.hasShadow = true;
			}
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

	ID3D11DeviceContext* pImmediateContext = this->direct3d.pImmediateContext;

	pImmediateContext->UpdateSubresource( this->direct3d.pCBLight, 0, NULL, &lightBuffer, 0, 0 );
	pImmediateContext->VSSetConstantBuffers( 2, 1, &(this->direct3d.pCBLight) );
	pImmediateContext->PSSetConstantBuffers( 2, 1, &(this->direct3d.pCBLight) );
}
void GraphicManager::SetupCameraNPrespective(TypedefObject::ObjectVector& objects)
{
	// Camera
	CHL::Vec4 vEye;
	CHL::Vec4 vTM;
	CHL::Vec4 vUp;
	double pitch;	double yaw;	double roll;

	TypedefObject::ObjectVector::const_iterator cameraIter;
	cameraIter = objects.First([](TypedefObject::ObjectVector::const_iterator objIter)
			{ 
				auto classTypeIter = objIter->find(Keys::Class);
				if(classTypeIter != objIter->end())
				{
					std::string classID = GenericObject<std::string>::GetValue(classTypeIter->second);
					return (classID == Keys::ClassType::Camera); 
				}
				else
					return false;
			}); // Find Camera
	if(cameraIter != objects.cend()) // if camera found
	{
		TypedefObject::ObjectInfo camera = *cameraIter;
		vEye = GenericObject<CHL::Vec4>::GetValue(camera[Keys::Camera::EYE]);
		vTM = GenericObject<CHL::Vec4>::GetValue(camera[Keys::Camera::TARGETMAGNITUDE]);
		vUp = GenericObject<CHL::Vec4>::GetValue(camera[Keys::Camera::UP]);
		pitch = GenericObject<double>::GetValue(camera[Keys::Camera::RADIANPITCH]);
		yaw = GenericObject<double>::GetValue(camera[Keys::Camera::RADIANYAW]);
		roll = GenericObject<double>::GetValue(camera[Keys::Camera::RADIANROLL]);
	}
	else
	{
		vEye(0) = 0.0;	vEye(1) = 0.0;	vEye(2) = 0.0;	vEye(3) = 0.0; 
		vTM(0) = 0.0;	vTM(1) = 0.0;	vTM(2) = 1.0;	vTM(3) = 0.0; 
		vUp(0) = 0.0;	vUp(1) = 1.0;	vUp(2) = 0.0;	vUp(3) = 0.0; 
		pitch = 0;	yaw = 0;	roll = 0;	
	}

	this->CamerMatrix = CHL::ViewCalculation(vEye, vTM, vUp, pitch, yaw, roll);

	// Prespective
	TypedefObject::ObjectVector::const_iterator prespectiveIter;

	double FovAngleY; 
	double height; double width;
	double nearZ;
	double farZ;

	prespectiveIter = objects.First([](TypedefObject::ObjectVector::const_iterator objIter)
			{ 
				auto classTypeIter = objIter->find(Keys::Class);
				if(classTypeIter != objIter->end())
				{
					std::string classID = GenericObject<std::string>::GetValue(classTypeIter->second);
					return (classID == Keys::ClassType::Prespective); 
				}
				else
					return false;
			}); // Find prespective]

	if(prespectiveIter != objects.cend()) // if prespective found
	{
		TypedefObject::ObjectInfo prespective = *prespectiveIter;
		FovAngleY = GenericObject<double>::GetValue(prespective[Keys::Prespective::FOVANGLE]);
		height = GenericObject<double>::GetValue(prespective[Keys::Prespective::SCREENHEIGHT]);
		width = GenericObject<double>::GetValue(prespective[Keys::Prespective::SCREENWIDTH]);
		nearZ = GenericObject<double>::GetValue(prespective[Keys::Prespective::MINVIEWABLE]);
		farZ = GenericObject<double>::GetValue(prespective[Keys::Prespective::MAXVIEWABLE]);
	}
	else
	{
		TypedefObject::ObjectVector::const_iterator windowInfoIter;
		windowInfoIter = objects.First([](TypedefObject::ObjectVector::const_iterator objIter)
				{ 
					auto classTypeIter = objIter->find(Keys::Class);
					if(classTypeIter != objIter->end())
					{
						std::string classID = GenericObject<std::string>::GetValue(classTypeIter->second);
						return (classID == Keys::ClassType::WindowInfo); 
					}
					else
						return false;
				}); // Find WindoInfo

		if(windowInfoIter == objects.cend())
		{
			throw std::exception("Failed to find windows info");
		}
		TypedefObject::ObjectInfo windowInfo = *windowInfoIter;

		width = GenericObject<int>::GetValue(windowInfo[Keys::Window::WIDTH]);
		height = GenericObject<int>::GetValue(windowInfo[Keys::Window::HEIGHT]);
		FovAngleY = 0.785398163;
		nearZ = 0.01;
		farZ = 5000.0;
	}

	this->PrespectiveMatrix = CHL::PerspectiveFovLHCalculation(FovAngleY, height/width, nearZ, farZ);
}
void GraphicManager::SetupConstantBuffer(TypedefObject::ObjectVector& objects)
{
	CHL::Vec4 vEye;

	TypedefObject::ObjectVector::const_iterator cameraIter;
	cameraIter = objects.First([](TypedefObject::ObjectVector::const_iterator objIter)
			{ 
				auto classTypeIter = objIter->find(Keys::Class);
				if(classTypeIter != objIter->end())
				{
					std::string classID = GenericObject<std::string>::GetValue(classTypeIter->second);
					return (classID == Keys::ClassType::Camera); 
				}
				else
					return false;
			}); // Find Camera

	if(cameraIter != objects.cend()) // if camera found
	{
		TypedefObject::ObjectInfo camera = *cameraIter;
		vEye = GenericObject<CHL::Vec4>::GetValue(camera[Keys::Camera::EYE]);
	}
	else
	{
		vEye(0) = 0.0;	vEye(1) = 0.0;	vEye(2) = 0.0;	vEye(3) = 0.0; 
	}

	cBuffer::cbInfo cbInfo;
	
	XMFLOAT4X4 view4x4 = CHL::Convert4x4(this->CamerMatrix);;
	XMFLOAT4X4 proj4x4 = CHL::Convert4x4(this->PrespectiveMatrix);;

	cbInfo.view = XMLoadFloat4x4(&view4x4);
	cbInfo.proj = XMLoadFloat4x4(&proj4x4);
	cbInfo.eye = XMFLOAT4((float)vEye(0), (float)vEye(1), (float)vEye(2), (float)vEye(3));

	ID3D11DeviceContext* pImmediateContext = this->direct3d.pImmediateContext;

	pImmediateContext->UpdateSubresource( this->direct3d.pCBInfo, 0, NULL, &cbInfo, 0, 0 );
	pImmediateContext->VSSetConstantBuffers( 1, 1, &(this->direct3d.pCBInfo) );
	pImmediateContext->PSSetConstantBuffers( 1, 1, &(this->direct3d.pCBInfo) );
}
void GraphicManager::ClearScreen(TypedefObject::ObjectVector& objects)
{
	// Clear the back buffer 
	float ClearColor[4] = { (float)this->ClearColour(0), (float)this->ClearColour(1), (float)this->ClearColour(2), 1.0f }; // red,green,blue,alpha
	this->direct3d.pImmediateContext->ClearRenderTargetView( this->direct3d.pRenderTargetView, ClearColor );
	this->direct3d.pImmediateContext->ClearDepthStencilView( this->direct3d.pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
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

		std::string graphicObjectID = GenericObject<std::string>::GetValue(graphicIDIter->second);

		auto drawableIter = this->objectDrawables.find(graphicObjectID);
		
		if(drawableIter == this->objectDrawables.end())
		{
			continue;
		}// If it didn't fine then continue

		auto textures = iterObj->Where([](const TypedefObject::ObjectInfo::const_iterator iterObj)
						{ 
							return (iterObj->first.compare(0, Keys::BasicTexture::TEXTUREOBJ.size(), Keys::BasicTexture::TEXTUREOBJ) == 0);
						});

		for(auto iterTexture = textures.cbegin();
			iterTexture != textures.cend();
			++iterTexture)
		{
			std::string textureID = GenericObject<std::string>::GetValue(iterTexture->second);
			auto texture = this->textures.find(textureID);
		
			if(texture != this->textures.cend())
			{
				texture->second->SettupTexture(*iterObj);
			}
		}

		drawableIter->second->Draw(*iterObj);

		for(auto iterTexture = textures.cbegin();
			iterTexture != textures.cend();
			++iterTexture)
		{
			std::string textureID = GenericObject<std::string>::GetValue(iterTexture->second);
			auto texture = this->textures.find(textureID);

			if(texture != this->textures.cend())
			{
				texture->second->CleanupTexture(*iterObj);
			}
		}
	}
}
void GraphicManager::Present(TypedefObject::ObjectVector& objects)
{
	// Present the information rendered to the back buffer to the front buffer (the screen)
	this->direct3d.pSwapChain->Present( 0, 0 );
}
void GraphicManager::InsertObjectDrawable(std::shared_ptr<Drawable> obj)
{
	this->objectDrawables[obj->ID] = obj;
}
const CHL::MapQ<std::string, std::shared_ptr<Drawable>> GraphicManager::AllObjectDrawables()
{
	return this->objectDrawables;
}

void GraphicManager::InsertTexture(std::shared_ptr<Texture> obj)
{
	this->textures[obj->ID] = obj;
}
const CHL::MapQ<std::string, std::shared_ptr<Texture>> GraphicManager::AllTexture()
{
	return this->textures;
}

void GraphicManager::InitDevice()
{
	TypedefObject::ObjectVector objects = ObjectManagerOutput::GetAllObjects();

	TypedefObject::ObjectVector::const_iterator windowInfoIter;
	windowInfoIter = objects.First([](TypedefObject::ObjectVector::const_iterator objIter)
			{ 
				auto classTypeIter = objIter->find(Keys::Class);
				if(classTypeIter != objIter->end())
				{
					std::string classID = GenericObject<std::string>::GetValue(classTypeIter->second);
					return (classID == Keys::ClassType::WindowInfo); 
				}
				else
					return false;
			}); // Find WindoInfo

	if(windowInfoIter == objects.cend())
	{
		throw std::exception("Failed to find windows info");
	}
	TypedefObject::ObjectInfo windowInfo = *windowInfoIter;

	int Width = GenericObject<int>::GetValue(windowInfo[Keys::Window::WIDTH]);
	int Height = GenericObject<int>::GetValue(windowInfo[Keys::Window::HEIGHT]);
	HWND hwnd = GenericObject<HWND>::GetValue(windowInfo[Keys::Window::HWND]);

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
	UINT numDriverTypes = ARRAYSIZE( driverTypes );

	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
	};
	UINT numFeatureLevels = ARRAYSIZE( featureLevels );

	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory( &sd, sizeof( sd ) );
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

	for( UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++ )
	{
		this->direct3d.driverType = driverTypes[driverTypeIndex];
		hr = D3D11CreateDeviceAndSwapChain( NULL, this->direct3d.driverType, NULL, createDeviceFlags, featureLevels, numFeatureLevels,
			D3D11_SDK_VERSION, &sd, &this->direct3d.pSwapChain, &this->direct3d.pd3dDevice, &this->direct3d.featureLevel, &this->direct3d.pImmediateContext );
		if( SUCCEEDED( hr ) )
			break;
	}
	if( FAILED( hr ) )
		throw std::exception("Failed at creating device and SwapChain");

	// Create a render target view
	ID3D11Texture2D* pBackBuffer = NULL;
	hr = this->direct3d.pSwapChain->GetBuffer( 0, __uuidof( ID3D11Texture2D ), ( LPVOID* )&pBackBuffer );
	if( FAILED( hr ) )
		throw std::exception("Failed at creating back buffer");

	hr = this->direct3d.pd3dDevice->CreateRenderTargetView( pBackBuffer, NULL, &this->direct3d.pRenderTargetView );
	pBackBuffer->Release();
	if( FAILED( hr ) )
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
	hr = this->direct3d.pd3dDevice->CreateTexture2D(&depthBufferDesc, NULL, &this->direct3d.pDepthStencilBuffer);
	if(FAILED(hr))
	{
		throw std::exception("Failed at creating dept buffer");
	}

	// Initialize the description of the stencil state.
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
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
	hr = this->direct3d.pd3dDevice->CreateDepthStencilState(&depthStencilDesc, &this->direct3d.pDepthStencilState);
	if(FAILED(hr)) 
	{
		throw std::exception("Failed at creating Dept stencil State");
	}

	// Set the depth stencil state.
	this->direct3d.pImmediateContext->OMSetDepthStencilState(this->direct3d.pDepthStencilState, 1);

	// Initialize the depth stencil view.
	ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));

	// Set up the depth stencil view description.
	depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Texture2D.MipSlice = 0;

	// Create the depth stencil view.
	hr = this->direct3d.pd3dDevice->CreateDepthStencilView(this->direct3d.pDepthStencilBuffer, &depthStencilViewDesc, &this->direct3d.pDepthStencilView);
	if(FAILED(hr))
	{
		throw std::exception("Failed at creating depth stencil view");
	}

	this->direct3d.pImmediateContext->OMSetRenderTargets( 1, &this->direct3d.pRenderTargetView, this->direct3d.pDepthStencilView );
	
	// Setup the viewport
	this->direct3d.vp.Width = (FLOAT)Width;
	this->direct3d.vp.Height = (FLOAT)Height;
	this->direct3d.vp.MinDepth = 0.0f;
	this->direct3d.vp.MaxDepth = 1.0f;
	this->direct3d.vp.TopLeftX = 0;
	this->direct3d.vp.TopLeftY = 0;
	this->direct3d.pImmediateContext->RSSetViewports( 1, &(this->direct3d.vp) );

	std::wstring error;
	if(!DX11Helper::LoadBuffer<cBuffer::cbInfo>(this->direct3d.pd3dDevice, &(this->direct3d.pCBInfo), error))
	{
		throw std::exception(CHL::ToString(error).c_str());
	}

	if(!DX11Helper::LoadBuffer<cBuffer::cbLight>(this->direct3d.pd3dDevice, &(this->direct3d.pCBLight), error))
	{
		throw std::exception(CHL::ToString(error).c_str());
	}
}