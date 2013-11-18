#include "LightINFO.h"
#include "Keys.h"

std::shared_ptr<Object> LightINFO::Get(const std::string& ID)
{
	std::shared_ptr<Object> returnValue;

	returnValue = INFO::Get(ID);
	if(!returnValue)
	{
			 if(ID == Keys::Light::DIFFUSE){ returnValue = GenericObj<CHL::Vec4>::CreateNew(this->Diffuse); }
		else if(ID == Keys::Light::AMBIENT){ returnValue = GenericObj<CHL::Vec4>::CreateNew(this->Ambient); }
		else if(ID == Keys::Light::SPECULAR){ returnValue = GenericObj<CHL::Vec4>::CreateNew(this->Specular); }
		else if(ID == Keys::Light::HASHADOW){ returnValue = GenericObj<bool>::CreateNew(this->HasShadow); }
	}

	return returnValue;
}


void LightINFO::Set(const std::string& ID, std::shared_ptr<Object> obj)
{
	INFO::Set(ID, obj);

		 if(ID == Keys::Light::DIFFUSE){ this->Diffuse = GenericObj<CHL::Vec4>::GetValue(obj); }
	else if(ID == Keys::Light::AMBIENT){ this->Ambient = GenericObj<CHL::Vec4>::GetValue(obj); }
	else if(ID == Keys::Light::SPECULAR){ this->Specular = GenericObj<CHL::Vec4>::GetValue(obj); }
	else if(ID == Keys::Light::HASHADOW){ this->HasShadow = GenericObj<bool>::GetValue(obj); }
}