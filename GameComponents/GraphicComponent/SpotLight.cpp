#include "SpotLight.h"
#include "GraphicManager.h"
#include <3DMath.h>
#include <Keys.h>
#include <XNAConverter.h>

SpotLight::SpotLight()
{
	static const int imageSize = 2048;

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

void SpotLight::GenerateShadowTexture(TypedefObject::ObjectInfo& light,
										    TypedefObject::ObjectVector& objects)
{
	GraphicManager& graphicManager = GraphicManager::GetInstance();

	CHL::Matrix4x4 oldViewMatrix = graphicManager.CamerMatrix;
	CHL::Matrix4x4 oldPrespectiveMatrix = graphicManager.PrespectiveMatrix;

	graphicManager.CamerMatrix = this->GetViewMatrix(light);
	graphicManager.PrespectiveMatrix = this->GetPrespectiveMatrix(light);

	this->Draw(objects);

	graphicManager.CamerMatrix = oldViewMatrix;
	graphicManager.PrespectiveMatrix = oldPrespectiveMatrix;
}

void SpotLight::Draw(TypedefObject::ObjectVector& objects)
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

cBuffer::CLightDesc SpotLight::GetLightDesc(TypedefObject::ObjectInfo& lightInfo)
{
	CHL::Vec4& diffuse = GenericObject<CHL::Vec4>::GetValue(lightInfo.find(Keys::Light::DIFFUSE)->second);
	CHL::Vec4& ambient = GenericObject<CHL::Vec4>::GetValue(lightInfo.find(Keys::Light::AMBIENT)->second);
	CHL::Vec4& specular = GenericObject<CHL::Vec4>::GetValue(lightInfo.find(Keys::Light::SPECULAR)->second);
	CHL::Vec4& position = GenericObject<CHL::Vec4>::GetValue(lightInfo.find(Keys::Light::POSITION)->second);
	double range = GenericObject<double>::GetValue(lightInfo.find(Keys::Light::RANGE)->second);
	CHL::Vec4& direction = GenericObject<CHL::Vec4>::GetValue(lightInfo.find(Keys::Light::DIRECTION)->second);
	double spot = GenericObject<double>::GetValue(lightInfo.find(Keys::Light::SPOT)->second);
	CHL::Vec4& att = GenericObject<CHL::Vec4>::GetValue(lightInfo.find(Keys::Light::ATTENUATION)->second);

	cBuffer::CLightDesc light;
	light.material.diffuse = CHL::ConvertVec4(diffuse);
	light.material.ambient = CHL::ConvertVec4(ambient);
	light.material.specular = CHL::ConvertVec4(specular);
	light.pos = CHL::ConvertVec4(position);
	light.range = (float)range;
	light.dir = CHL::ConvertVec4(direction);
	light.spot = (float)spot;
	light.attenuation = CHL::ConvertVec4(att);
	light.type = 3;
	return light;
}

CHL::Matrix4x4 SpotLight::GetViewMatrix(TypedefObject::ObjectInfo& light)
{
	CHL::Vec4 vEye;
	CHL::Vec4 vT;
	CHL::Vec4 vUp;
	double pitch; double yaw; double roll;

	vEye = GenericObject<CHL::Vec4>::GetValue(light[Keys::Light::POSITION]);
	vT(0) = 0.0; vT(1) = 0.0; vT(2) = 1.0; vT(3) = 0.0;
	vUp(0) = 0.0; vUp(1) = 1.0; vUp(2) = 0.0; vUp(3) = 0.0;

	pitch = GenericObject<CHL::Vec4>::GetValue(light[Keys::Light::DIRECTION])(0);
	yaw = GenericObject<CHL::Vec4>::GetValue(light[Keys::Light::DIRECTION])(1);
	roll = GenericObject<CHL::Vec4>::GetValue(light[Keys::Light::DIRECTION])(2);

	return CHL::ViewCalculation(vEye, vT, vUp, pitch, yaw, roll);
}
CHL::Matrix4x4 SpotLight::GetPrespectiveMatrix(TypedefObject::ObjectInfo& light)
{
	double FovAngleY = 1.570796327; 
	double height = 2048;
	double width = 2048;
	double nearZ = 1.0;
	double farZ = GenericObject<double>::GetValue(light.find(Keys::Light::RANGE)->second);

	return CHL::PerspectiveFovLHCalculation(FovAngleY, height/width, nearZ, farZ);
}