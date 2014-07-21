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
	this->ClearColor = {0.5, 0.5, 0.5, 1.0};
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

CML::Vec4 CameraEntity::GetClearColor()
{
	std::lock_guard<std::mutex> lock(this->metux);
	return this->ClearColor;
}
void CameraEntity::SetClearColor(const CML::Vec4& v)
{
	std::lock_guard<std::mutex> lock(this->metux);
	this->ClearColor = v;
}

std::hash_set<std::string> CameraEntity::GetGlobalTexture2D()
{
	std::lock_guard<std::mutex> lock(this->metux);
	return this->GlobalTexture2D;
}
void CameraEntity::SetGlobalTexture2D(const std::hash_set<std::string>& v)
{
	std::lock_guard<std::mutex> lock(this->metux);
	this->GlobalTexture2D = v;
}
void CameraEntity::AddGlobalTexture2D(std::string ID)
{
	std::lock_guard<std::mutex> lock(this->metux);
	this->GlobalTexture2D.insert(ID);
}
void CameraEntity::DeleteGlobalTexture2D(std::string ID)
{
	std::lock_guard<std::mutex> lock(this->metux);
	this->GlobalTexture2D.erase(ID);
}
void CameraEntity::EmptyGlobalTexture2D()
{
	std::lock_guard<std::mutex> lock(this->metux);
	this->GlobalTexture2D.clear();
}

std::hash_set<std::string> CameraEntity::GetGlobalTextureCube()
{
	std::lock_guard<std::mutex> lock(this->metux);
	return this->GlobalTextureCube;
}
void CameraEntity::SetGlobalTextureCube(const std::hash_set<std::string>& v)
{
	std::lock_guard<std::mutex> lock(this->metux);
	this->GlobalTextureCube = v;
}
void CameraEntity::AddGlobalTextureCube(std::string ID)
{
	std::lock_guard<std::mutex> lock(this->metux);
	this->GlobalTextureCube.insert(ID);
}
void CameraEntity::DeleteGlobalTextureCube(std::string ID)
{
	std::lock_guard<std::mutex> lock(this->metux);
	this->GlobalTextureCube.erase(ID);
}
void CameraEntity::EmptyGlobalTextureCube()
{
	std::lock_guard<std::mutex> lock(this->metux);
	this->GlobalTextureCube.clear();
}


std::hash_map<std::string, std::vector<char>> CameraEntity::GetUserData()
{
	std::lock_guard<std::mutex> lock(this->metux);
	return this->UserData;
}
void CameraEntity::SetUserData(std::hash_map<std::string, std::vector<char>> v)
{
	std::lock_guard<std::mutex> lock(this->metux);
	this->UserData = v;
}
bool CameraEntity::FindUserData(const std::string& ID, std::vector<char>& v)
{
	std::lock_guard<std::mutex> lock(this->metux);
	auto iter = this->UserData.find(ID);
	if(iter != this->UserData.end())
	{
		v = iter->second;
		return true;
	}
	return false;
}
void CameraEntity::SetUserData(const std::string& ID, const std::vector<char>& data)
{
	std::lock_guard<std::mutex> lock(this->metux);
	this->UserData[ID] = data;
}
void CameraEntity::DeleteUserData(const std::string& ID)
{
	std::lock_guard<std::mutex> lock(this->metux);
	this->UserData.erase(ID);
}
void CameraEntity::EmptyUserData()
{
	std::lock_guard<std::mutex> lock(this->metux);
	this->UserData.clear();
}

CameraEntity::InclusionType CameraEntity::GetInclusionState()
{
	std::lock_guard<std::mutex> lock(this->metux);
	return this->InclusionState;
}
void CameraEntity::SetInclusionState(InclusionType v)
{
	std::lock_guard<std::mutex> lock(this->metux);
	this->InclusionState = v;
}

std::hash_set<std::string> CameraEntity::GetInclusionList()
{
	std::lock_guard<std::mutex> lock(this->metux);
	return this->InclusionList;
}
void CameraEntity::SetInclusionList(const std::hash_set<std::string>& v)
{
	std::lock_guard<std::mutex> lock(this->metux);
	this->InclusionList = v;
}
void CameraEntity::AddInclusionList(std::string ID)
{
	std::lock_guard<std::mutex> lock(this->metux);
	this->InclusionList.insert(ID);
}
void CameraEntity::DeleteInclusionList(std::string ID)
{
	std::lock_guard<std::mutex> lock(this->metux);
	this->InclusionList.erase(ID);
}
void CameraEntity::EmptyInclusionList()
{
	std::lock_guard<std::mutex> lock(this->metux);
	this->InclusionList.clear();
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