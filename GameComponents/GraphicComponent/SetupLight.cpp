#include "SetupLight.h"
#include <SpotLightINFO.h>
#include <DirectionalLightINFO.h>
#include <PointLightINFO.h>
#include "DirectLight.h"
#include "SpotLight.h"
#include "PointLight.h"
#include "GraphicManager.h"
#include <GenerateGUID.h>
#include <3DMath.h>
#include <XNAConverter.h>

cBuffer::cbLight LastLightInput;
cBuffer::cbShadows LastShadowInput;

Light::Light()
{
	this->shaderShadowTexture = 0;
	this->shadowTexture = 0;
}

void Light::Init()
{
}

void Light::SetupShadow(unsigned int numberOfShadows)
{
	for(auto iter = this->vecDepthShadow.begin();
		iter != this->vecDepthShadow.end();
		++iter)
	{
		(*iter)->Release();
		(*iter) = nullptr;
	}
	if(this->shaderShadowTexture != 0){ this->shaderShadowTexture->Release(); }
	if(this->shadowTexture != 0){ this->shadowTexture->Release(); }


	D3D11_TEXTURE2D_DESC sTexDesc;
	sTexDesc.Width = this->Width;
	sTexDesc.Height = this->Height;
	sTexDesc.MipLevels = 0;
	sTexDesc.ArraySize = numberOfShadows;
	sTexDesc.Format = DXGI_FORMAT_R24G8_TYPELESS;
	sTexDesc.SampleDesc.Count = 1;
	sTexDesc.SampleDesc.Quality = 0;
	sTexDesc.Usage = D3D11_USAGE_DEFAULT;
	sTexDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;
	sTexDesc.CPUAccessFlags = 0;
	sTexDesc.MiscFlags = 0;

	HRESULT hr = GraphicManager::GetInstance().D3DStuff.pd3dDevice->CreateTexture2D(&sTexDesc, NULL, &( this->shadowTexture ));
	if(FAILED(hr))
		throw std::runtime_error("Failed at creating texture array for shadows");

	this->vecDepthShadow.resize(numberOfShadows);
	unsigned int counter = 0;
	for(auto iter = this->vecDepthShadow.begin();
		iter != this->vecDepthShadow.end();
		++iter)
	{
		( *iter ) = ShadowScreenShot::Spawn(this->Width, this->Height, this->shadowTexture, counter, sTexDesc.ArraySize);
		++counter;
	}

	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	srvDesc.Format = DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2DARRAY;
	srvDesc.Texture2DArray.MipLevels = 1;
	srvDesc.Texture2DArray.ArraySize = sTexDesc.ArraySize;
	srvDesc.Texture2DArray.FirstArraySlice = 0;
	srvDesc.Texture2D.MostDetailedMip = 0;
	hr = GraphicManager::GetInstance().D3DStuff.pd3dDevice->CreateShaderResourceView(this->shadowTexture, &srvDesc, &this->shaderShadowTexture);
	if(FAILED(hr)){ throw std::runtime_error("Error creating 2d texture for shadow"); }
}

