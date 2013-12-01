#include "SetupLight.h"
#include <SpotLightINFO.h>
#include <DirectionalLightINFO.h>
#include <PointLightINFO.h>
#include "DirectLight.h"
#include "SpotLight.h"
#include "PointLight.h"
#include "GraphicManager.h"
#include <GenerateGUID.h>

cBuffer::cbLight LastLightInput;

Light::Light()
{
	this->shadowTexture = 0;
}

void Light::Init()
{
	D3D11_TEXTURE2D_DESC sTexDesc;
	sTexDesc.Width = this->Width;
	sTexDesc.Height = this->Height;
	sTexDesc.MipLevels = 0;
	sTexDesc.ArraySize = this->NumberOfShadows; 
	sTexDesc.Format = DXGI_FORMAT_R24G8_TYPELESS;
	sTexDesc.SampleDesc.Count = 1;
	sTexDesc.SampleDesc.Quality = 0;
	sTexDesc.Usage = D3D11_USAGE_DEFAULT;
	sTexDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;
	sTexDesc.CPUAccessFlags = 0;
	sTexDesc.MiscFlags = 0;

	HRESULT hr = GraphicManager::GetInstance().D3DStuff.pd3dDevice->CreateTexture2D(&sTexDesc, NULL, &(this->shadowTexture));
	if(FAILED(hr))
		throw std::exception("Failed at creating texture array for shadows");

	this->vecDepthShadow.resize(this->NumberOfShadows);
	unsigned int counter = 0;
	for(auto iter = this->vecDepthShadow.begin();
		iter != this->vecDepthShadow.end();
		++iter)
	{
		(*iter) = ShadowScreenCapture::Spawn(this->Width, this->Height, this->shadowTexture, counter, sTexDesc.ArraySize);
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
	if(FAILED(hr)){ throw std::exception("Error creating 2d texture for shadow"); }

	shadowFilter = ShadowFilter::Spawn(CHL::GenerateGUID());
}

void Light::SetupLight(std::hash_map<std::string, SP_INFO>& objects)
{
	GraphicManager& graphicManager = GraphicManager::GetInstance();
	graphicManager.InsertSceneFilter(this->shadowFilter);

	std::vector<cBuffer::CLightDesc> vecLightBuffer;
	unsigned int shadowCounter = 0;

	for(auto iterObj = objects.begin();
		iterObj != objects.end();
		++iterObj)
	{
		std::shared_ptr<LightINFO> light = std::dynamic_pointer_cast<LightINFO>(iterObj->second);

		if(light)
		{
			if(std::shared_ptr<DirectionalLightINFO> light = std::dynamic_pointer_cast<DirectionalLightINFO>(iterObj->second))
			{
				vecLightBuffer.push_back(DirectLight::GetLightDesc(light));

				if(light->HasShadow == true && (shadowCounter < this->vecDepthShadow.size()))
				{
					this->vecDepthShadow[shadowCounter]->D3DInfo.cameraMatrix = DirectLight::CalculateViewMatrix(light);
					this->vecDepthShadow[shadowCounter]->D3DInfo.prespectiveMatrix = DirectLight::CalculatePrespectiveMatrix(light);

					this->vecDepthShadow[shadowCounter]->Snap(objects);

					vecLightBuffer.back().shadowNum = shadowCounter;

					++shadowCounter;
				}
			}
			else if(std::shared_ptr<PointLightINFO> light = std::dynamic_pointer_cast<PointLightINFO>(iterObj->second))
			{
				vecLightBuffer.push_back(PointLight::GetLightDesc(light));
			}
			else if(std::shared_ptr<SpotLightINFO> light = std::dynamic_pointer_cast<SpotLightINFO>(iterObj->second))
			{
				vecLightBuffer.push_back(SpotLight::GetLightDesc(light));

				if(light->HasShadow == true && (shadowCounter < this->vecDepthShadow.size()))
				{
					this->vecDepthShadow[shadowCounter]->D3DInfo.cameraMatrix = SpotLight::CalculateViewMatrix(light);
					this->vecDepthShadow[shadowCounter]->D3DInfo.prespectiveMatrix = SpotLight::CalculatePrespectiveMatrix(light);

					this->vecDepthShadow[shadowCounter]->Snap(objects);

					vecLightBuffer.back().shadowNum = shadowCounter;

					++shadowCounter;
				}
			}

		}
	}

	cBuffer::cbLight lightBuffer;
	ZeroMemory(&lightBuffer, sizeof(cBuffer::cbLight));

	std::size_t numberOfLights = vecLightBuffer.size();
	if(numberOfLights > 0)
	{
		unsigned int totalSize = numberOfLights * sizeof(cBuffer::CLightDesc);

		if(totalSize > sizeof(cBuffer::cbLight))
			totalSize = sizeof(cBuffer::cbLight);

		memcpy(&lightBuffer.lights, &vecLightBuffer.front(), totalSize);
	}

	int difference = memcmp(&lightBuffer, &LastLightInput, sizeof(cBuffer::cbLight));
	if(difference != 0)
	{
		ID3D11DeviceContext* pImmediateContext = graphicManager.D3DStuff.pImmediateContext;

		graphicManager.D3DStuff.pImmediateContext->UpdateSubresource(graphicManager.D3DStuff.pCBLight, 0, NULL, &lightBuffer, 0, 0);
		graphicManager.D3DStuff.pImmediateContext->VSSetConstantBuffers(2, 1, &(graphicManager.D3DStuff.pCBLight));
		graphicManager.D3DStuff.pImmediateContext->PSSetConstantBuffers(2, 1, &(graphicManager.D3DStuff.pCBLight));

		LastLightInput = lightBuffer;
	}
	
	graphicManager.D3DStuff.pImmediateContext->PSSetShaderResources(100, 1, &(this->shaderShadowTexture));

	graphicManager.RemoveSceneFilter(this->shadowFilter->ID);
}