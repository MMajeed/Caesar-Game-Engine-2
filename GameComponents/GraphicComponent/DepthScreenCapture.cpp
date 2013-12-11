#include "DepthScreenCapture.h"
#include "GraphicManager.h"
#include <Object.h>
#include <GenerateGUID.h>

DepthScreenCapture::DepthScreenCapture(const std::string& inputID)
: ScreenCapture(inputID)
{
	this->D3DInfo.pDepthMapDSV = 0;
	this->pScreenTexture = 0;
}

void DepthScreenCapture::Init()
{
	GraphicManager& graphic = GraphicManager::GetInstance();
	auto d3dStuff = graphic.D3DStuff;

	// Use typeless format because the DSV is going to interpret
	// the bits as DXGI_FORMAT_D24_UNORM_S8_UINT, whereas the SRV is going to interpret
	// the bits as DXGI_FORMAT_R24_UNORM_X8_TYPELESS.
	D3D11_TEXTURE2D_DESC texDesc;
	texDesc.Width     = this->D3DInfo.width;
	texDesc.Height    = this->D3DInfo.height;
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
void DepthScreenCapture::Destory()
{
	if(this->D3DInfo.pDepthMapDSV != 0){ this->D3DInfo.pDepthMapDSV->Release(); }
	if(this->pScreenTexture != 0){ this->pScreenTexture->Release(); }
	this->D3DInfo.pDepthMapDSV = 0;
	this->pScreenTexture = 0;
}
void DepthScreenCapture::Update(double realTime, double deltaTime)
{

}
void DepthScreenCapture::Snap(std::hash_map<std::string, SP_INFO>& objects)
{
	GraphicManager& graphic = GraphicManager::GetInstance();

	auto currentSene = graphic.SceneInfo;

	this->SetupScene(objects);
	this->SetupSnapShot(objects);
	this->TakeScreenSnapShot(objects);
	this->CleanupSnapShot(objects);

	graphic.SceneInfo = currentSene;
}

void DepthScreenCapture::SetupScene(std::hash_map<std::string, SP_INFO>& objects)
{
	GraphicManager& graphic = GraphicManager::GetInstance();
	graphic.SceneInfo.CamerMatrix = this->D3DInfo.cameraMatrix;
	graphic.SceneInfo.PrespectiveMatrix = this->D3DInfo.prespectiveMatrix;
	CHL::Vec4 eye{this->D3DInfo.cameraMatrix[0][3], this->D3DInfo.cameraMatrix[1][3], this->D3DInfo.cameraMatrix[2][3], this->D3DInfo.cameraMatrix[3][3]};

}
void DepthScreenCapture::SetupSnapShot(std::hash_map<std::string, SP_INFO>& objects)
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
void DepthScreenCapture::TakeScreenSnapShot(std::hash_map<std::string, SP_INFO>& objects)
{
	GraphicManager& graphic = GraphicManager::GetInstance();

	graphic.SetupConstantBuffer(objects);
	graphic.DrawObjects(objects);
}
void DepthScreenCapture::CleanupSnapShot(std::hash_map<std::string, SP_INFO>& objects)
{
	GraphicManager& graphic = GraphicManager::GetInstance();
	auto d3dStuff = graphic.D3DStuff;

	d3dStuff.pImmediateContext->OMSetRenderTargets(1, &(d3dStuff.pRenderTargetView), d3dStuff.pDepthStencilView);
	d3dStuff.pImmediateContext->RSSetViewports(1, &d3dStuff.vp);
}

std::shared_ptr<DepthScreenCapture> DepthScreenCapture::Spawn(std::string id, unsigned int width, unsigned int height)
{
	std::shared_ptr<DepthScreenCapture> newObject(new DepthScreenCapture(id));

	newObject->D3DInfo.width = width;
	newObject->D3DInfo.height = height;

	newObject->Init();

	return newObject;
}
std::shared_ptr<ScreenCapture> DepthScreenCapture::clone() const
{
	std::shared_ptr<DepthScreenCapture> newObject(new DepthScreenCapture(*this));
	newObject->Init();

	return newObject;
}
