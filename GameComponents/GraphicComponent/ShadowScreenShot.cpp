#include "ShadowScreenShot.h"
#include "GraphicManager.h"
#include <Object.h>
#include <GenerateGUID.h>
#include "Scene.h"
#include "ShadowFilter.h"

ShadowScreenShot::ShadowScreenShot()
{
	this->D3DInfo.pDepthMapDSV = 0;
	this->pScreenTexture = 0;
}

void ShadowScreenShot::Init()
{
	GraphicManager& graphic = GraphicManager::GetInstance();
	auto& d3dStuff = graphic.D3DStuff;

	// Use typeless format because the DSV is going to interpret
	// the bits as DXGI_FORMAT_D24_UNORM_S8_UINT, whereas the SRV is going to interpret
	// the bits as DXGI_FORMAT_R24_UNORM_X8_TYPELESS.
	D3D11_TEXTURE2D_DESC texDesc;
	texDesc.Width = this->D3DInfo.width;
	texDesc.Height = this->D3DInfo.height;
	texDesc.MipLevels = 1;
	texDesc.ArraySize = 1;
	texDesc.Format = DXGI_FORMAT_R24G8_TYPELESS;
	texDesc.SampleDesc.Count = 1;
	texDesc.SampleDesc.Quality = 0;
	texDesc.Usage = D3D11_USAGE_DEFAULT;
	texDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;
	texDesc.CPUAccessFlags = 0;
	texDesc.MiscFlags = 0;

	ID3D11Texture2D* depthMap = 0;
	HRESULT hr = d3dStuff.pd3dDevice->CreateTexture2D(&texDesc, 0, &depthMap);
	if(FAILED(hr)){ throw std::runtime_error("Error creating 2d texture for shadow"); }

	D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc;
	dsvDesc.Flags = 0;
	dsvDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	dsvDesc.Texture2D.MipSlice = 0;
	hr = d3dStuff.pd3dDevice->CreateDepthStencilView(depthMap, &dsvDesc, &this->D3DInfo.pDepthMapDSV);
	if(FAILED(hr)){ throw std::runtime_error("Error creating 2d texture for shadow"); }

	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	srvDesc.Format = DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = texDesc.MipLevels;
	srvDesc.Texture2D.MostDetailedMip = 0;
	hr = d3dStuff.pd3dDevice->CreateShaderResourceView(depthMap, &srvDesc, &this->pScreenTexture);
	if(FAILED(hr)){ throw std::runtime_error("Error creating 2d texture for shadow"); }

	// View saves a reference to the texture so we can release our reference.
	depthMap->Release();

	this->D3DInfo.Viewport.TopLeftX = 0.0f;
	this->D3DInfo.Viewport.TopLeftY = 0.0f;
	this->D3DInfo.Viewport.Width = (FLOAT)this->D3DInfo.width;
	this->D3DInfo.Viewport.Height = (FLOAT)this->D3DInfo.height;
	this->D3DInfo.Viewport.MinDepth = 0.0f;
	this->D3DInfo.Viewport.MaxDepth = 1.0f;
}
void ShadowScreenShot::Release()
{
	if(this->D3DInfo.pDepthMapDSV != 0){ this->D3DInfo.pDepthMapDSV->Release(); }
	if(this->pScreenTexture != 0){ this->pScreenTexture->Release(); }
	this->D3DInfo.pDepthMapDSV = 0;
	this->pScreenTexture = 0;
}
void ShadowScreenShot::Update(double realTime, double deltaTime)
{

}
void ShadowScreenShot::Snap(std::hash_map<std::string, SP_INFO>& objects)
{
	GraphicManager& graphic = GraphicManager::GetInstance();

	this->SetupSnapShot(objects);
	this->TakeScreenSnapShot(objects);
	this->CleanupSnapShot(objects);
}


