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
	auto obj = *this->objects.First([&ID](CHL::VectorQ<std::shared_ptr<Object>>::iterator iterObj)
					{ return (*iterObj)->ID() == ID; });

	obj->Store(infoID, info);
}

std::shared_ptr<Object> ObjectManager::GetObjectW(std::string ID)
{
	return *this->objects.First([&ID](CHL::VectorQ<std::shared_ptr<Object>>::iterator iterObj)
					{ return (*iterObj)->ID() == ID; });
}

void ObjectManager::Insert(std::shared_ptr<Object> obj)
{
	this->objects.push_back(obj);
}

const CHL::VectorQ<std::shared_ptr<Object>> ObjectManager::AllObjects()
{
	return this->objects;
}