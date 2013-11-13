#include "SpotLight.h"
#include "GraphicManager.h"
#include <3DMath.h>
#include <Keys.h>
#include <XNAConverter.h>

cBuffer::CLightDesc SpotLight::GetLightDesc(TypedefObject::ObjectInfo& lightInfo)
{
	CHL::Vec4& diffuse = GenericObj<CHL::Vec4>::GetValue(lightInfo.find(Keys::Light::DIFFUSE)->second);
	CHL::Vec4& ambient = GenericObj<CHL::Vec4>::GetValue(lightInfo.find(Keys::Light::AMBIENT)->second);
	CHL::Vec4& specular = GenericObj<CHL::Vec4>::GetValue(lightInfo.find(Keys::Light::SPECULAR)->second);
	CHL::Vec4& position = GenericObj<CHL::Vec4>::GetValue(lightInfo.find(Keys::Light::POSITION)->second);
	double range = GenericObj<double>::GetValue(lightInfo.find(Keys::Light::RANGE)->second);
	CHL::Vec4& direction = GenericObj<CHL::Vec4>::GetValue(lightInfo.find(Keys::Light::DIRECTION)->second);
	double spot = GenericObj<double>::GetValue(lightInfo.find(Keys::Light::SPOT)->second);
	CHL::Vec4& att = GenericObj<CHL::Vec4>::GetValue(lightInfo.find(Keys::Light::ATTENUATION)->second);

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