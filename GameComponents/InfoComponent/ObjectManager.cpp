#include "ObjectManager.h"
#include <Keys.h>

ObjectManager::ObjectManager()
{

}

void ObjectManager::Init()
{
}

void ObjectManager::Update(double realTime, double deltaTime)
{

}

void ObjectManager::Work()	
{

}

void ObjectManager::Shutdown()	
{

}

void ObjectManager::UpdateObject(std::string ID, std::string infoID, std::string info)
{
	auto obj = this->objects.First([&ID](CHL::VectorQ<Object>::iterator iterObj)
					{ return iterObj->ID() == ID; });

	obj->Store(infoID, info);
}

Object ObjectManager::GetObjectInfo(std::string ID)
{
	return *this->objects.First([&ID](CHL::VectorQ<Object>::iterator iterObj)
					{ return iterObj->ID() == ID; });
}

void ObjectManager::Insert(Object obj)
{
	this->objects.push_back(obj);
}

const CHL::VectorQ<Object> ObjectManager::AllObjects()
{
	return this->objects;
}