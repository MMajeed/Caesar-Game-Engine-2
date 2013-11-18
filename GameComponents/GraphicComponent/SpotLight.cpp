#include "SpotLight.h"
#include <XNAConverter.h>

cBuffer::CLightDesc SpotLight::GetLightDesc(std::shared_ptr<SpotLightINFO> lightInfo)
{
	cBuffer::CLightDesc light;
	light.material.diffuse = CHL::ConvertVec4(lightInfo->Diffuse);
	light.material.ambient = CHL::ConvertVec4(lightInfo->Ambient);
	light.material.specular = CHL::ConvertVec4(lightInfo->Specular);
	light.pos = CHL::ConvertVec4(lightInfo->Position);
	light.range = (float)lightInfo->Range;
	light.dir = CHL::ConvertVec4(lightInfo->Direction);
	light.spot = (float)lightInfo->Spot;
	light.attenuation = CHL::ConvertVec4(lightInfo->Attenuation);
	light.type = 3;
	return light;
}