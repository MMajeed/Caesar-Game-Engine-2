#include "GraphicManager.h"

#include <EntityCommunicator\EntityConfig.h>
#include <EntityCommunicator\ImportantIDConfig.h>
#include <Keys.h>
#include <3DMath.h>
#include <XNAConverter.h>
#include "DX11Helper.h"
#include "Buffers.h"
#include "SetupLight.h"
#include <algorithm>
#include <CameraINFO.h>
#include <ObjectINFO.h>
#include <WindowINFO.h>

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

	this->SceneInfo.ClearColour = {0.5, 0.5, 0.5, 0.5};
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
	std::hash_map<std::string, SP_INFO> objects = EntityConfig::GetAllEntity();

	this->SetupScene(objects);
	this->SetupLight(objects);
	this->RunAllCapture(objects);
	this->SetupConstantBuffer(objects);
	this->ClearScreen(objects);
	this->DrawObjects(objects);
	this->Present(objects);
}

void GraphicManager::Shutdown()
{

}

void GraphicManager::RunAllCapture(std::hash_map<std::string, SP_INFO>& objects)
{
	for(auto iter = this->ContinuousScreenCaptures.begin();
		iter != this->ContinuousScreenCaptures.end();
		++iter)
	{
		iter->second->Snap(objects);
	}
}
void GraphicManager::SetupLight(std::hash_map<std::string, SP_INFO>& objects)
{
	Light::GetInstance().SetupLight(objects);
}
void GraphicManager::SetupScene(std::hash_map<std::string, SP_INFO>& objects)
{
	// Camera
	CHL::Vec4 vEye{0.0, 0.0, 0.0, 0.0};
	CHL::Vec4 vTM{0.0, 0.0, 1.0, 0.0};
	CHL::Vec4 vUp{0.0, 1.0, 0.0, 0.0};
	double pitch = 0.0;	double yaw = 0.0;	double roll = 0.0;

	std::string cameraID = CameraID::Get();

	if(!cameraID.empty())
	{
		std::hash_map<std::string, SP_INFO>::const_iterator cameraIter = objects.find(cameraID);

		if(cameraIter != objects.cend()) // if camera found
		{
			std::shared_ptr<CameraINFO> cam = std::dynamic_pointer_cast<CameraINFO>(cameraIter->second);

			if(cam)
			{
				vEye = cam->Eye;
				vTM = cam->TargetMagnitude;
				vUp = cam->Up;
				pitch = cam->Pitch;
				yaw = cam->Yaw;
				roll = cam->Roll;
			}
		}
	}

	this->SceneInfo.CamerMatrix = CHL::ViewCalculation(vEye, vTM, vUp, pitch, yaw, roll);
	this->SceneInfo.Eye = vEye;

	// Prespective
	std::hash_map<std::string, SP_INFO>::const_iterator prespectiveIter = objects.cend();

	double FovAngleY = 0.785398163;
	double height = this->D3DStuff.vp.Height; double width = this->D3DStuff.vp.Width;
	double nearZ = 0.01;
	double farZ = 5000.0;

	std::string prespective = PrespectiveID::Get();
	if(!prespective.empty())
	{
		std::hash_map<std::string, SP_INFO>::const_iterator cameraIter = objects.find(prespective);

		if(cameraIter != objects.cend()) // if prespective found
		{
			// Fill in later
		}
	}

	this->SceneInfo.PrespectiveMatrix = CHL::PerspectiveFovLHCalculation(FovAngleY, width / height, nearZ, farZ);
}
void GraphicManager::SetupConstantBuffer(std::hash_map<std::string, SP_INFO>& objects)
{
	CHL::Vec4 vEye = this->SceneInfo.Eye;

	cBuffer::cbInfo cbInfo;
	
	XMFLOAT4X4 view4x4 = CHL::Convert4x4(this->SceneInfo.CamerMatrix);;
	XMFLOAT4X4 proj4x4 = CHL::Convert4x4(this->SceneInfo.PrespectiveMatrix);;

	cbInfo.view = XMMatrixTranspose(XMLoadFloat4x4(&view4x4));
	cbInfo.proj = XMMatrixTranspose(XMLoadFloat4x4(&proj4x4));
	cbInfo.eye = XMFLOAT4((float)vEye(0), (float)vEye(1), (float)vEye(2), (float)vEye(3));

	ID3D11DeviceContext* pImmediateContext = this->D3DStuff.pImmediateContext;

	pImmediateContext->UpdateSubresource( this->D3DStuff.pCBInfo, 0, NULL, &cbInfo, 0, 0 );
}
void GraphicManager::ClearScreen(std::hash_map<std::string, SP_INFO>& objects)
{
	// Clear the back buffer 
	float ClearColor[4] = {(float)this->SceneInfo.ClearColour(0), (float)this->SceneInfo.ClearColour(1), (float)this->SceneInfo.ClearColour(2), 1.0f}; // red,green,blue,alpha
	this->D3DStuff.pImmediateContext->ClearRenderTargetView( this->D3DStuff.pRenderTargetView, ClearColor );
	this->D3DStuff.pImmediateContext->ClearDepthStencilView( this->D3DStuff.pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
}
void GraphicManager::DrawObjects(std::hash_map<std::string, SP_INFO>& objects)
{
	std::vector<std::shared_ptr<ObjectINFO>> vecObjects;
	vecObjects.reserve(objects.size());

	for(auto iterObj = objects.begin();
		iterObj != objects.end();
		++iterObj)
	{
		std::shared_ptr<ObjectINFO> objInfo = std::dynamic_pointer_cast<ObjectINFO>(iterObj->second);
		if(!objInfo){ continue; }

		bool fitsTheScene = true;
		for(auto iterScene = this->sceneFilters.begin();
			iterScene != this->sceneFilters.end();
			++iterScene)
		{
			fitsTheScene = iterScene->second->Filter(iterObj->second);
			if(fitsTheScene == false){ break; }
		}
		if(fitsTheScene == false){ continue; }

		vecObjects.push_back(objInfo);
	}

	CHL::Vec4 eye = this->SceneInfo.Eye;
	std::sort(vecObjects.begin(), vecObjects.end(),
			  [eye](const std::shared_ptr<ObjectINFO>& a, const std::shared_ptr<ObjectINFO>& b) -> bool
			  {
				float rankA = 0.0f; float rankB = 0.0f;

				if(a->Diffuse[3] >= 1.0)	 { rankA += 100000.0f; }
				else if(a->Diffuse[3] < 1.0) { rankA += CHL::Length(eye, a->Location); }
		
				if(b->Diffuse[3] >= 1.0)	 { rankB += 100000.0f; }
				else if(b->Diffuse[3] < 1.0) { rankB += CHL::Length(eye, b->Location); }

				if(a->Depth == false) { rankA -= 1000000.0f; }
				if(b->Depth == false) { rankB -= 1000000.0f; }

				return rankA > rankB;
			 });

	for(auto iterObj = vecObjects.begin();
		iterObj != vecObjects.end();
		++iterObj)
	{

		auto drawableIter = this->objectDrawables.find((*iterObj)->DrawObjID);
		if(drawableIter == this->objectDrawables.end()){ continue; }// If it didn't fine then continue

		drawableIter->second->Draw(*iterObj);

	}

}
void GraphicManager::Present(std::hash_map<std::string, SP_INFO>& objects)
{
	// Present the information rendered to the back buffer to the front buffer (the screen)
	this->D3DStuff.pSwapChain->Present( 0, 0 );
}

void GraphicManager::InitDevice()
{
	std::hash_map<std::string, SP_INFO> objects = EntityConfig::GetAllEntity();

	std::string window = WindowINFOID::Get();
	if(window.empty()){	throw std::invalid_argument("Windows Information is not set");	}
	
	std::hash_map<std::string, SP_INFO>::iterator iter = objects.find(window);
	if(iter == objects.cend()) { throw std::invalid_argument("Could not find windows Info"); }
	std::shared_ptr<WindowINFO> windowInfo = std::dynamic_pointer_cast<WindowINFO>(iter->second);
	
	int Width = windowInfo->Width;
	int Height = windowInfo->Height;
	HWND hwnd = windowInfo->HWND;

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
		throw std::runtime_error("Failed at creating device and SwapChain");

	// Create a render target view
	ID3D11Texture2D* pBackBuffer = NULL;
	hr = this->D3DStuff.pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	if(FAILED(hr))
		throw std::runtime_error("Failed at creating back buffer");

	hr = this->D3DStuff.pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &this->D3DStuff.pRenderTargetView);
	pBackBuffer->Release();
	if(FAILED(hr))
		throw std::runtime_error("Failed at creating Render Target view");

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
		throw std::runtime_error("Failed at creating dept buffer");
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
		throw std::runtime_error("Failed at creating Dept stencil State");
	}

	D3D11_DEPTH_STENCIL_DESC depthDisabledStencilDesc;
	ZeroMemory(&depthDisabledStencilDesc, sizeof(depthDisabledStencilDesc));

	// Set up the depth stencil view description.
	depthDisabledStencilDesc.DepthEnable = false;
	depthDisabledStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthDisabledStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;
	depthDisabledStencilDesc.StencilEnable = true;
	depthDisabledStencilDesc.StencilReadMask = 0xFF;
	depthDisabledStencilDesc.StencilWriteMask = 0xFF;
	depthDisabledStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthDisabledStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	depthDisabledStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthDisabledStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	depthDisabledStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthDisabledStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	depthDisabledStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthDisabledStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	// Create the depth stencil view.
	hr = this->D3DStuff.pd3dDevice->CreateDepthStencilState(&depthDisabledStencilDesc, &this->D3DStuff.pDepthDisabledStencilState);
	if(FAILED(hr))
	{
		throw std::runtime_error("Failed at creating no depth state");
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
		throw std::runtime_error("Failed at creating depth stencil view");
	}

	// Set the depth stencil state.
	this->D3DStuff.pImmediateContext->OMSetDepthStencilState(this->D3DStuff.pDepthStencilState, 1);

	this->D3DStuff.pImmediateContext->OMSetRenderTargets(1, &this->D3DStuff.pRenderTargetView, this->D3DStuff.pDepthStencilView);

	D3D11_BLEND_DESC transparentDesc = {0};
	transparentDesc.AlphaToCoverageEnable = false;
	transparentDesc.IndependentBlendEnable = false;

	transparentDesc.RenderTarget[0].BlendEnable = true;
	transparentDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	transparentDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	transparentDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	transparentDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	transparentDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	transparentDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	transparentDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	hr = this->D3DStuff.pd3dDevice->CreateBlendState(&transparentDesc, &(this->D3DStuff.pTransperency));
	if(FAILED(hr))
	{
		throw std::runtime_error("Failed at creating a transperency blend");
	}
	float blendFactor[] = {0.0f, 0.0f, 0.0f, 0.0f};
	this->D3DStuff.pImmediateContext->OMSetBlendState(this->D3DStuff.pTransperency, blendFactor, 0xffffffff);

	// Setup the viewport
	this->D3DStuff.vp.Width = (FLOAT)Width;
	this->D3DStuff.vp.Height = (FLOAT)Height;
	this->D3DStuff.vp.MinDepth = 0.0f;
	this->D3DStuff.vp.MaxDepth = 1.0f;
	this->D3DStuff.vp.TopLeftX = 0;
	this->D3DStuff.vp.TopLeftY = 0;
	this->D3DStuff.pImmediateContext->RSSetViewports(1, &(this->D3DStuff.vp));

	DX11Helper::LoadBuffer<cBuffer::cbObject>(this->D3DStuff.pd3dDevice, &( this->D3DStuff.pCBObject ));
	this->D3DStuff.pImmediateContext->VSSetConstantBuffers(0, 1, &( this->D3DStuff.pCBObject ));
	this->D3DStuff.pImmediateContext->PSSetConstantBuffers(0, 1, &( this->D3DStuff.pCBObject ));

	DX11Helper::LoadBuffer<cBuffer::cbInfo>(this->D3DStuff.pd3dDevice, &( this->D3DStuff.pCBInfo ));
	this->D3DStuff.pImmediateContext->VSSetConstantBuffers(1, 1, &( this->D3DStuff.pCBInfo ));
	this->D3DStuff.pImmediateContext->PSSetConstantBuffers(1, 1, &( this->D3DStuff.pCBInfo ));

	DX11Helper::LoadBuffer<cBuffer::cbLight>(this->D3DStuff.pd3dDevice, &( this->D3DStuff.pCBLight ));
	this->D3DStuff.pImmediateContext->VSSetConstantBuffers(2, 1, &( this->D3DStuff.pCBLight ));
	this->D3DStuff.pImmediateContext->PSSetConstantBuffers(2, 1, &( this->D3DStuff.pCBLight ));

	Light::GetInstance().Init();

	this->D3DStuff.IsInitialized = true;
}


