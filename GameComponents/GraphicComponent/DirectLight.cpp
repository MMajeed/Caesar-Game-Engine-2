#include "DirectLight.h"
#include "GraphicManager.h"
#include <3DMath.h>
#include <Keys.h>
#include <XNAConverter.h>

static const float radius = 100.0f;

DirectLight::DirectLight()
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

void DirectLight::GenerateShadowTexture(TypedefObject::ObjectInfo& light,
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

void DirectLight::Draw(TypedefObject::ObjectVector& objects)
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

cBuffer::CLightDesc DirectLight::GetLightDesc(TypedefObject::ObjectInfo& lightInfo)
{
	CHL::Vec4& diffuse = GenericObject<CHL::Vec4>::GetValue(lightInfo.find(Keys::DIFFUSE)->second);
	CHL::Vec4& ambient = GenericObject<CHL::Vec4>::GetValue(lightInfo.find(Keys::AMBIENT)->second);
	CHL::Vec4& specular = GenericObject<CHL::Vec4>::GetValue(lightInfo.find(Keys::SPECULAR)->second);
	CHL::Vec4& direction = GenericObject<CHL::Vec4>::GetValue(lightInfo.find(Keys::DIRECTION)->second);

	cBuffer::CLightDesc light;
	light.material.diffuse = CHL::ConvertVec4(diffuse);
	light.material.ambient = CHL::ConvertVec4(ambient);
	light.material.specular = CHL::ConvertVec4(specular);
	light.dir = CHL::ConvertVec4(direction);
	light.type = 1;
	return light;
}

CHL::Matrix4x4 DirectLight::GetViewMatrix(TypedefObject::ObjectInfo& light)
{
	double pitch; double yaw; double roll;

	pitch = GenericObject<CHL::Vec4>::GetValue(light[Keys::DIRECTION])(0);
	yaw = GenericObject<CHL::Vec4>::GetValue(light[Keys::DIRECTION])(1);
	roll = GenericObject<CHL::Vec4>::GetValue(light[Keys::DIRECTION])(2);

	XMFLOAT3 dir((float)pitch, (float)yaw, (float)roll);
	XMFLOAT3 center(0.0f, 0.0f, 0.0f);

	XMVECTOR lightDir = XMLoadFloat3(&dir);
	XMVECTOR lightPos = radius*lightDir;
	XMVECTOR targetPos = XMLoadFloat3(&center);
	XMVECTOR up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	XMMATRIX V = XMMatrixLookAtLH(lightPos, targetPos, up);
	V = XMMatrixTranspose(V);

	XMFLOAT4X4 vFloat4x4;
	XMStoreFloat4x4(&vFloat4x4, V); 
	return CHL::Convert4x4(vFloat4x4);
}
CHL::Matrix4x4 DirectLight::GetPrespectiveMatrix(TypedefObject::ObjectInfo& light)
{
	double pitch; double yaw; double roll;

	pitch = GenericObject<CHL::Vec4>::GetValue(light[Keys::DIRECTION])(0);
	yaw = GenericObject<CHL::Vec4>::GetValue(light[Keys::DIRECTION])(1);
	roll = GenericObject<CHL::Vec4>::GetValue(light[Keys::DIRECTION])(2);

	XMFLOAT3 dir((float)pitch, (float)yaw, (float)roll);
	XMFLOAT3 center(0.0f, 0.0f, 0.0f);

	XMVECTOR lightDir = XMLoadFloat3(&dir);
	XMVECTOR lightPos = radius*lightDir;
	XMVECTOR targetPos = XMLoadFloat3(&center);
	XMVECTOR up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	XMMATRIX V = XMMatrixLookAtLH(lightPos, targetPos, up);

	// Transform bounding sphere to light space.
	XMFLOAT3 sphereCenterLS;
	XMStoreFloat3(&sphereCenterLS, XMVector3TransformCoord(targetPos, V));
		
	// Ortho frustum in light space encloses scene.
	float l = sphereCenterLS.x - radius;
	float b = sphereCenterLS.y - radius;
	float n = sphereCenterLS.z - radius;
	float r = sphereCenterLS.x + radius;
	float t = sphereCenterLS.y + radius;
	float f = sphereCenterLS.z + radius;
	XMMATRIX P = XMMatrixOrthographicOffCenterLH(l, r, b, t, n, f);

	P = XMMatrixTranspose(P);

	XMFLOAT4X4 pFloat4x4;
	XMStoreFloat4x4(&pFloat4x4, P); 
	return CHL::Convert4x4(pFloat4x4);
}
