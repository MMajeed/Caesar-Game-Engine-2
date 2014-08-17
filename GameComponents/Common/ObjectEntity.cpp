#include "ObjectEntity.h"
#include <MathFunctions.h>

ObjectEntity::ObjectEntity()
{
	this->Location	= {0.0, 0.0, 0.0, 1.0};
	this->Rotation	= {0.0, 0.0, 0.0, 1.0};
	this->Scale		= {1.0, 1.0, 1.0, 1.0};
	this->Depth		= true;
	this->Priority	= 0;
	this->FillMode	= FILL_MODE::FILL_SOLID;
	this->CullMode	= CULL_MODE::CULL_FRONT;
	this->Tracker	= 0;
}

unsigned int ObjectEntity::GetTracker()
{
	std::lock_guard<std::mutex> lock(this->metux);
	return this->Tracker;
}
void ObjectEntity::PrivateUpdateTracker()
{
	(this->Tracker)++;
}
void ObjectEntity::UpdateTracker()
{
	std::lock_guard<std::mutex> lock(this->metux);
	this->PrivateUpdateTracker();
}

CML::Vec4 ObjectEntity::GetLocation()
{
	std::lock_guard<std::mutex> lock(this->metux);
	return this->Location; 
}
void ObjectEntity::SetLocation(const CML::Vec4& v)
{
	std::lock_guard<std::mutex> lock(this->metux);
	this->PrivateUpdateTracker();
	this->Location = v; 
}

CML::Vec4 ObjectEntity::GetRotation()
{
	std::lock_guard<std::mutex> lock(this->metux);
	return this->Rotation; 
}
void ObjectEntity::SetRotation(const CML::Vec4& v)
{
	std::lock_guard<std::mutex> lock(this->metux);
	this->PrivateUpdateTracker();
	this->Rotation = v; 
}

CML::Vec4 ObjectEntity::GetScale()
{

	std::lock_guard<std::mutex> lock(this->metux);
	return this->Scale; 
}
void ObjectEntity::SetScale(const CML::Vec4& v)
{
	std::lock_guard<std::mutex> lock(this->metux);
	this->PrivateUpdateTracker();
	this->Scale = v; 
}

bool ObjectEntity::GetDepth()
{
	std::lock_guard<std::mutex> lock(this->metux);
	return this->Depth;
}
void ObjectEntity::SetDepth(bool v)
{
	std::lock_guard<std::mutex> lock(this->metux);
	this->PrivateUpdateTracker();
	this->Depth = v;
}

double ObjectEntity::GetPriority()
{
	std::lock_guard<std::mutex> lock(this->metux);
	return this->Priority;
}
void ObjectEntity::SetPriority(double v)
{
	std::lock_guard<std::mutex> lock(this->metux);
	this->PrivateUpdateTracker();
	this->Priority = v;
}

std::string ObjectEntity::GetGraphicModelID()
{
	std::lock_guard<std::mutex> lock(this->metux);
	return this->GraphicModelID; 
}
void ObjectEntity::SetGraphicModelID(const std::string& v)
{
	std::lock_guard<std::mutex> lock(this->metux);
	this->PrivateUpdateTracker();
	this->GraphicModelID = v;
}

std::string ObjectEntity::GetVertexShaderID()
{
	std::lock_guard<std::mutex> lock(this->metux);
	return this->VertexShaderID;
}
void ObjectEntity::SetVertexShaderID(const std::string& v)
{
	std::lock_guard<std::mutex> lock(this->metux);
	this->PrivateUpdateTracker();
	this->VertexShaderID = v;
}

std::string ObjectEntity::GetGeometryShaderID()
{
	std::lock_guard<std::mutex> lock(this->metux);
	return this->GeometryShaderID;
}
void ObjectEntity::SetGeometryShaderID(const std::string& v)
{
	std::lock_guard<std::mutex> lock(this->metux);
	this->PrivateUpdateTracker();
	this->GeometryShaderID = v;
}

std::string ObjectEntity::GetPixelShaderID()
{
	std::lock_guard<std::mutex> lock(this->metux);
	return this->PixelShaderID;
}
void ObjectEntity::SetPixelShaderID(const std::string& v)
{
	std::lock_guard<std::mutex> lock(this->metux);
	this->PrivateUpdateTracker();
	this->PixelShaderID = v;
}

std::string ObjectEntity::GetAnimationID()
{
	std::lock_guard<std::mutex> lock(this->metux);
	return this->AnimationID;
}
void ObjectEntity::SetAnimationID(const std::string& v)
{
	std::lock_guard<std::mutex> lock(this->metux);
	this->PrivateUpdateTracker();
	this->AnimationID = v;
}

std::string ObjectEntity::GetJointName()
{
	std::lock_guard<std::mutex> lock(this->metux);
	return this->JointName;
}
void ObjectEntity::SetJointName(const std::string& v)
{
	std::lock_guard<std::mutex> lock(this->metux);
	this->PrivateUpdateTracker();
	this->JointName = v;
}

std::string ObjectEntity::GetRigidBodyID()
{
	std::lock_guard<std::mutex> lock(this->metux);
	return this->RigidBodyID;
}
void ObjectEntity::SetRigidBodyID(const std::string& v)
{
	std::lock_guard<std::mutex> lock(this->metux);
	this->PrivateUpdateTracker();
	this->RigidBodyID = v;
}

