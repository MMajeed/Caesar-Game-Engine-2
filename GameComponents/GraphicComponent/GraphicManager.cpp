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
#include "Scene.h"
#include "SceneInfo.h"
GraphicManager::GraphicManager()
{
	this->D3DStuff.pd3dDevice = 0;
	this->D3DStuff.pImmediateContext = 0;
	this->D3DStuff.pSwapChain = 0;
	this->D3DStuff.pRenderTargetView = 0;
	this->D3DStuff.pDepthStencilBuffer = 0;
	this->D3DStuff.pDepthStencilState = 0;
	this->D3DStuff.pDepthStencilView = 0;
	this->D3DStuff.IsInitialized = false;
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

	std::string window = ImportantIDConfig::WindowINFOID::Get();
	if(window.empty()){ throw std::invalid_argument("Windows Information is not set"); }
	std::hash_map<std::string, SP_INFO>::iterator iter = objects.find(window);
	if(iter == objects.cend()) { throw std::invalid_argument("Could not find windows Info"); }
	std::shared_ptr<WindowINFO> windowInfo = std::dynamic_pointer_cast<WindowINFO>(iter->second);

	std::string camera = ImportantIDConfig::CameraID::Get();
	std::hash_map<std::string, SP_INFO>::iterator cameraIter = objects.find(camera);
	std::shared_ptr<CameraINFO> cameraObj;
	if(cameraIter != objects.cend()) { cameraObj = std::dynamic_pointer_cast<CameraINFO>(cameraIter->second); }

	SceneInfo s = Scene::SetupScene(cameraObj, windowInfo->Width, windowInfo->Height);
	Light::GetInstance().SetupLight(objects, s.Eye);
	this->RunAllCapture(objects);
	Scene::SetupConstantBuffer(s);
	Scene::ClearScreen(s);
	auto vecObj = Scene::FilterScene(objects, s);
	Scene::DrawObjects(vecObj, s);

	// Present the information rendered to the back buffer to the front buffer (the screen)
	this->D3DStuff.pSwapChain->Present(0, 0);
}

void GraphicManager::Shutdown()
{

}

void GraphicManager::RunAllCapture(std::hash_map<std::string, SP_INFO>& objects)
{
	for(auto iter = this->ScreenCaptures.begin();
		iter != this->ScreenCaptures.end();
		++iter)
	{
		iter->second->Snap(objects);
	}
}

void GraphicManager::InitDevice()
{
	std::hash_map<std::string, SP_INFO> objects = EntityConfig::GetAllEntity();

	std::string window = ImportantIDConfig::WindowINFOID::Get();
	if(window.empty()){ throw std::invalid_argument("Windows Information is not set"); }

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

	DX11Helper::LoadBuffer<cBuffer::cbObject>(this->D3DStuff.pd3dDevice, &(this->D3DStuff.pCBObject));
	this->D3DStuff.pImmediateContext->VSSetConstantBuffers(0, 1, &(this->D3DStuff.pCBObject));
	this->D3DStuff.pImmediateContext->PSSetConstantBuffers(0, 1, &(this->D3DStuff.pCBObject));
	this->D3DStuff.pImmediateContext->GSSetConstantBuffers(0, 1, &(this->D3DStuff.pCBObject));

	DX11Helper::LoadBuffer<cBuffer::cbInfo>(this->D3DStuff.pd3dDevice, &(this->D3DStuff.pCBInfo));
	this->D3DStuff.pImmediateContext->VSSetConstantBuffers(1, 1, &(this->D3DStuff.pCBInfo));
	this->D3DStuff.pImmediateContext->PSSetConstantBuffers(1, 1, &(this->D3DStuff.pCBInfo));
	this->D3DStuff.pImmediateContext->GSSetConstantBuffers(1, 1, &(this->D3DStuff.pCBInfo));

	DX11Helper::LoadBuffer<cBuffer::cbLight>(this->D3DStuff.pd3dDevice, &(this->D3DStuff.pCBLight));
	this->D3DStuff.pImmediateContext->VSSetConstantBuffers(2, 1, &(this->D3DStuff.pCBLight));
	this->D3DStuff.pImmediateContext->PSSetConstantBuffers(2, 1, &(this->D3DStuff.pCBLight));
	this->D3DStuff.pImmediateContext->GSSetConstantBuffers(2, 1, &(this->D3DStuff.pCBLight));

	DX11Helper::LoadBuffer<cBuffer::cbShadows>(this->D3DStuff.pd3dDevice, &(this->D3DStuff.pCBShadow));
	this->D3DStuff.pImmediateContext->VSSetConstantBuffers(3, 1, &(this->D3DStuff.pCBShadow));
	this->D3DStuff.pImmediateContext->PSSetConstantBuffers(3, 1, &(this->D3DStuff.pCBShadow));
	this->D3DStuff.pImmediateContext->GSSetConstantBuffers(3, 1, &(this->D3DStuff.pCBShadow));

	Light::GetInstance().Init();

	this->D3DStuff.IsInitialized = true;
}


void GraphicManager::InsertObjectDrawable(const std::string& ID, std::shared_ptr<Drawable> obj)
{
	this->objectDrawables[ID] = obj;
}
void GraphicManager::RemoveObjectDrawable(const std::string& ID)
{
	auto iter = this->objectDrawables.find(ID);
	if(iter != this->objectDrawables.end())
	{
		iter->second->Destory();
		this->objectDrawables.erase(iter);
	}
}
const std::hash_map<std::string, std::shared_ptr<Drawable>> GraphicManager::AllObjectDrawables()
{
	return this->objectDrawables;
}

void GraphicManager::InsertTexture(const std::string& ID, std::shared_ptr<BasicTexture> obj)
{
	this->textures[ID] = obj;
}
void GraphicManager::RemoveTexture(const std::string& ID)
{
	auto iter = this->textures.find(ID);
	if(iter != this->textures.end())
	{
		iter->second->Destory();
		this->textures.erase(iter);
	}
}
const std::hash_map<std::string, std::shared_ptr<BasicTexture>> GraphicManager::AllTexture()
{
	return this->textures;
}

void GraphicManager::InsertScreenCapture(const std::string& ID, std::shared_ptr<ScreenCapture> obj)
{
	this->ScreenCaptures[ID] = obj;
}
void GraphicManager::RemoveScreenCapture(const std::string& ID)
{
	auto iter = this->ScreenCaptures.find(ID);
	if(iter != this->ScreenCaptures.end())
	{
		iter->second->Destory();
		this->ScreenCaptures.erase(iter);
	}
}
const std::hash_map<std::string, std::shared_ptr<ScreenCapture>> GraphicManager::AllScreenCapture()
{
	return this->ScreenCaptures;
}

