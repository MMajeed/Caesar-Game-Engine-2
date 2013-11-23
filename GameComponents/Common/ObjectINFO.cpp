#include "ObjectINFO.h"
#include "Keys.h"

ObjectINFO::ObjectINFO()
{
	this->Light = true;
	this->Shadow = true;
}

std::shared_ptr<Object> ObjectINFO::Get(const std::string& ID)
{
	std::shared_ptr<Object> returnValue;

	returnValue = INFO::Get(ID);
	if(!returnValue)
	{
			 if(ID == Keys::ObjectInfo::LOCATION){ returnValue = GenericObj<CHL::Vec4>::CreateNew(this->Location); }
		else if(ID == Keys::ObjectInfo::ROTATION){ returnValue = GenericObj<CHL::Vec4>::CreateNew(this->Rotation); }
		else if(ID == Keys::ObjectInfo::SCALE){ returnValue = GenericObj<CHL::Vec4>::CreateNew(this->Scale); }
		else if(ID == Keys::ObjectInfo::DIFFUSE){ returnValue = GenericObj<CHL::Vec4>::CreateNew(this->Diffuse); }
		else if(ID == Keys::ObjectInfo::AMBIENT){ returnValue = GenericObj<CHL::Vec4>::CreateNew(this->Ambient); }
		else if(ID == Keys::ObjectInfo::SPECULAR){ returnValue = GenericObj<CHL::Vec4>::CreateNew(this->Specular); }
		else if(ID == Keys::ObjectInfo::DRAWABLEOBJ){ returnValue = GenericObj<std::string>::CreateNew(this->DrawObjID); }
		else if(ID == Keys::ObjectInfo::TEXTURE2DOBJ){ returnValue = GenericObj<std::vector<std::string>>::CreateNew(this->Texture2DVecs); }
		else if(ID == Keys::ObjectInfo::TEXTURECUBEOBJ){ returnValue = GenericObj<std::vector<std::string>>::CreateNew(this->TextureCubeVecs); }
		else if(ID == Keys::ObjectInfo::LIGHT){ returnValue = GenericObj<bool>::CreateNew(this->Light); }
		else if(ID == Keys::ObjectInfo::SHADOW){ returnValue = GenericObj<bool>::CreateNew(this->Shadow); }
	}

	return returnValue;
}


void ObjectINFO::Set(const std::string& ID, std::shared_ptr<Object> obj)
{
	INFO::Set(ID, obj);
	
		 if(ID == Keys::ObjectInfo::LOCATION){ this->Location = GenericObj<CHL::Vec4>::GetValue(obj); }
	else if(ID == Keys::ObjectInfo::ROTATION){ this->Rotation = GenericObj<CHL::Vec4>::GetValue(obj); }
	else if(ID == Keys::ObjectInfo::SCALE){ this->Scale = GenericObj<CHL::Vec4>::GetValue(obj); }
	else if(ID == Keys::ObjectInfo::DIFFUSE){ this->Diffuse = GenericObj<CHL::Vec4>::GetValue(obj); }
	else if(ID == Keys::ObjectInfo::AMBIENT){ this->Ambient = GenericObj<CHL::Vec4>::GetValue(obj); }
	else if(ID == Keys::ObjectInfo::SPECULAR){ this->Specular = GenericObj<CHL::Vec4>::GetValue(obj); }
	else if(ID == Keys::ObjectInfo::DRAWABLEOBJ){ this->DrawObjID = GenericObj<std::string>::GetValue(obj); }
	else if(ID == Keys::ObjectInfo::TEXTURE2DOBJ){ this->Texture2DVecs = GenericObj<std::vector<std::string>>::GetValue(obj); }
	else if(ID == Keys::ObjectInfo::TEXTURECUBEOBJ){ this->TextureCubeVecs = GenericObj<std::vector<std::string>>::GetValue(obj); }
	else if(ID == Keys::ObjectInfo::LIGHT){ this->Light = GenericObj<bool>::GetValue(obj); }
	else if(ID == Keys::ObjectInfo::SHADOW){ this->Shadow = GenericObj<bool>::GetValue(obj); }
	
}

std::shared_ptr<INFO> ObjectINFO::Clone()
{
	return std::make_shared<ObjectINFO>(*this);
}