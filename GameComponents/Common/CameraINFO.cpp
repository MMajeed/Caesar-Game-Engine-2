#include "CameraINFO.h"
#include "Keys.h"

CameraINFO::CameraINFO()
{

}

std::shared_ptr<Object> CameraINFO::Get(const std::string& ID)
{
	std::shared_ptr<Object> returnValue;

	returnValue = INFO::Get(ID);
	if(!returnValue)
	{
			 if(ID == Keys::Camera::EYE){ returnValue = GenericObj<CHL::Vec4>::CreateNew(this->Eye); }
		else if(ID == Keys::Camera::TARGETMAGNITUDE){ returnValue = GenericObj<CHL::Vec4>::CreateNew(this->TargetMagnitude); }
		else if(ID == Keys::Camera::UP){ returnValue = GenericObj<CHL::Vec4>::CreateNew(this->Up); }
		else if(ID == Keys::Camera::RADIANPITCH){ returnValue = GenericObj<double>::CreateNew(this->Pitch); }
		else if(ID == Keys::Camera::RADIANYAW){ returnValue = GenericObj<double>::CreateNew(this->Yaw); }
		else if(ID == Keys::Camera::RADIANROLL){ returnValue = GenericObj<double>::CreateNew(this->Roll); }
		else if(ID == Keys::Camera::FOVANGLE){ returnValue = GenericObj<double>::CreateNew(this->FovAngleY); }
		else if(ID == Keys::Camera::NEARZ){ returnValue = GenericObj<double>::CreateNew(this->NearZ); }
		else if(ID == Keys::Camera::FARZ){ returnValue = GenericObj<double>::CreateNew(this->FarZ); }
		else if(ID == Keys::Camera::CLEARCOLOR){ returnValue = GenericObj<CHL::Vec4>::CreateNew(this->ClearColor); }
		else if(ID == Keys::Camera::GLOBAL2DTEXTURE){ returnValue = GenericObj<std::vector<std::string>>::CreateNew(this->Global2DTexture); }
		else if(ID == Keys::Camera::GLOBALCUBETEXTURE){ returnValue = GenericObj<std::vector<std::string>>::CreateNew(this->GlobalCubeTexture); }
		else if(ID == Keys::Camera::PROCESS2D){ returnValue = GenericObj<bool>::CreateNew(this->Process2D); }
		else if(ID == Keys::Camera::GLOBALUSERDATA){ returnValue = GenericObj<std::array<float, GLOBALUSERDATASIZE>>::CreateNew(this->GlobalUserData); }
	}

	return returnValue;
}

void CameraINFO::Set(const std::string& ID, std::shared_ptr<Object> obj)
{
	INFO::Set(ID, obj);

		 if(ID == Keys::Camera::EYE){ this->Eye = GenericObj<CHL::Vec4>::GetValue(obj); }
	else if(ID == Keys::Camera::TARGETMAGNITUDE){ this->TargetMagnitude = GenericObj<CHL::Vec4>::GetValue(obj); }
	else if(ID == Keys::Camera::UP){ this->Up = GenericObj<CHL::Vec4>::GetValue(obj); }
	else if(ID == Keys::Camera::RADIANPITCH){ this->Pitch = GenericObj<double>::GetValue(obj); }
	else if(ID == Keys::Camera::RADIANYAW){ this->Yaw = GenericObj<double>::GetValue(obj); }
	else if(ID == Keys::Camera::RADIANROLL){ this->Roll = GenericObj<double>::GetValue(obj); }
	else if(ID == Keys::Camera::FOVANGLE){ this->FovAngleY = GenericObj<double>::GetValue(obj); }
	else if(ID == Keys::Camera::NEARZ){ this->NearZ = GenericObj<double>::GetValue(obj); }
	else if(ID == Keys::Camera::FARZ){ this->FarZ = GenericObj<double>::GetValue(obj); }
	else if(ID == Keys::Camera::CLEARCOLOR){ this->ClearColor = GenericObj<CHL::Vec4>::GetValue(obj); }
	else if(ID == Keys::Camera::GLOBAL2DTEXTURE){ this->Global2DTexture = GenericObj<std::vector<std::string>>::GetValue(obj); }
	else if(ID == Keys::Camera::GLOBALCUBETEXTURE){ this->GlobalCubeTexture = GenericObj<std::vector<std::string>>::GetValue(obj); }
	else if(ID == Keys::Camera::PROCESS2D){ this->Process2D = GenericObj<bool>::GetValue(obj); }
	else if(ID == Keys::Camera::GLOBALUSERDATA){ this->GlobalUserData = GenericObj<std::array<float, GLOBALUSERDATASIZE>>::GetValue(obj); }
}

std::shared_ptr<INFO> CameraINFO::Clone()
{
	return std::make_shared<CameraINFO>(*this);
}