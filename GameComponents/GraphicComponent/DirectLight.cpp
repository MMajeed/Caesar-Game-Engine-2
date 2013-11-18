#include "DirectLight.h"
#include <XNAConverter.h>
#include <DirectionalLightINFO.h>

cBuffer::CLightDesc DirectLight::GetLightDesc(std::shared_ptr<DirectionalLightINFO> lightInfo)
{
	cBuffer::CLightDesc light;
	light.material.diffuse = CHL::ConvertVec4(lightInfo->Diffuse);
	light.material.ambient = CHL::ConvertVec4(lightInfo->Ambient);
	light.material.specular = CHL::ConvertVec4(lightInfo->Specular);
	light.dir = CHL::ConvertVec4(lightInfo->Direction);
	light.type = 1;
	return light;
}