void Light::SetupLight(std::hash_map<std::string, SP_INFO>& objects, const CHL::Vec4& eye)
{
	GraphicManager& graphicManager = GraphicManager::GetInstance();
	//graphicManager.InsertSceneFilter(this->shadowFilter);

	std::vector<std::shared_ptr<LightINFO>> vecLights;
	for(auto iterObj = objects.begin();
		iterObj != objects.end();
		++iterObj)
	{
		std::shared_ptr<LightINFO> light = std::dynamic_pointer_cast<LightINFO>( iterObj->second );
		if(!light){ continue; }

		vecLights.push_back(light);
	}

	
	if(vecLights.size() > cBuffer::numOfLights)
	{
		std::sort(vecLights.begin(), vecLights.end(),
				  [eye](const std::shared_ptr<LightINFO>& a, const std::shared_ptr<LightINFO>& b) -> bool
					{
						float rankA = 0.0f; float rankB = 0.0f;

						if(std::shared_ptr<PointLightINFO> light = std::dynamic_pointer_cast<PointLightINFO>( a ))
						{
							rankA += CHL::Length(eye, light->Position);
						}
						else if(std::shared_ptr<SpotLightINFO> light = std::dynamic_pointer_cast<SpotLightINFO>( a ))
						{
							rankA += CHL::Length(eye, light->Position);
						}

						if(std::shared_ptr<PointLightINFO> light = std::dynamic_pointer_cast<PointLightINFO>( b ))
						{
							rankB += CHL::Length(eye, light->Position);
						}
						else if(std::shared_ptr<SpotLightINFO> light = std::dynamic_pointer_cast<SpotLightINFO>( b ))
						{
							rankB += CHL::Length(eye, light->Position);
						}

						return rankA < rankB;
					});
		vecLights.resize(cBuffer::numOfLights);
	}

	unsigned int numberOfShadows = 0;
	for(auto iterLight = vecLights.begin();
		iterLight != vecLights.end();
		++iterLight)
	{
		if((*iterLight)->HasShadow == true ){ ++numberOfShadows; }
	}
	if(numberOfShadows > this->vecDepthShadow.size())
	{
		this->SetupShadow(numberOfShadows);
	}

	cBuffer::cbLight lightBuffer;
	cBuffer::cbShadows shadows;
	ZeroMemory(&lightBuffer, sizeof(cBuffer::cbLight));
	ZeroMemory(&shadows, sizeof(cBuffer::cbShadows));
	unsigned int shadowCounter = 0;
	unsigned int counter = 0;
	for(auto iterLight = vecLights.begin();
		iterLight != vecLights.end();
		++iterLight, ++counter)
	{
		if(std::shared_ptr<DirectionalLightINFO> light = std::dynamic_pointer_cast<DirectionalLightINFO>( *iterLight ))
		{
			lightBuffer.lights[counter] = DirectLight::GetLightDesc(light);

			if(light->HasShadow == true && ( shadowCounter < this->vecDepthShadow.size() ))
			{
				this->vecDepthShadow[shadowCounter]->D3DInfo.scene = DirectLight::GetScene(light, eye);

				this->vecDepthShadow[shadowCounter]->Snap(objects);

				lightBuffer.lights[counter].shadowNum = shadowCounter;

				shadows.shadows[counter] = XMLoadFloat4x4(&CHL::Convert4x4(DirectLight::CalculateShadowMatrix(light, eye)));
				++shadowCounter;
			}
		}
		else if(std::shared_ptr<PointLightINFO> light = std::dynamic_pointer_cast<PointLightINFO>( *iterLight ))
		{
			lightBuffer.lights[counter] = PointLight::GetLightDesc(light);
		}
		else if(std::shared_ptr<SpotLightINFO> light = std::dynamic_pointer_cast<SpotLightINFO>( *iterLight ))
		{
			lightBuffer.lights[counter] = SpotLight::GetLightDesc(light);

			if(light->HasShadow == true && ( shadowCounter < this->vecDepthShadow.size() ))
			{
				this->vecDepthShadow[shadowCounter]->D3DInfo.scene = SpotLight::GetScene(light, eye);

				this->vecDepthShadow[shadowCounter]->Snap(objects);

				lightBuffer.lights[counter].shadowNum = shadowCounter;
				shadows.shadows[counter] = XMLoadFloat4x4(&CHL::Convert4x4(SpotLight::CalculateShadowMatrix(light, eye)));

				++shadowCounter;
			}
		}
	}
	
	int lightDifference = memcmp(&lightBuffer, &LastLightInput, sizeof(cBuffer::cbLight));
	if(lightDifference != 0)
	{
		ID3D11DeviceContext* pImmediateContext = graphicManager.D3DStuff.pImmediateContext;

		graphicManager.D3DStuff.pImmediateContext->UpdateSubresource(graphicManager.D3DStuff.pCBLight, 0, NULL, &lightBuffer, 0, 0);

		LastLightInput = lightBuffer;
	}
	int ShadowDifference = memcmp(&shadows, &LastShadowInput, sizeof(cBuffer::cbShadows));
	if(ShadowDifference != 0)
	{
		ID3D11DeviceContext* pImmediateContext = graphicManager.D3DStuff.pImmediateContext;

		graphicManager.D3DStuff.pImmediateContext->UpdateSubresource(graphicManager.D3DStuff.pCBShadow, 0, NULL, &shadows, 0, 0);

		LastShadowInput = shadows;
	}

	graphicManager.D3DStuff.pImmediateContext->PSSetShaderResources(100, 1, &(this->shaderShadowTexture));

	//graphicManager.RemoveSceneFilter(this->shadowFilter->ID);
}