#include "SetupLight.h"
#include <SpotLightINFO.h>
#include <DirectionalLightINFO.h>
#include <PointLightINFO.h>
#include "DirectLight.h"
#include "SpotLight.h"
#include "PointLight.h"
#include "GraphicManager.h"

void Light::SetupLight(std::hash_map<std::string, SP_INFO>& objects)
{
	std::vector<cBuffer::CLightDesc> vecLightBuffer;

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
			}
			else if(std::shared_ptr<PointLightINFO> light = std::dynamic_pointer_cast<PointLightINFO>(iterObj->second))
			{
				vecLightBuffer.push_back(PointLight::GetLightDesc(light));
			}
			else if(std::shared_ptr<SpotLightINFO> light = std::dynamic_pointer_cast<SpotLightINFO>(iterObj->second))
			{
				vecLightBuffer.push_back(SpotLight::GetLightDesc(light));
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

	GraphicManager& graphicManager = GraphicManager::GetInstance();

	ID3D11DeviceContext* pImmediateContext = graphicManager.D3DStuff.pImmediateContext;

	graphicManager.D3DStuff.pImmediateContext->UpdateSubresource(graphicManager.D3DStuff.pCBLight, 0, NULL, &lightBuffer, 0, 0);
	graphicManager.D3DStuff.pImmediateContext->VSSetConstantBuffers(2, 1, &(graphicManager.D3DStuff.pCBLight));
	graphicManager.D3DStuff.pImmediateContext->PSSetConstantBuffers(2, 1, &(graphicManager.D3DStuff.pCBLight));
}