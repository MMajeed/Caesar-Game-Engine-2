#include "DepthTexture.h"

#include "GraphicManager.h"
#include "DX11Helper.h"

DepthTexture::DepthTexture(const std::string& inputID)
: Texture(inputID)
{
	this->D3DInfo.mDepthMapSRV = 0;
	this->D3DInfo.mDepthMapDSV = 0;
	this->D3DInfo.slot = 0;
}
void DepthTexture::Init()
{
	auto d3dStuff = GraphicManager::GetInstance().direct3d;

	this->D3DInfo.mViewport.TopLeftX = 0.0f;
	this->D3DInfo.mViewport.TopLeftY = 0.0f;
	this->D3DInfo.mViewport.Width    = this->D3DInfo.widthSize;
	this->D3DInfo.mViewport.Height   = this->D3DInfo.heightSize;
	this->D3DInfo.mViewport.MinDepth = 0.0f;
	this->D3DInfo.mViewport.MaxDepth = 1.0f;

	// Use typeless format because the DSV is going to interpret
	// the bits as DXGI_FORMAT_D24_UNORM_S8_UINT, whereas the SRV is going to interpret
	// the bits as DXGI_FORMAT_R24_UNORM_X8_TYPELESS.
	D3D11_TEXTURE2D_DESC texDesc;
	texDesc.Width = this->D3DInfo.widthSize;
	texDesc.Height = this->D3DInfo.heightSize;
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
	if (hr)
	{
		throw std::exception("Error creating 2d texture for shadow");
	}

	D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc;
	dsvDesc.Flags = 0;
	dsvDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	dsvDesc.Texture2D.MipSlice = 0;
	hr = d3dStuff.pd3dDevice->CreateDepthStencilView(depthMap, &dsvDesc, &(this->D3DInfo.mDepthMapDSV));
	if (hr)
	{
		throw std::exception("Error creating 2d texture for shadow");
	}

	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	srvDesc.Format = DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = texDesc.MipLevels;
	srvDesc.Texture2D.MostDetailedMip = 0;
	hr = d3dStuff.pd3dDevice->CreateShaderResourceView(depthMap, &srvDesc, &(this->D3DInfo.mDepthMapSRV));
	if (hr)
	{
		throw std::exception("Error creating 2d texture for shadow");
	}
	// View saves a reference to the texture so we can release our reference.
	depthMap->Release();
}
void DepthTexture::Destory()
{
	this->D3DInfo.mDepthMapDSV->Release();
	this->D3DInfo.mDepthMapSRV->Release();
}
void DepthTexture::SettupTexture()
{
	ID3D11DeviceContext* pImmediateContext = GraphicManager::GetInstance().direct3d.pImmediateContext;

	if (this->D3DInfo.slot > 0)
	{
		pImmediateContext->PSSetShaderResources(this->D3DInfo.slot, 1, &(this->D3DInfo.mDepthMapSRV));
	}
}
void DepthTexture::CleanupTexture()
{
	if (this->D3DInfo.slot > 0)
	{
		ID3D11DeviceContext* pImmediateContext = GraphicManager::GetInstance().direct3d.pImmediateContext;

		ID3D11ShaderResourceView* tab = NULL;

		pImmediateContext->PSSetShaderResources(this->D3DInfo.slot, 1, &tab);
	}
}
void DepthTexture::Update(double realTime, double deltaTime)
{

}
std::shared_ptr<DepthTexture> DepthTexture::Spawn(const std::string& inputID, int slot, const std::string& fileName)
{
	std::shared_ptr<DepthTexture> newTexture(new DepthTexture(inputID));
	newTexture->D3DInfo.slot = slot;
	newTexture->Init();
	return newTexture;
}