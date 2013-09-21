#include "ObjectManager.h"
#include "Keys.h"
#include "Window.h"

ObjectManager::ObjectManager()
{

}

void ObjectManager::Init()
{
	boost::numeric::ublas::vector<double> eye(4);
	eye(0) = 0.0f;	eye(1) = 5.0f;	eye(2) = -20.0f;	eye(3) = 0.0f; 
	boost::numeric::ublas::vector<double> target(4);
	target(0) = 0.0f;	target(1) = 0.0f;	target(2) = 1.0f;	target(3) = 0.0f; 
	boost::numeric::ublas::vector<double> up(4);
	up(0) = 0.0f;	up(1) = 1.0f;	up(2) = 0.0f;	up(3) = 0.0f; 

	std::shared_ptr<Object> camera(new Object);
	camera->Store(Keys::Class, Keys::ClassType::Camera);
	camera->Store(Keys::EYE, eye);
	camera->Store(Keys::TARGETMAGNITUDE, target);
	camera->Store(Keys::UP, up);
	camera->Store(Keys::RADIANROLL, 0.0);
	camera->Store(Keys::RADIANPITCH, 0.0);
	camera->Store(Keys::RADIANYAW, 0.0);
	this->Insert(camera);

	std::shared_ptr<Object> prespective(new Object);
	prespective->Store(Keys::FOVANGLE, 0.785398163);
	prespective->Store(Keys::SCREENWIDTH, (double)Window::GetInstance().window.width);
	prespective->Store(Keys::SCREENHEIGHT, (double)Window::GetInstance().window.height);
	prespective->Store(Keys::MINVIEWABLE, 0.01);
	prespective->Store(Keys::MAXVIEWABLE, 5000.0);
	prespective->Store(Keys::Class, Keys::ClassType::Prespective);
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