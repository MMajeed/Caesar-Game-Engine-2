#include "ObjectManager.h"
#include "Camera.h"
#include "Prespective.h"

ObjectManager::ObjectManager()
	: Interface("Object Manager")
{

}

void ObjectManager::Init()
{
	std::shared_ptr<Camera> camera(new Camera("Camera1"));
	this->Insert(camera);
	std::shared_ptr<Prespective> prespective(new Prespective("Prespective1"));
	this->Insert(prespective);
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

const CHL::VectorQueryable<std::shared_ptr<Object>> ObjectManager::AllObjects()
{
	return this->objects;
}