#include "BasicScreenShot.h"
#include "GraphicManager.h"
#include <Object.h>
#include "Scene.h"
#include <Logger.h>

BasicScreenShot::BasicScreenShot()
{
	this->numberOfTargets = 1;
}
void BasicScreenShot::Init()
{
	GraphicManager& graphic = GraphicManager::GetInstance();
	auto& d3dStuff = graphic.D3DStuff;
	
	HRESULT hr;

	this->pScreenTexture.resize(this->numberOfTargets);
	this->pColorMapRTV.resize(this->numberOfTargets);

	std::vector<ID3D11Texture2D*> colorMap(this->numberOfTargets);

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

	
	for(unsigned int i = 0; i < this->numberOfTargets; ++i)
	{
		hr = d3dStuff.pd3dDevice->CreateTexture2D(&texDesc, 0, &colorMap[i]);
		if(FAILED(hr)){ Logger::LogError("Failed at creating the texture 2d for the BasicScreenShot"); }
	}

	for(unsigned int i = 0; i < this->numberOfTargets; ++i)
	{	
		// Null description means to create a view to all mipmap levels
		// using the format the texture was created with.
		ID3D11RenderTargetView*	pTempColorMapRTV;
		hr = d3dStuff.pd3dDevice->CreateRenderTargetView(colorMap[i], 0, &pTempColorMapRTV);
		if(FAILED(hr)){ Logger::LogError("Failed at creating render target view"); }
		this->pColorMapRTV[i] = pTempColorMapRTV;

	}

	for(unsigned int i = 0; i < this->numberOfTargets; ++i)
	{
		ID3D11ShaderResourceView* pTempScreenTexture;
		hr = d3dStuff.pd3dDevice->CreateShaderResourceView(colorMap[i], 0, &pTempScreenTexture);
		if(FAILED(hr)){ Logger::LogError("Failed at creating shader resource view"); }
		this->pScreenTexture[i] = pTempScreenTexture;
	}

	for(unsigned int i = 0; i < this->numberOfTargets; ++i)
	{
		// View saves a reference to the texture so we can release our reference.
		colorMap[i]->Release();
	}

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
	Scene::UpdateCameraEntities();
	Scene::UpdateObjectEntities();

	const std::unordered_map<std::string, std::shared_ptr<GraphicObjectEntity>>& objects = Scene::GetAllObjectEntities();
	this->Snap( objects);
}
void BasicScreenShot::Snap(const std::unordered_map<std::string, std::shared_ptr<GraphicObjectEntity>>& list)
{
	GraphicManager& graphic = GraphicManager::GetInstance();

	auto camera = Scene::GetCamera(this->cameraID, this->width, this->height);

	this->SetupSnapShot(camera, list);
	this->TakeScreenSnapShot(camera, list);
	this->CleanupSnapShot(camera, list);
}

void BasicScreenShot::SetupSnapShot(std::shared_ptr<GraphicCameraEntity> Camera, const std::unordered_map<std::string, std::shared_ptr<GraphicObjectEntity>>& list)
{
	GraphicManager& graphic = GraphicManager::GetInstance();
	auto& d3dStuff = graphic.D3DStuff;

	std::vector<ID3D11RenderTargetView*> renderTargets;

	auto c = Camera->GetClearColor();
	for(unsigned int i = 0; i < this->numberOfTargets; ++i)
	{
		if(Camera->GetClearScreen() == true)
		{
			// Clear the back buffer 
			d3dStuff.pImmediateContext->ClearRenderTargetView(this->pColorMapRTV[i], c.data());
		}
		renderTargets.push_back(this->pColorMapRTV[i]);
	}
	d3dStuff.pImmediateContext->ClearDepthStencilView(this->pDepthMapDSV, D3D11_CLEAR_DEPTH, 1.0f, 0);

	d3dStuff.pImmediateContext->OMSetRenderTargets(renderTargets.size(), renderTargets.data(), this->pDepthMapDSV);
	
	d3dStuff.pImmediateContext->RSSetViewports(1, &this->Viewport); 	
}
void BasicScreenShot::TakeScreenSnapShot(std::shared_ptr<GraphicCameraEntity> Camera, const std::unordered_map<std::string, std::shared_ptr<GraphicObjectEntity>>& list)
{
	GraphicManager& graphic = GraphicManager::GetInstance();

	Scene::DrawObjects(Camera, list);
}
void BasicScreenShot::CleanupSnapShot(std::shared_ptr<GraphicCameraEntity> Camera, const std::unordered_map<std::string, std::shared_ptr<GraphicObjectEntity>>& list)
{
	GraphicManager& graphic = GraphicManager::GetInstance();
	auto& d3dStuff = graphic.D3DStuff;

	for(unsigned int i = 0; i < this->numberOfTargets; ++i)
	{
		d3dStuff.pImmediateContext->GenerateMips(this->pScreenTexture[i]);
	}
}

std::shared_ptr<BasicScreenShot> BasicScreenShot::Spawn(unsigned int width, unsigned int height, unsigned int numberOfTargets, const std::string& cameraID)
{
	std::shared_ptr<BasicScreenShot> newObject(new BasicScreenShot());
	newObject->cameraID = cameraID;
	newObject->width = width;
	newObject->height = height;
	newObject->numberOfTargets = numberOfTargets;

	newObject->Init();

	return newObject;
}

std::shared_ptr<ScreenShot> BasicScreenShot::clone() const
{
	std::shared_ptr<BasicScreenShot> newObject(new BasicScreenShot(*this));
	newObject->Init();

	return newObject;
}