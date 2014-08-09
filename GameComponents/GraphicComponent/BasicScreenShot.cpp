#include "BasicScreenShot.h"
#include "GraphicManager.h"
#include <Object.h>
#include "Scene.h"
#include <Logger.h>

BasicScreenShot::BasicScreenShot()
{
}
void BasicScreenShot::Init()
{
	GraphicManager& graphic = GraphicManager::GetInstance();
	auto& d3dStuff = graphic.D3DStuff;

	ID3D11Texture2D* colorMap = 0;

	D3D11_TEXTURE2D_DESC texDesc;
	ZeroMemory(&texDesc, sizeof(texDesc));
	texDesc.Width = this->width;
	texDesc.Height = this->height;
	texDesc.MipLevels = 0;
	texDesc.ArraySize = 1;
	texDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	texDesc.SampleDesc.Count = 1;
	texDesc.SampleDesc.Quality = 0;
	texDesc.Usage = D3D11_USAGE_DEFAULT;
	texDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	texDesc.CPUAccessFlags = 0;
	texDesc.MiscFlags = D3D11_RESOURCE_MISC_GENERATE_MIPS;

	HRESULT hr;
	hr = d3dStuff.pd3dDevice->CreateTexture2D(&texDesc, 0, &colorMap);
	if(FAILED(hr)){ Logger::LogError("Failed at creating the texture 2d for the BasicScreenShot"); }

	// Null description means to create a view to all mipmap levels
	// using the format the texture was created with.
	ID3D11RenderTargetView*	pTempColorMapRTV;
	hr = d3dStuff.pd3dDevice->CreateRenderTargetView(colorMap, 0, &pTempColorMapRTV);
	if(FAILED(hr)){ Logger::LogError("Failed at creating render target view"); }
	this->pColorMapRTV = pTempColorMapRTV;

	ID3D11ShaderResourceView* pTempScreenTexture;
	hr = d3dStuff.pd3dDevice->CreateShaderResourceView(colorMap, 0, &pTempScreenTexture);
	if(FAILED(hr)){ Logger::LogError("Failed at creating shader resource view"); }
	this->pScreenTexture = pTempScreenTexture;

	// View saves a reference to the texture so we can release our reference.
	colorMap->Release();

	ID3D11Texture2D* depthMap = 0;
	ZeroMemory(&texDesc, sizeof(texDesc));
	texDesc.Width = this->width;
	texDesc.Height = this->height;
	texDesc.MipLevels = 1;
	texDesc.ArraySize = 1;
	texDesc.Format = DXGI_FORMAT_R32_TYPELESS;
	texDesc.SampleDesc.Count = 1;
	texDesc.SampleDesc.Quality = 0;
	texDesc.Usage = D3D11_USAGE_DEFAULT;
	texDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;

	texDesc.CPUAccessFlags = 0; 
	texDesc.MiscFlags = 0;

	hr = d3dStuff.pd3dDevice->CreateTexture2D(&texDesc, 0, &depthMap);
	if(FAILED(hr)){ Logger::LogError("Failed at creating shader resource view"); }

	D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc;
	ZeroMemory(&dsvDesc, sizeof(dsvDesc));
	dsvDesc.Format = DXGI_FORMAT_D32_FLOAT;
	dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	dsvDesc.Texture2D.MipSlice = 0;
	ID3D11DepthStencilView*	pTempDepthMapDSV;
	hr = d3dStuff.pd3dDevice->CreateDepthStencilView(depthMap, &dsvDesc, &pTempDepthMapDSV);
	if(FAILED(hr)){ Logger::LogError("Failed at creating shader resource view"); }
	this->pDepthMapDSV = pTempDepthMapDSV;

	this->Viewport.TopLeftX = 0.0f;
	this->Viewport.TopLeftY = 0.0f;
	this->Viewport.Width = (FLOAT)this->width;
	this->Viewport.Height = (FLOAT)this->height;
	this->Viewport.MinDepth = 0.0f;
	this->Viewport.MaxDepth = 1.0f;
}
void BasicScreenShot::Snap()
{
	const std::hash_map<std::string, std::shared_ptr<GraphicObjectEntity>>& objects = Scene::GetAllObjectEntities();
	this->Snap( objects);
}
void BasicScreenShot::Snap(const std::hash_map<std::string, std::shared_ptr<GraphicObjectEntity>>& list)
{
	GraphicManager& graphic = GraphicManager::GetInstance();

	auto camera = Scene::GetCamera(this->cameraID);

	this->SetupSnapShot(camera, list);
	this->TakeScreenSnapShot(camera, list);
	this->CleanupSnapShot(camera, list);
}

void BasicScreenShot::SetupSnapShot(const GraphicCameraEntity& Camera, const std::hash_map<std::string, std::shared_ptr<GraphicObjectEntity>>& list)
{
	GraphicManager& graphic = GraphicManager::GetInstance();
	auto& d3dStuff = graphic.D3DStuff;

	// Clear the back buffer 
	auto c = Camera.GetClearColor();
	d3dStuff.pImmediateContext->ClearRenderTargetView(this->pColorMapRTV, c.data());
	d3dStuff.pImmediateContext->ClearDepthStencilView(this->pDepthMapDSV, D3D11_CLEAR_DEPTH, 1.0f, 0);

	ID3D11RenderTargetView* renderTargets[1] = {this->pColorMapRTV};
	d3dStuff.pImmediateContext->OMSetRenderTargets(1, renderTargets, this->pDepthMapDSV);
	d3dStuff.pImmediateContext->RSSetViewports(1, &this->Viewport); 	
}
void BasicScreenShot::TakeScreenSnapShot(const GraphicCameraEntity& Camera, const std::hash_map<std::string, std::shared_ptr<GraphicObjectEntity>>& list)
{
	GraphicManager& graphic = GraphicManager::GetInstance();

	Scene::DrawObjects(Camera, list);
}
void BasicScreenShot::CleanupSnapShot(const GraphicCameraEntity& Camera, const std::hash_map<std::string, std::shared_ptr<GraphicObjectEntity>>& list)
{
	GraphicManager& graphic = GraphicManager::GetInstance();
	auto& d3dStuff = graphic.D3DStuff;

	d3dStuff.pImmediateContext->GenerateMips(this->pScreenTexture);
}

std::shared_ptr<BasicScreenShot> BasicScreenShot::Spawn(unsigned int width, unsigned int height, const std::string& cameraID)
{
	std::shared_ptr<BasicScreenShot> newObject(new BasicScreenShot());
	newObject->cameraID = cameraID;
	newObject->width = width;
	newObject->height = height;

	newObject->Init();

	return newObject;
}

std::shared_ptr<ScreenShot> BasicScreenShot::clone() const
{
	std::shared_ptr<BasicScreenShot> newObject(new BasicScreenShot(*this));
	newObject->Init();

	return newObject;
}