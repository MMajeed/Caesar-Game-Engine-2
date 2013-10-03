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

Info InfoManager::GetObjectInfo(std::string ID)
{
	return this->objects[ID];
}

void InfoManager::Insert(const Info& obj)
{
	this->objects[obj.ID()] = obj;
}

const CHL::MapQ<std::string, Info>& InfoManager::AllObjects()
{
	return this->objects;
}