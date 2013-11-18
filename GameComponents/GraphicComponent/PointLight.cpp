#include "PointLight.h"
#include <XNAConverter.h>

cBuffer::CLightDesc PointLight::GetLightDesc(std::shared_ptr<PointLightINFO> lightInfo)
{
	cBuffer::CLightDesc light;
	light.material.diffuse = CHL::ConvertVec4(lightInfo->Diffuse);
	light.material.ambient = CHL::ConvertVec4(lightInfo->Ambient);
	light.material.specular = CHL::ConvertVec4(lightInfo->Specular);
	light.pos = CHL::ConvertVec4(lightInfo->Position);
	light.range = (float)lightInfo->Range;
	light.attenuation = CHL::ConvertVec4(lightInfo->Attenuation);
	light.type = 2;
	return light;
}