std::set<std::string> ObjectEntity::GetGroupList()
{
	std::lock_guard<std::mutex> lock(this->metux);
	return this->GroupList;
}
void ObjectEntity::SetGroupList(const std::set<std::string>& v)
{
	std::lock_guard<std::mutex> lock(this->metux);
	this->PrivateUpdateTracker();
	this->GroupList = v;
}
void ObjectEntity::AddGroupList(std::string ID)
{
	std::lock_guard<std::mutex> lock(this->metux);
	this->PrivateUpdateTracker();
	this->GroupList.insert(ID);
}
void ObjectEntity::DeleteGroupList(std::string ID)
{
	std::lock_guard<std::mutex> lock(this->metux);
	this->PrivateUpdateTracker();
	this->GroupList.erase(ID);
}
void ObjectEntity::EmptyGroupList()
{
	std::lock_guard<std::mutex> lock(this->metux);
	this->PrivateUpdateTracker();
	this->GroupList.clear();
}

std::unordered_map<std::string, std::string> ObjectEntity::GetTexture()
{
	std::lock_guard<std::mutex> lock(this->metux);
	return this->Texture;
}
void ObjectEntity::SetTexture(std::unordered_map<std::string, std::string> v)
{
	std::lock_guard<std::mutex> lock(this->metux);
	this->PrivateUpdateTracker();
	this->Texture = v;
}
bool ObjectEntity::FindTexture(const std::string& ID, std::string& returnTextureID)
{
	std::lock_guard<std::mutex> lock(this->metux);
	this->PrivateUpdateTracker();
	bool returnValue = false;
	auto iter = this->Texture.find(ID);
	if(iter != this->Texture.end())
	{
		returnTextureID = iter->second;
		returnValue = true;
	}
	return returnValue;
}
void ObjectEntity::SetTexture(const std::string& ID, const std::string& v)
{
	std::lock_guard<std::mutex> lock(this->metux);
	this->PrivateUpdateTracker();
	this->Texture[ID] = v;
}
void ObjectEntity::DeleteTexture(const std::string& ID)
{
	std::lock_guard<std::mutex> lock(this->metux);
	this->Texture.erase(ID);
}
void ObjectEntity::EmptyTexture()
{
	std::lock_guard<std::mutex> lock(this->metux);
	this->PrivateUpdateTracker();
	this->Texture.clear();
}

std::unordered_map<std::string, std::shared_ptr<Object>> ObjectEntity::GetUserData()
{
	std::lock_guard<std::mutex> lock(this->metux);
	return this->UserData;
}
void ObjectEntity::SetUserData(std::unordered_map<std::string, std::shared_ptr<Object>> v)
{
	std::lock_guard<std::mutex> lock(this->metux);
	this->PrivateUpdateTracker();
	this->UserData = v;
}
std::shared_ptr<Object> ObjectEntity::FindUserData(const std::string& ID)
{
	std::lock_guard<std::mutex> lock(this->metux);
	this->PrivateUpdateTracker();

	std::shared_ptr<Object> returnValue;
	auto iter = this->UserData.find(ID);
	if(iter != this->UserData.end())
	{
		returnValue = iter->second;
	}
	return returnValue;
}
void ObjectEntity::SetUserData(const std::string& ID, const std::shared_ptr<Object>& data)
{
	std::lock_guard<std::mutex> lock(this->metux);
	this->UserData[ID] = data;
}
void ObjectEntity::DeleteUserData(const std::string& ID)
{
	std::lock_guard<std::mutex> lock(this->metux);
	this->PrivateUpdateTracker();
	this->UserData.erase(ID);
}
void ObjectEntity::EmptyUserData()
{
	std::lock_guard<std::mutex> lock(this->metux);
	this->PrivateUpdateTracker();
	this->UserData.clear();
}

ObjectEntity::FILL_MODE ObjectEntity::GetFillMode()
{
	std::lock_guard<std::mutex> lock(this->metux);
	return this->FillMode;
}
void ObjectEntity::SetFillMode(const ObjectEntity::FILL_MODE& v)
{
	std::lock_guard<std::mutex> lock(this->metux);
	this->PrivateUpdateTracker();
	this->FillMode = v;
}

ObjectEntity::CULL_MODE ObjectEntity::GetCullMode()
{
	std::lock_guard<std::mutex> lock(this->metux);
	return this->CullMode;
}
void ObjectEntity::SetCullMode(const ObjectEntity::CULL_MODE& v)
{
	std::lock_guard<std::mutex> lock(this->metux);
	this->PrivateUpdateTracker();
	this->CullMode = v;
}

std::shared_ptr<ObjectEntity> ObjectEntity::Spawn()
{
	std::shared_ptr<ObjectEntity> returnValue(new ObjectEntity);
	return returnValue;
}
std::shared_ptr<Entity> ObjectEntity::Clone()
{
	ObjectEntity* temp = new ObjectEntity(*this);
	std::shared_ptr<ObjectEntity> returnValue(temp);
	return returnValue;
}