#include "SpotLightINFO.h"
#include "Keys.h"

std::shared_ptr<Object> SpotLightINFO::Get(const std::string& ID)
{
	std::shared_ptr<Object> returnValue;

	returnValue = LightINFO::Get(ID);
	if(!returnValue)
	{
			 if(ID == Keys::Light::POSITION){ returnValue = GenericObj<CML::Vec4>::CreateNew(this->Position); }
		else if(ID == Keys::Light::DIRECTION){ returnValue = GenericObj<CML::Vec4>::CreateNew(this->Direction); }
		else if(ID == Keys::Light::ATTENUATION){ returnValue = GenericObj<CML::Vec4>::CreateNew(this->Attenuation); }
		else if(ID == Keys::Light::RANGE){ returnValue = GenericObj<double>::CreateNew(this->Range); }
		else if(ID == Keys::Light::SPOT){ returnValue = GenericObj<double>::CreateNew(this->Spot); }
	}

	return returnValue;
}


void SpotLightINFO::Set(const std::string& ID, std::shared_ptr<Object> obj)
{
	LightINFO::Set(ID, obj);

	if(ID == Keys::Light::POSITION){ this->Position = GenericObj<CML::Vec4>::GetValue(obj); }
	else if(ID == Keys::Light::DIRECTION){ this->Direction = GenericObj<CML::Vec4>::GetValue(obj); }
	else if(ID == Keys::Light::ATTENUATION){ this->Attenuation = GenericObj<CML::Vec4>::GetValue(obj); }
	else if(ID == Keys::Light::RANGE){ this->Range = GenericObj<double>::GetValue(obj); }
	else if(ID == Keys::Light::SPOT){ this->Spot = GenericObj<double>::GetValue(obj); }
}

std::shared_ptr<INFO> SpotLightINFO::Clone()
{
	return std::make_shared<SpotLightINFO>(*this);
}