#include "ObjectINFO.h"
#include "Keys.h"

ObjectINFO::ObjectINFO()
{
	this->Light = true;
	this->Shadow = true;
	this->Depth = true;
}

std::shared_ptr<Object> ObjectINFO::Get(const std::string& ID)
{
	std::shared_ptr<Object> returnValue;

	returnValue = INFO::Get(ID);
	if(!returnValue)
	{
			 if(ID == Keys::ObjectInfo::LOCATION){ returnValue = GenericObj<CML::Vec4>::CreateNew(this->Location); }
		else if(ID == Keys::ObjectInfo::ROTATION){ returnValue = GenericObj<CML::Vec4>::CreateNew(this->Rotation); }
		else if(ID == Keys::ObjectInfo::SCALE){ returnValue = GenericObj<CML::Vec4>::CreateNew(this->Scale); }
		else if(ID == Keys::ObjectInfo::DIFFUSE){ returnValue = GenericObj<CML::Vec4>::CreateNew(this->Diffuse); }
		else if(ID == Keys::ObjectInfo::AMBIENT){ returnValue = GenericObj<CML::Vec4>::CreateNew(this->Ambient); }
		else if(ID == Keys::ObjectInfo::SPECULAR){ returnValue = GenericObj<CML::Vec4>::CreateNew(this->Specular); }
		else if(ID == Keys::ObjectInfo::DRAWABLEOBJ){ returnValue = GenericObj<std::string>::CreateNew(this->DrawObjID); }
		else if(ID == Keys::ObjectInfo::TEXTURE2DOBJ){ returnValue = GenericObj<std::vector<std::string>>::CreateNew(this->Texture2DVecs); }
		else if(ID == Keys::ObjectInfo::TEXTURECUBEOBJ){ returnValue = GenericObj<std::vector<std::string>>::CreateNew(this->TextureCubeVecs); }
		else if(ID == Keys::ObjectInfo::LIGHT){ returnValue = GenericObj<bool>::CreateNew(this->Light); }
		else if(ID == Keys::ObjectInfo::SHADOW){ returnValue = GenericObj<bool>::CreateNew(this->Shadow); }
		else if(ID == Keys::ObjectInfo::DEPTH){ returnValue = GenericObj<bool>::CreateNew(this->Depth); }
		else if(ID == Keys::ObjectInfo::OBJUSERDATA){ returnValue = GenericObj<std::array<float, USERDATASIZE>>::CreateNew(this->UserData); }
		else if(ID == Keys::ObjectInfo::ANIMATIONJOINT){ returnValue = GenericObj<ObjectINFO::sAnimationJoint>::CreateNew(this->AnimationJoint); }
	}

	return returnValue;
}


void ObjectINFO::Set(const std::string& ID, std::shared_ptr<Object> obj)
{
	INFO::Set(ID, obj);
	
		 if(ID == Keys::ObjectInfo::LOCATION){ this->Location = GenericObj<CML::Vec4>::GetValue(obj); }
	else if(ID == Keys::ObjectInfo::ROTATION){ this->Rotation = GenericObj<CML::Vec4>::GetValue(obj); }
	else if(ID == Keys::ObjectInfo::SCALE){ this->Scale = GenericObj<CML::Vec4>::GetValue(obj); }
	else if(ID == Keys::ObjectInfo::DIFFUSE){ this->Diffuse = GenericObj<CML::Vec4>::GetValue(obj); }
	else if(ID == Keys::ObjectInfo::AMBIENT){ this->Ambient = GenericObj<CML::Vec4>::GetValue(obj); }
	else if(ID == Keys::ObjectInfo::SPECULAR){ this->Specular = GenericObj<CML::Vec4>::GetValue(obj); }
	else if(ID == Keys::ObjectInfo::DRAWABLEOBJ){ this->DrawObjID = GenericObj<std::string>::GetValue(obj); }
	else if(ID == Keys::ObjectInfo::TEXTURE2DOBJ){ this->Texture2DVecs = GenericObj<std::vector<std::string>>::GetValue(obj); }
	else if(ID == Keys::ObjectInfo::TEXTURECUBEOBJ){ this->TextureCubeVecs = GenericObj<std::vector<std::string>>::GetValue(obj); }
	else if(ID == Keys::ObjectInfo::LIGHT){ this->Light = GenericObj<bool>::GetValue(obj); }
	else if(ID == Keys::ObjectInfo::SHADOW){ this->Shadow = GenericObj<bool>::GetValue(obj); }
	else if(ID == Keys::ObjectInfo::DEPTH){ this->Depth = GenericObj<bool>::GetValue(obj); }
	else if(ID == Keys::ObjectInfo::OBJUSERDATA){ this->UserData = GenericObj<std::array<float, USERDATASIZE>>::GetValue(obj); }
	else if(ID == Keys::ObjectInfo::ANIMATIONJOINT){ this->AnimationJoint = GenericObj<ObjectINFO::sAnimationJoint>::GetValue(obj); }
}

std::shared_ptr<INFO> ObjectINFO::Clone()
{
	return std::make_shared<ObjectINFO>(*this);
}