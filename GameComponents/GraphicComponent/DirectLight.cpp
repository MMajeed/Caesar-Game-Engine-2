#include "DirectLight.h"
#include "GraphicManager.h"
#include <3DMath.h>
#include <Keys.h>
#include <XNAConverter.h>


cBuffer::CLightDesc DirectLight::GetLightDesc(TypedefObject::ObjectInfo& lightInfo)
{
	CHL::Vec4& diffuse = GenericObj<CHL::Vec4>::GetValue(lightInfo.find(Keys::Light::DIFFUSE)->second);
	CHL::Vec4& ambient = GenericObj<CHL::Vec4>::GetValue(lightInfo.find(Keys::Light::AMBIENT)->second);
	CHL::Vec4& specular = GenericObj<CHL::Vec4>::GetValue(lightInfo.find(Keys::Light::SPECULAR)->second);
	CHL::Vec4& direction = GenericObj<CHL::Vec4>::GetValue(lightInfo.find(Keys::Light::DIRECTION)->second);

	cBuffer::CLightDesc light;
	light.material.diffuse = CHL::ConvertVec4(diffuse);
	light.material.ambient = CHL::ConvertVec4(ambient);
	light.material.specular = CHL::ConvertVec4(specular);
	light.dir = CHL::ConvertVec4(direction);
	light.type = 1;
	return light;
}