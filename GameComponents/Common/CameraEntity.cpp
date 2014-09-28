#include "CameraEntity.h"

CameraEntity::CameraEntity()
{
	this->Eye = {0.0, 0.0, 0.0, 0.0};
	this->TargetMagnitude = {0.0, 0.0, 1.0, 0.0};
	this->Up = {0.0, 1.0, 0.0, 0.0};
	this->Roll = 0.0;
	this->Pitch = 0.0;
	this->Yaw = 0.0;
	this->FovAngleY = 0.785398163;
	this->NearZ = 0.01;
	this->FarZ = 5000.0;
}

CML::Vec4 CameraEntity::GetEye()
{
	std::lock_guard<std::mutex> lock(this->metux);
	return this->Eye;
}
void CameraEntity::SetEye(const CML::Vec4& v)
{
	std::lock_guard<std::mutex> lock(this->metux);
	this->Eye = v;
}

CML::Vec4 CameraEntity::GetTargetMagnitude()
{
	std::lock_guard<std::mutex> lock(this->metux);
	return this->TargetMagnitude;
}
void CameraEntity::SetTargetMagnitude(const CML::Vec4& v)
{
	std::lock_guard<std::mutex> lock(this->metux);
	this->TargetMagnitude = v;
}

CML::Vec4 CameraEntity::GetUp()
{
	std::lock_guard<std::mutex> lock(this->metux);
	return this->Up;
}
void CameraEntity::SetUp(const CML::Vec4& v)
{
	std::lock_guard<std::mutex> lock(this->metux);
	this->Up = v;
}

double CameraEntity::GetRoll()
{
	std::lock_guard<std::mutex> lock(this->metux);
	return this->Roll;
}
void CameraEntity::SetRoll(double v)
{
	std::lock_guard<std::mutex> lock(this->metux);
	this->Roll = v;
}

double CameraEntity::GetPitch()
{
	std::lock_guard<std::mutex> lock(this->metux);
	return this->Pitch;
}
void CameraEntity::SetPitch(double v)
{
	std::lock_guard<std::mutex> lock(this->metux);
	this->Pitch = v;
}

double CameraEntity::GetYaw()
{
	std::lock_guard<std::mutex> lock(this->metux);
	return this->Yaw;
}
void CameraEntity::SetYaw(double v)
{
	std::lock_guard<std::mutex> lock(this->metux);
	this->Yaw = v;
}

double CameraEntity::GetFovAngleY()
{
	std::lock_guard<std::mutex> lock(this->metux);
	return this->FovAngleY;
}
void CameraEntity::SetFovAngleY(double v)
{
	std::lock_guard<std::mutex> lock(this->metux);
	this->FovAngleY = v;
}

double CameraEntity::GetNearZ()
{
	std::lock_guard<std::mutex> lock(this->metux);
	return this->NearZ;
}
void CameraEntity::SetNearZ(double v)
{
	std::lock_guard<std::mutex> lock(this->metux);
	this->NearZ = v;
}

double CameraEntity::GetFarZ()
{
	std::lock_guard<std::mutex> lock(this->metux);
	return this->FarZ;
}
void CameraEntity::SetFarZ(double v)
{
	std::lock_guard<std::mutex> lock(this->metux);
	this->FarZ = v;
}

std::shared_ptr<CameraEntity> CameraEntity::Spawn()
{
	std::shared_ptr<CameraEntity> returnValue(new CameraEntity);
	return returnValue;
}
std::shared_ptr<Entity> CameraEntity::Clone()
{
	CameraEntity* temp = new CameraEntity(*this);
	std::shared_ptr<CameraEntity> returnValue(temp);
	return returnValue;
}