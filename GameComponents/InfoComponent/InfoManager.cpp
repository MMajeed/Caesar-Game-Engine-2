#include "InfoManager.h"
#include <Keys.h>

InfoManager::InfoManager()
{

}

void InfoManager::Init()
{
}

void InfoManager::Update(double realTime, double deltaTime)
{

}

void InfoManager::Work()	
{

}

void InfoManager::Shutdown()	
{

}

void InfoManager::UpdateObject(std::string ID, std::string infoID, std::shared_ptr<Object> info)
{
	this->objects[ID].Store(infoID, info);
}

void InfoManager::DeleteInfo(std::string ID, std::string infoID)
{
	this->objects[ID].Erase(infoID);
}

const Info& InfoManager::GetObjectInfo(std::string ID)
{
	auto iter = this->objects.find(ID);
	if (iter == this->objects.end())
	{
		throw std::exception(("Failed to find the object with the ID" + ID).c_str());
	}
	return iter->second;
}

void InfoManager::Insert(const Info& obj)
{
	this->objects[obj.ID()] = obj;
}

const std::hash_map<std::string, Info>& InfoManager::AllObjects()
{
	return this->objects;
}