#include "ObjectManager.h"
#include "Camera.h"

void ObjectManager::Init()
{
	std::shared_ptr<Object> obj(new Camera);
	this->Insert(obj);
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

void ObjectManager::Insert(std::shared_ptr<Object> obj)
{
	this->objects.push_back(obj);
}

const CHL::VectorQuerable<std::shared_ptr<Object>>  ObjectManager::AllObjects()
{
	return this->objects;
}