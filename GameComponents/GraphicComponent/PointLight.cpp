#include "PointLight.h"
#include "XNAConverter.h"

cBuffer::CLightDesc PointLight::GetLightDesc(std::shared_ptr<PointLightINFO> lightInfo)
{
	cBuffer::CLightDesc light;
	light.material.diffuse = ConvertVec4(lightInfo->Diffuse);
	light.material.ambient = ConvertVec4(lightInfo->Ambient);
	light.material.specular = ConvertVec4(lightInfo->Specular);
	light.pos = ConvertVec4(lightInfo->Position);
	light.range = (float)lightInfo->Range;
	light.attenuation = ConvertVec4(lightInfo->Attenuation);
	light.type = 2;
	light.shadowNum = -1;
	return light;
}