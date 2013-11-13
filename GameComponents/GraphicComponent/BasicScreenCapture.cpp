#include "BasicScreenCapture.h"
#include "GraphicManager.h"
#include <Keys.h>
#include <Object.h>

BasicScreenCapture::BasicScreenCapture(const std::string& inputID)
: ScreenCapture(inputID)
{

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
		throw std::exception("Failed at creating the texture 2d for the Sniper");

	// Null description means to create a view to all mipmap levels
	// using the format the texture was created with.
	hr = d3dStuff.pd3dDevice->CreateRenderTargetView(colorMap, 0, &(this->D3DInfo.pColorMapRTV));
	if (FAILED(hr))
		throw std::exception("Failed at creating render target view");

	hr = d3dStuff.pd3dDevice->CreateShaderResourceView(colorMap, 0, &(this->D3DInfo.pColorMapSRV));
	if (FAILED(hr))
		throw std::exception("Failed at creating shader resource view");

	// View saves a reference to the texture so we can release our reference.
	colorMap->Release();

	this->D3DInfo.Viewport.TopLeftX = 0.0f;
	this->D3DInfo.Viewport.TopLeftY = 0.0f;
	this->D3DInfo.Viewport.Width = (FLOAT)this->D3DInfo.width;
	this->D3DInfo.Viewport.Height = (FLOAT)this->D3DInfo.height;
	this->D3DInfo.Viewport.MinDepth = 0.0f;
	this->D3DInfo.Viewport.MaxDepth = 1.0f;
}
void BasicScreenCapture::Destory()
{
	this->D3DInfo.pColorMapRTV->Release();
	this->D3DInfo.pColorMapSRV->Release();
}
void BasicScreenCapture::Update(double realTime, double deltaTime)
{

}
void BasicScreenCapture::Snap(TypedefObject::ObjectVector& objects, std::string cameraID, std::string prespectiveID)
{
	GraphicManager& graphic = GraphicManager::GetInstance();

	std::string currentCameraID = graphic.CameraKeyID;
	std::string currentPrespectiveID = graphic.PrespectiveKeyID;
	
	if(!cameraID.empty()){	graphic.CameraKeyID = cameraID;	}
	if(!prespectiveID.empty()){	graphic.PrespectiveKeyID = prespectiveID;	}

	this->SetupSnapShot(objects);
	this->TakeSnapShot(objects);
	this->CleanupSnapShot(objects);
	
	graphic.CameraKeyID = currentCameraID;
	graphic.PrespectiveKeyID = currentPrespectiveID;
}

void BasicScreenCapture::SetupSnapShot(TypedefObject::ObjectVector& objects)
{
	GraphicManager& graphic = GraphicManager::GetInstance();
	auto d3dStuff = graphic.D3DStuff;
	
	ID3D11RenderTargetView* renderTargets[1] = {this->D3DInfo.pColorMapRTV};
	d3dStuff.pImmediateContext->OMSetRenderTargets(1, renderTargets, d3dStuff.pDepthStencilView);

	d3dStuff.pImmediateContext->RSSetViewports(1, &this->D3DInfo.Viewport);

	float black[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
	d3dStuff.pImmediateContext->ClearRenderTargetView(this->D3DInfo.pColorMapRTV, black);
	d3dStuff.pImmediateContext->ClearDepthStencilView(d3dStuff.pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
}
void BasicScreenCapture::TakeSnapShot(TypedefObject::ObjectVector& objects)
{
	GraphicManager& graphic = GraphicManager::GetInstance();

	graphic.SetupLight(objects);
	graphic.SetupCameraNPrespective(objects);
	graphic.SetupConstantBuffer(objects);
	graphic.ClearScreen(objects);
	graphic.DrawObjects(objects);

	graphic.D3DStuff.pImmediateContext->GenerateMips(this->D3DInfo.pColorMapSRV);
}
void BasicScreenCapture::CleanupSnapShot(TypedefObject::ObjectVector& objects)
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