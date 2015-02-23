#include "PhysicsFactory.h"

#include <Logger.h>

PhysicsFactory::PhysicsFactory(const PhysicsFactory::PhysicsItem& input) : _ClassItems(input)
{
	if(this->Verify() == false)
	{
		Logger::LogError("Failed to load Physics, factory component was not loaded.");
	}
}

bool PhysicsFactory::Verify()
{
	if(this->_ClassItems._PhysicsInterface == false){ return false; }
	if(this->_ClassItems._CollisionShapeFactory == false){ return false; }
	if(this->_ClassItems._ConstraintFactory == false){ return false; }
	if(this->_ClassItems._RigidBodyFactory == false){ return false; }

	return true;
}

void PhysicsFactory::SubmitMessage(std::shared_ptr<Message> msg)
{
	this->_ClassItems._PhysicsInterface->SubmitMessage(msg);
}
void PhysicsFactory::SubmitMessage(std::function<Message::Status()> func)
{
	std::shared_ptr<FuncMessage> msg(new FuncMessage(func));
	this->_ClassItems._PhysicsInterface->SubmitMessage(msg);
}
std::shared_ptr<Interface> PhysicsFactory::GetComponent()
{
	return this->_ClassItems._PhysicsInterface;
}

std::mutex& PhysicsFactory::Mutex()
{
	return this->_ClassItems._PhysicsInterface->mutex;
}

std::shared_ptr<iCollisionShapeFactory> PhysicsFactory::CollisionShapeFactory()
{
	return this->_ClassItems._CollisionShapeFactory;
}
std::shared_ptr<iConstraintFactory> PhysicsFactory::ConstraintFactory()
{
	return this->_ClassItems._ConstraintFactory;
}
std::shared_ptr<iRigidBodyFactory> PhysicsFactory::RigidBodyFactory()
{
	return this->_ClassItems._RigidBodyFactory;
}