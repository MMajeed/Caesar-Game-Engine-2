#include "BasicScreenCapture.h"
#include "GraphicManager.h"
#include <Keys.h>
#include <Object.h>

BasicScreenCapture::BasicScreenCapture(const std::string& inputID)
: ScreenCapture(inputID)
{
	this->D3DInfo.pDepthMapDSV = 0;
	this->D3DInfo.pColorMapRTV = 0;
	this->pScreenTexture = 0;
}

void BasicScreenCapture::Init()
{
	GraphicManager& graphic = GraphicManager::GetInstance();
	auto d3dStuff = graphic. D3DStuff;

	ID3D11Texture2D* colorMap = 0;

	D3D11_TEXTURE2D_DESC texDesc;
	ZeroMemory(&texDesc, sizeof(texDesc));

	texDesc.Width = this->D3DInfo.width;
	texDesc.Height = this->D3DInfo.height;
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
	if (FAILED(hr))
		throw std::exception("Failed at creating the texture 2d for the BasicScreenCapture");

	// Null description means to create a view to all mipmap levels
	// using the format the texture was created with.
	hr = d3dStuff.pd3dDevice->CreateRenderTargetView(colorMap, 0, &(this->D3DInfo.pColorMapRTV));
	if (FAILED(hr))
		throw std::exception("Failed at creating render target view");

	hr = d3dStuff.pd3dDevice->CreateShaderResourceView(colorMap, 0, &(this->pScreenTexture));
	if (FAILED(hr))
		throw std::exception("Failed at creating shader resource view");

	// View saves a reference to the texture so we can release our reference.
	colorMap->Release();

	ID3D11Texture2D* depthMap = 0;
	ZeroMemory(&texDesc, sizeof(texDesc));

	texDesc.Width = this->D3DInfo.width;
	texDesc.Height = this->D3DInfo.height;
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
	if(FAILED(hr))
		throw std::exception("Failed at creating shader resource view");

	D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc;

	ZeroMemory(&dsvDesc, sizeof(dsvDesc));
	dsvDesc.Format = DXGI_FORMAT_D32_FLOAT;
	dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	dsvDesc.Texture2D.MipSlice = 0;

	hr = d3dStuff.pd3dDevice->CreateDepthStencilView(depthMap, &dsvDesc, &this->D3DInfo.pDepthMapDSV);
	if(FAILED(hr))
		throw std::exception("Failed at creating shader resource view");

	this->D3DInfo.Viewport.TopLeftX = 0.0f;
	this->D3DInfo.Viewport.TopLeftY = 0.0f;
	this->D3DInfo.Viewport.Width = (FLOAT)this->D3DInfo.width;
	this->D3DInfo.Viewport.Height = (FLOAT)this->D3DInfo.height;
	this->D3DInfo.Viewport.MinDepth = 0.0f;
	this->D3DInfo.Viewport.MaxDepth = 1.0f;
}
void BasicScreenCapture::Destory()
{
	if(this->D3DInfo.pDepthMapDSV != 0){ this->D3DInfo.pDepthMapDSV->Release(); }
	if(this->D3DInfo.pColorMapRTV != 0){ this->D3DInfo.pColorMapRTV->Release(); }
	if(this->pScreenTexture != 0){ this->pScreenTexture->Release(); }
	this->D3DInfo.pDepthMapDSV = 0;
	this->D3DInfo.pColorMapRTV = 0;
	this->pScreenTexture = 0;
}
void BasicScreenCapture::Update(double realTime, double deltaTime)
{

}
void BasicScreenCapture::Snap(std::hash_map<std::string, SP_INFO>& objects)
{
	GraphicManager& graphic = GraphicManager::GetInstance();

	auto currentSene = graphic.SceneInfo;

	this->SetupScene(objects);
	this->SetupSnapShot(objects);
	this->TakeScreenSnapShot(objects);
	this->CleanupSnapShot(objects);
	
	graphic.SceneInfo = currentSene;
}

void BasicScreenCapture::SetupScene(std::hash_map<std::string, SP_INFO>& objects)
{
	GraphicManager& graphic = GraphicManager::GetInstance();

	graphic.SceneInfo.CamerMatrix = this->D3DInfo.cameraMatrix;
	graphic.SceneInfo.PrespectiveMatrix = this->D3DInfo.prespectiveMatrix;
	double eyeX = this->D3DInfo.cameraMatrix[0][3] * -1.0;
	double eyeY = this->D3DInfo.cameraMatrix[1][3] * -1.0;
	double eyeZ = this->D3DInfo.cameraMatrix[2][3] * -1.0;
	double eyeW = this->D3DInfo.cameraMatrix[3][3] * -1.0;

	CHL::Vec4 eye{eyeX, eyeY, eyeZ, eyeW};
	graphic.SceneInfo.Eye = eye;
}
void BasicScreenCapture::SetupSnapShot(std::hash_map<std::string, SP_INFO>& objects)
{
	GraphicManager& graphic = GraphicManager::GetInstance();
	auto d3dStuff = graphic.D3DStuff;

	ID3D11RenderTargetView* renderTargets[1] = {this->D3DInfo.pColorMapRTV};
	d3dStuff.pImmediateContext->OMSetRenderTargets(1, renderTargets, this->D3DInfo.pDepthMapDSV);

	d3dStuff.pImmediateContext->RSSetViewports(1, &this->D3DInfo.Viewport);

	float black[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
	d3dStuff.pImmediateContext->ClearRenderTargetView(this->D3DInfo.pColorMapRTV, black);
	d3dStuff.pImmediateContext->ClearDepthStencilView(this->D3DInfo.pDepthMapDSV, D3D11_CLEAR_DEPTH, 1.0f, 0);
}
void BasicScreenCapture::TakeScreenSnapShot(std::hash_map<std::string, SP_INFO>& objects)
{
	GraphicManager& graphic = GraphicManager::GetInstance();

	graphic.SetupConstantBuffer(objects);
	graphic.DrawObjects(objects);

	graphic.D3DStuff.pImmediateContext->GenerateMips(this->pScreenTexture);
}
void BasicScreenCapture::CleanupSnapShot(std::hash_map<std::string, SP_INFO>& objects)
{
	GraphicManager& graphic = GraphicManager::GetInstance();
	auto d3dStuff = graphic.D3DStuff;
	
	d3dStuff.pImmediateContext->RSSetViewports(1, &d3dStuff.vp);
	
	d3dStuff.pImmediateContext->OMSetRenderTargets(1, &(d3dStuff.pRenderTargetView), d3dStuff.pDepthStencilView);
}

std::shared_ptr<BasicScreenCapture> BasicScreenCapture::Spawn(std::string id, unsigned int width, unsigned int height)
{
	std::shared_ptr<BasicScreenCapture> newObject(new BasicScreenCapture(id));

	newObject->D3DInfo.width = width;
	newObject->D3DInfo.height = height;

	newObject->Init();

	return newObject;
}

std::shared_ptr<ScreenCapture> BasicScreenCapture::clone() const
{
	std::shared_ptr<BasicScreenCapture> newObject(new BasicScreenCapture(*this));
	newObject->Init();

	return newObject;
}