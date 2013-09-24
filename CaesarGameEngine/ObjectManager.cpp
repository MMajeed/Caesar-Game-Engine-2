#include "ObjectManager.h"
#include "Keys.h"
#include "Window.h"

ObjectManager::ObjectManager()
{

}

void ObjectManager::Init()
{
	/*std::shared_ptr<Object> prespective(new Object);
	prespective->Store(Keys::FOVANGLE, 0.785398163);
	prespective->Store(Keys::SCREENWIDTH, (double)Window::GetInstance().window.width);
	prespective->Store(Keys::SCREENHEIGHT, (double)Window::GetInstance().window.height);
	prespective->Store(Keys::MINVIEWABLE, 0.01);
	prespective->Store(Keys::MAXVIEWABLE, 5000.0);
	prespective->Store(Keys::Class, Keys::ClassType::Prespective);
	this->Insert(prespective);*/
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