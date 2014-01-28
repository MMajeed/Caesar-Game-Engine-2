#include "DirectionalLightINFO.h"
#include "Keys.h"

std::shared_ptr<Object> DirectionalLightINFO::Get(const std::string& ID)
{
	std::shared_ptr<Object> returnValue;

	returnValue = LightINFO::Get(ID);
	if(!returnValue)
	{
		if(ID == Keys::Light::DIRECTION){ returnValue = GenericObj<CML::Vec4>::CreateNew(this->Direction); }
	}

	return returnValue;
}


void DirectionalLightINFO::Set(const std::string& ID, std::shared_ptr<Object> obj)
{
	LightINFO::Set(ID, obj);

	if(ID == Keys::Light::DIRECTION){ this->Direction = GenericObj<CML::Vec4>::GetValue(obj); }
}

std::shared_ptr<INFO> DirectionalLightINFO::Clone()
{
	return std::make_shared<DirectionalLightINFO>(*this);
}