void GraphicManager::InsertObjectDrawable(std::shared_ptr<Drawable> obj)
{
	this->objectDrawables[obj->ID] = obj;
}
void GraphicManager::RemoveObjectDrawable(std::string ID)
{
	auto iter = this->objectDrawables.find(ID);
	if(iter != this->objectDrawables.end())
	{
		this->objectDrawables.erase(iter);
	}
}
const std::hash_map<std::string, std::shared_ptr<Drawable>> GraphicManager::AllObjectDrawables()
{
	return this->objectDrawables;
}

void GraphicManager::InsertTexture(std::shared_ptr<BasicTexture> obj)
{
	this->textures[obj->ID] = obj;
}
void GraphicManager::RemoveTexture(std::string ID)
{
	auto iter = this->textures.find(ID);
	if(iter != this->textures.end())
	{
		this->textures.erase(iter);
	}
}
const std::hash_map<std::string, std::shared_ptr<BasicTexture>> GraphicManager::AllTexture()
{
	return this->textures;
}

void GraphicManager::InsertContinuousScreenCapture(std::shared_ptr<ContinuousScreenShot> obj)
{
	this->ContinuousScreenCaptures[obj->ID] = obj;
}
void GraphicManager::RemoveContinuousScreenCapture(std::string ID)
{
	auto iter = this->ContinuousScreenCaptures.find(ID);
	if(iter != this->ContinuousScreenCaptures.end())
	{
		this->ContinuousScreenCaptures.erase(iter);
	}
}
const std::hash_map<std::string, std::shared_ptr<ContinuousScreenShot>> GraphicManager::AllContinuousScreenCapture()
{
	return this->ContinuousScreenCaptures;
}


void GraphicManager::InsertSceneFilter(std::shared_ptr<SceneFilter> obj)
{
	this->sceneFilters[obj->ID] = obj;
}
void GraphicManager::RemoveSceneFilter(std::string ID)
{
	auto iter = this->sceneFilters.find(ID);
	if(iter != this->sceneFilters.end())
	{
		this->sceneFilters.erase(iter);
	}
}
const std::hash_map<std::string, std::shared_ptr<SceneFilter>> GraphicManager::AllSceneFilters()
{
	return this->sceneFilters;
}