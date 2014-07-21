#include "ObjectEntity.h"
#include <MathFunctions.h>
#include "Keys.h"

ObjectEntity::ObjectEntity()
{
	this->Location	= {0.0, 0.0, 0.0, 1.0};
	this->Rotation	= {0.0, 0.0, 0.0, 1.0};
	this->Scale		= {1.0, 1.0, 1.0, 1.0};
	this->Depth		= true;
}

CML::Vec4 ObjectEntity::GetLocation()
{
	std::lock_guard<std::mutex> lock(this->metux);
	return this->Location; 
}
void ObjectEntity::SetLocation(const CML::Vec4& v)
{
	std::lock_guard<std::mutex> lock(this->metux);
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
	this->Depth = v; 
}

std::string ObjectEntity::GetDrawObjID()
{
	std::lock_guard<std::mutex> lock(this->metux);
	return this->DrawObjID; 
}
void ObjectEntity::SetDrawObjID(const std::string& v)
{
	std::lock_guard<std::mutex> lock(this->metux);
	this->DrawObjID = v;
}

std::string ObjectEntity::GetAnimationID()
{
	std::lock_guard<std::mutex> lock(this->metux);
	return this->AnimationID;
}
void ObjectEntity::SetAnimationID(const std::string& v)
{
	std::lock_guard<std::mutex> lock(this->metux);
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
	this->RigidBodyID = v;
}

std::hash_set<std::string> ObjectEntity::GetGroupList()
{
	std::lock_guard<std::mutex> lock(this->metux);
	return this->GroupList;
}
void ObjectEntity::SetGroupList(const std::hash_set<std::string>& v)
{
	std::lock_guard<std::mutex> lock(this->metux);
	this->GroupList = v;
}
void ObjectEntity::AddGroupList(std::string ID)
{
	std::lock_guard<std::mutex> lock(this->metux);
	this->GroupList.insert(ID);
}
void ObjectEntity::DeleteGroupList(std::string ID)
{
	std::lock_guard<std::mutex> lock(this->metux);
	this->GroupList.erase(ID);
}
void ObjectEntity::EmptyGroupList()
{
	std::lock_guard<std::mutex> lock(this->metux);
	this->GroupList.clear();
}

std::hash_set<std::string> ObjectEntity::GetTexture2D()
{
	std::lock_guard<std::mutex> lock(this->metux);
	return this->Texture2D;
}
void ObjectEntity::SetTexture2D(const std::hash_set<std::string>& v)
{
	std::lock_guard<std::mutex> lock(this->metux);
	this->Texture2D = v;
}
void ObjectEntity::AddTexture2D(std::string ID)
{
	std::lock_guard<std::mutex> lock(this->metux);
	this->Texture2D.insert(ID);
}
void ObjectEntity::DeleteTexture2D(std::string ID)
{
	std::lock_guard<std::mutex> lock(this->metux);
	this->Texture2D.erase(ID);
}
void ObjectEntity::EmptyTexture2D()
{
	std::lock_guard<std::mutex> lock(this->metux);
	this->Texture2D.clear();
}

std::hash_set<std::string> ObjectEntity::GetTextureCube()
{
	std::lock_guard<std::mutex> lock(this->metux);
	return this->TextureCube;
}
void ObjectEntity::SetTextureCube(const std::hash_set<std::string>& v)
{
	std::lock_guard<std::mutex> lock(this->metux);
	this->TextureCube = v;
}
void ObjectEntity::AddTextureCube(const std::string& ID)
{
	std::lock_guard<std::mutex> lock(this->metux);
	this->TextureCube.insert(ID);
}
void ObjectEntity::DeleteTextureCube(const std::string& ID)
{
	std::lock_guard<std::mutex> lock(this->metux);
	this->TextureCube.erase(ID);
}
void ObjectEntity::EmptyTextureCube()
{
	std::lock_guard<std::mutex> lock(this->metux);
	this->TextureCube.clear();
}

std::hash_map<std::string, std::vector<char>> ObjectEntity::GetUserData()
{
	std::lock_guard<std::mutex> lock(this->metux);
	return this->UserData;
}
void ObjectEntity::SetUserData(std::hash_map<std::string, std::vector<char>> v)
{
	std::lock_guard<std::mutex> lock(this->metux);
	this->UserData = v;
}
bool ObjectEntity::FindUserData(const std::string& ID, std::vector<char>& v)
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
void ObjectEntity::SetUserData(const std::string& ID, const std::vector<char>& data)
{
	std::lock_guard<std::mutex> lock(this->metux);
	this->UserData[ID] = data;
}
void ObjectEntity::DeleteUserData(const std::string& ID)
{
	std::lock_guard<std::mutex> lock(this->metux);
	this->UserData.erase(ID);
}
void ObjectEntity::EmptyUserData()
{
	std::lock_guard<std::mutex> lock(this->metux);
	this->UserData.clear();
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