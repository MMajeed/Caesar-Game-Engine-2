#include "SpotLightShadow.h"
#include "GraphicManager.h"
#include <MathOperations.h>
#include <Keys.h>

void SpotLightShadow::Init()
{
	static const int imageSize = 1024;

	auto d3dStuff = GraphicManager::GetInstance().direct3d;

	mViewport.TopLeftX = 0.0f;
    mViewport.TopLeftY = 0.0f;
    mViewport.Width    = imageSize;
    mViewport.Height   = imageSize;
    mViewport.MinDepth = 0.0f;
    mViewport.MaxDepth = 1.0f;

	// Use typeless format because the DSV is going to interpret
	// the bits as DXGI_FORMAT_D24_UNORM_S8_UINT, whereas the SRV is going to interpret
	// the bits as DXGI_FORMAT_R24_UNORM_X8_TYPELESS.
	D3D11_TEXTURE2D_DESC texDesc;
    texDesc.Width     = imageSize;
    texDesc.Height    = imageSize;
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
	if(hr)
	{
		throw std::exception("Error creating 2d texture for shadow");
	}

    D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc;
	dsvDesc.Flags = 0;
    dsvDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
    dsvDesc.Texture2D.MipSlice = 0;
    hr = d3dStuff.pd3dDevice->CreateDepthStencilView(depthMap, &dsvDesc, &mDepthMapDSV);
	if(hr)
	{
		throw std::exception("Error creating 2d texture for shadow");
	}

    D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
    srvDesc.Format = DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
    srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    srvDesc.Texture2D.MipLevels = texDesc.MipLevels;
    srvDesc.Texture2D.MostDetailedMip = 0;
    hr = d3dStuff.pd3dDevice->CreateShaderResourceView(depthMap, &srvDesc, &mDepthMapSRV);
	if(hr)
	{
		throw std::exception("Error creating 2d texture for shadow");
	}
    // View saves a reference to the texture so we can release our reference.
	depthMap->Release();
}

void SpotLightShadow::GenerateShadowTexture(TypedefObject::ObjectInfo& light,
										    TypedefObject::ObjectVector& objects)
{
	GraphicManager& graphicManager = GraphicManager::GetInstance();

	boost::numeric::ublas::matrix<double> oldViewMatrix = graphicManager.CamerMatrix;
	boost::numeric::ublas::matrix<double> oldPrespectiveMatrix = graphicManager.PrespectiveMatrix;

	graphicManager.CamerMatrix = this->GetViewMatrix(light);
	graphicManager.PrespectiveMatrix = this->GetPrespectiveMatrix(light);

	this->Draw(objects);

	//graphicManager.CamerMatrix = oldViewMatrix;
	//graphicManager.PrespectiveMatrix = oldPrespectiveMatrix;
}

void SpotLightShadow::Draw(TypedefObject::ObjectVector& objects)
{
	auto d3dStuff = GraphicManager::GetInstance().direct3d;

	d3dStuff.pImmediateContext->RSSetViewports(1, &mViewport);

	// Set null render target because we are only going to draw to depth buffer.
	// Setting a null render target will disable color writes.
    ID3D11RenderTargetView* renderTargets[1] = {0};
    d3dStuff.pImmediateContext->OMSetRenderTargets(1, renderTargets, this->mDepthMapDSV);
    
    d3dStuff.pImmediateContext->ClearDepthStencilView(this->mDepthMapDSV, D3D11_CLEAR_DEPTH, 1.0f, 0);

	GraphicManager::GetInstance().SetupConstantBuffer(objects);
	GraphicManager::GetInstance().ClearScreen(objects);
	GraphicManager::GetInstance().DrawObjects(objects);

	d3dStuff.pImmediateContext->OMSetRenderTargets(1, &(d3dStuff.pRenderTargetView), d3dStuff.pDepthStencilView);	
	d3dStuff.pImmediateContext->RSSetViewports(1, &d3dStuff.vp);

	d3dStuff.pImmediateContext->PSSetShaderResources( 10, 1, &(this->mDepthMapSRV) );
}

boost::numeric::ublas::matrix<double> SpotLightShadow::GetViewMatrix(TypedefObject::ObjectInfo& light)
{
	boost::numeric::ublas::vector<double> vEye(4);
	boost::numeric::ublas::vector<double> vT(4);
	boost::numeric::ublas::vector<double> vUp(4);
	double pitch; double yaw; double roll;

	vEye = GenericObject<boost::numeric::ublas::vector<double>>::GetValue(light[Keys::POSITION]);
	vT(0) = 0.0; vT(1) = 0.0; vT(2) = 1.0; vT(3) = 0.0;
	vUp(0) = 0.0; vUp(1) = 1.0; vUp(2) = 0.0; vUp(3) = 0.0;

	pitch = GenericObject<boost::numeric::ublas::vector<double>>::GetValue(light[Keys::DIRECTION])(0);
	yaw = GenericObject<boost::numeric::ublas::vector<double>>::GetValue(light[Keys::DIRECTION])(1);
	roll = GenericObject<boost::numeric::ublas::vector<double>>::GetValue(light[Keys::DIRECTION])(2);

	return MathOperations::ViewCalculation(vEye, vT, vUp, pitch, yaw, roll);
}
boost::numeric::ublas::matrix<double> SpotLightShadow::GetPrespectiveMatrix(TypedefObject::ObjectInfo& light)
{
	double FovAngleY = 1.570796327; 
	double height = 1080;
	double width = 1080;
	double nearZ = 1.0;
	double farZ = GenericObject<double>::GetValue(light.find(Keys::RANGE)->second);

	return MathOperations::PerspectiveFovLHCalculation(FovAngleY, height/width, nearZ, farZ);
}
