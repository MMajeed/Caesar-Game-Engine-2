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
		else if(ID == Keys::Camera::NEARZ){ returnValue = GenericObj<double>::CreateNew(this->nearZ); }
		else if(ID == Keys::Camera::FARZ){ returnValue = GenericObj<double>::CreateNew(this->farZ); }
		else if(ID == Keys::Camera::CLEARCOLOR){ returnValue = GenericObj<CHL::Vec4>::CreateNew(this->ClearColor); }
		else if(ID == Keys::Camera::PROCESS2D){ returnValue = GenericObj<bool>::CreateNew(this->process2D); }
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
	else if(ID == Keys::Camera::NEARZ){ this->nearZ = GenericObj<double>::GetValue(obj); }
	else if(ID == Keys::Camera::FARZ){ this->farZ = GenericObj<double>::GetValue(obj); }
	else if(ID == Keys::Camera::CLEARCOLOR){ this->ClearColor = GenericObj<CHL::Vec4>::GetValue(obj); }
	else if(ID == Keys::Camera::PROCESS2D){ this->process2D = GenericObj<bool>::GetValue(obj); }
}

std::shared_ptr<INFO> CameraINFO::Clone()
{
	return std::make_shared<CameraINFO>(*this);
}