void ShadowScreenShot::SetupSnapShot(std::hash_map<std::string, SP_INFO>& objects)
{
	GraphicManager& graphic = GraphicManager::GetInstance();
	auto d3dStuff = graphic.D3DStuff;

	d3dStuff.pImmediateContext->RSSetViewports(1, &this->D3DInfo.Viewport);

	// Set null render target because we are only going to draw to depth buffer.
	// Setting a null render target will disable color writes.
	ID3D11RenderTargetView* renderTargets[1] = {0};
	d3dStuff.pImmediateContext->OMSetRenderTargets(1, renderTargets, this->D3DInfo.pDepthMapDSV);
	d3dStuff.pImmediateContext->ClearDepthStencilView(this->D3DInfo.pDepthMapDSV, D3D11_CLEAR_DEPTH, 1.0f, 0);
}
void ShadowScreenShot::TakeScreenSnapShot(std::hash_map<std::string, SP_INFO>& objects)
{
	GraphicManager& graphic = GraphicManager::GetInstance();

	Scene::SetupConstantBuffer(this->D3DInfo.scene);
	std::vector<std::shared_ptr<ObjectINFO>> vecObj = Scene::FilterScene(objects, this->D3DInfo.scene);
	for(auto iter = vecObj.begin();
		iter != vecObj.end();
		++iter)
	{
		if(ShadowFilter::Filter(*iter))
		{
			auto drawableIter = graphic.objectDrawables.find((*iter)->DrawObjID);
			if(drawableIter == graphic.objectDrawables.end()){ continue; }// If it didn't fine then continue

			drawableIter->second->DrawShadow(*iter, this->D3DInfo.scene);
		}
	}
}
void ShadowScreenShot::CleanupSnapShot(std::hash_map<std::string, SP_INFO>& objects)
{
	GraphicManager& graphic = GraphicManager::GetInstance();
	auto d3dStuff = graphic.D3DStuff;

	d3dStuff.pImmediateContext->OMSetRenderTargets(1, &(d3dStuff.pRenderTargetView), d3dStuff.pDepthStencilView);
	d3dStuff.pImmediateContext->RSSetViewports(1, &d3dStuff.vp);
}

std::shared_ptr<ShadowScreenShot> ShadowScreenShot::Spawn(unsigned int width, unsigned int height, ID3D11Texture2D*& tex, unsigned int index, unsigned int arraySize)
{
	std::shared_ptr<ShadowScreenShot> newObject(new ShadowScreenShot());

	newObject->D3DInfo.width = width;
	newObject->D3DInfo.height = height;

	GraphicManager& graphic = GraphicManager::GetInstance();
	auto& d3dStuff = graphic.D3DStuff;

	D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc;
	ZeroMemory(&dsvDesc, sizeof(dsvDesc));
	dsvDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DARRAY;
	dsvDesc.Texture2DArray.ArraySize = 1;
	dsvDesc.Texture2DArray.FirstArraySlice = index;
	HRESULT hr = d3dStuff.pd3dDevice->CreateDepthStencilView(tex, &dsvDesc, &newObject->D3DInfo.pDepthMapDSV);
	if(FAILED(hr)){ throw std::runtime_error("Error creating 2d texture for shadow"); }


	newObject->D3DInfo.Viewport.TopLeftX = 0.0f;
	newObject->D3DInfo.Viewport.TopLeftY = 0.0f;
	newObject->D3DInfo.Viewport.Width = (FLOAT)newObject->D3DInfo.width;
	newObject->D3DInfo.Viewport.Height = (FLOAT)newObject->D3DInfo.height;
	newObject->D3DInfo.Viewport.MinDepth = 0.0f;
	newObject->D3DInfo.Viewport.MaxDepth = 1.0f;

	return newObject;
}
std::shared_ptr<ScreenShot> ShadowScreenShot::clone() const
{
	std::shared_ptr<ShadowScreenShot> newObject(new ShadowScreenShot(*this));
	newObject->Init();

	return newObject;
}
