#include "DepthScreenShot.h"
#include "GraphicManager.h"
#include <Object.h>
#include <GenerateGUID.h>
#include "Scene.h"
#include <Logger.h>

DepthScreenShot::DepthScreenShot()
{
	this->pScreenTexture.resize(1);
}

void DepthScreenShot::Init()
{
	GraphicManager& graphic = GraphicManager::GetInstance();
	auto& d3dStuff = graphic.D3DStuff;

	// Use typeless format because the DSV is going to interpret
	// the bits as DXGI_FORMAT_D24_UNORM_S8_UINT, whereas the SRV is going to interpret
	// the bits as DXGI_FORMAT_R24_UNORM_X8_TYPELESS.
	D3D11_TEXTURE2D_DESC texDesc;
	texDesc.Width     = this->width;
	texDesc.Height    = this->height;
	texDesc.MipLevels = 1;
	texDesc.ArraySize = 1;
	texDesc.Format    = DXGI_FORMAT_R24G8_TYPELESS;
	texDesc.SampleDesc.Count   = 1;  
	texDesc.SampleDesc.Quality = 0;  
	texDesc.Usage          = D3D11_USAGE_DEFAULT;
	texDesc.BindFlags      = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;
	texDesc.CPUAccessFlags = 0; 
	texDesc.MiscFlags      = 0;

	ID3D11Texture2D* depthMap = 0;
	HRESULT hr = d3dStuff.pd3dDevice->CreateTexture2D(&texDesc, 0, &depthMap);
	if(FAILED(hr)){ Logger::LogError("ErrorException creating 2d texture for shadow"); }

	D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc;
	dsvDesc.Flags = 0;
	dsvDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	dsvDesc.Texture2D.MipSlice = 0;
	ID3D11DepthStencilView* pTempDepthMapDSV;
	hr = d3dStuff.pd3dDevice->CreateDepthStencilView(depthMap, &dsvDesc, &pTempDepthMapDSV);
	if(FAILED(hr)){ Logger::LogError("ErrorException creating 2d texture for shadow"); }
	this->pDepthMapDSV = pTempDepthMapDSV;

	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	srvDesc.Format = DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = texDesc.MipLevels;
	srvDesc.Texture2D.MostDetailedMip = 0;
	ID3D11ShaderResourceView* pTempScreenTexture;
	hr = d3dStuff.pd3dDevice->CreateShaderResourceView(depthMap, &srvDesc, &pTempScreenTexture);
	if(FAILED(hr)){ Logger::LogError("ErrorException creating 2d texture for shadow"); }
	this->pScreenTexture[0] = pTempScreenTexture;

	// View saves a reference to the texture so we can release our reference.
	depthMap->Release();

	this->Viewport.TopLeftX = 0.0f;
	this->Viewport.TopLeftY = 0.0f;
	this->Viewport.Width = (FLOAT)this->width;
	this->Viewport.Height = (FLOAT)this->height;
	this->Viewport.MinDepth = 0.0f;
	this->Viewport.MaxDepth = 1.0f;
}
void DepthScreenShot::Snap()
{
	Scene::UpdateCameraEntities();
	Scene::UpdateDrawSettingsEntities();
	Scene::UpdateObjectEntities();

	const std::unordered_map<std::string, std::shared_ptr<GraphicObjectEntity>>& objects = Scene::GetAllObjectEntities();

	this->Snap(objects);
}
void DepthScreenShot::Snap(const std::unordered_map<std::string, std::shared_ptr<GraphicObjectEntity>>& list)
{
	GraphicManager& graphic = GraphicManager::GetInstance();

	auto camera = Scene::GetCamera(this->cameraID, this->width, this->height);
	auto drawSettings = Scene::GetDrawSettings(this->drawSettingsID);

	this->SetupSnapShot(camera, drawSettings, list);
	this->TakeScreenSnapShot(camera, drawSettings, list);
	this->CleanupSnapShot(camera, drawSettings, list);
}

void DepthScreenShot::SetupSnapShot(std::shared_ptr<GraphicCameraEntity> Camera, std::shared_ptr<GraphicDrawSettingsEntity> drawSettings, const std::unordered_map<std::string, std::shared_ptr<GraphicObjectEntity>>& list)
{
	GraphicManager& graphic = GraphicManager::GetInstance();
	auto d3dStuff = graphic.D3DStuff;

	d3dStuff.pImmediateContext->RSSetViewports(1, &this->Viewport);

	// Set null render target because we are only going to draw to depth buffer.
	// Setting a null render target will disable color writes.
	ID3D11RenderTargetView* renderTargets[1] = {0};
	d3dStuff.pImmediateContext->OMSetRenderTargets(1, renderTargets, this->pDepthMapDSV);
	d3dStuff.pImmediateContext->ClearDepthStencilView(this->pDepthMapDSV, D3D11_CLEAR_DEPTH, 1.0f, 0);
}
void DepthScreenShot::TakeScreenSnapShot(std::shared_ptr<GraphicCameraEntity> Camera, std::shared_ptr<GraphicDrawSettingsEntity> drawSettings, const std::unordered_map<std::string, std::shared_ptr<GraphicObjectEntity>>& list)
{
	GraphicManager& graphic = GraphicManager::GetInstance();

	Scene::DrawObjects(Camera, drawSettings, list);
}
void DepthScreenShot::CleanupSnapShot(std::shared_ptr<GraphicCameraEntity> Camera, std::shared_ptr<GraphicDrawSettingsEntity> drawSettings, const std::unordered_map<std::string, std::shared_ptr<GraphicObjectEntity>>& list)
{
	GraphicManager& graphic = GraphicManager::GetInstance();
	auto& d3dStuff = graphic.D3DStuff;

	d3dStuff.pImmediateContext->GenerateMips(this->pScreenTexture[0]);
}

std::shared_ptr<DepthScreenShot> DepthScreenShot::Spawn(unsigned int width,
														unsigned int height,
														const std::string& cameraID,
														const std::string& drawSettingsID)
{
	std::shared_ptr<DepthScreenShot> newObject(new DepthScreenShot());
	newObject->cameraID = cameraID;
	newObject->drawSettingsID = drawSettingsID;
	newObject->width = width;
	newObject->height = height;

	newObject->Init();

	return newObject;
}
std::shared_ptr<ScreenShot> DepthScreenShot::clone() const
{
	std::shared_ptr<DepthScreenShot> newObject(new DepthScreenShot(*this));
	newObject->Init();

	return newObject;
}
