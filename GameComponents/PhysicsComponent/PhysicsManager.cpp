#include "PhysicsManager.h"

PhysicsManager::PhysicsManager()
{
}

void PhysicsManager::Init()
{
	this->Info.broadphase = std::shared_ptr<btDbvtBroadphase>(new btDbvtBroadphase());
	this->Info.collisionConfiguration = std::shared_ptr<btDefaultCollisionConfiguration>(new btDefaultCollisionConfiguration());
	this->Info.dispatcher = std::shared_ptr<btCollisionDispatcher>(new btCollisionDispatcher(this->Info.collisionConfiguration.get()));
	this->Info.solver = std::shared_ptr<btSequentialImpulseConstraintSolver>(new btSequentialImpulseConstraintSolver);
	this->Info.dynamicsWorld = std::shared_ptr<btDiscreteDynamicsWorld>(
		new btDiscreteDynamicsWorld(this->Info.dispatcher.get(),
									this->Info.broadphase.get(), 
									this->Info.solver.get(),
									this->Info.collisionConfiguration.get()));

	this->Info.dynamicsWorld->setGravity(btVector3(0.0f, -9.81f, 0.0f));
}
void PhysicsManager::Work(double realTime, double deltaTime)
{
	std::lock_guard<std::mutex> lock(this->mutex);

	this->Info.dynamicsWorld->stepSimulation((float)deltaTime, 10);
	
}
void PhysicsManager::Shutdown()
{
}


void PhysicsManager::InsertCollisionShapeObj(const std::string& ID, std::shared_ptr<CollisionShape> obj)
{
	this->CollisionShapeObjs[ID] = obj;
}
void PhysicsManager::RemoveCollisionShapeObj(const std::string& ID)
{
	auto iter = this->CollisionShapeObjs.find(ID);
	if(iter != this->CollisionShapeObjs.end())
	{
		iter->second->Destory();
		this->CollisionShapeObjs.erase(iter);
	}
}

void PhysicsManager::InsertRigidBodyObj(const std::string& ID, std::shared_ptr<RigidBody> obj)
{
	this->RigidBodyObjs[ID] = obj;
}
void PhysicsManager::RemoveRigidBodyObj(const std::string& ID)
{
	auto iter = this->RigidBodyObjs.find(ID);
	if(iter != this->RigidBodyObjs.end())
	{
		iter->second->Destory();
		this->RigidBodyObjs.erase(iter);
	}
}

void PhysicsManager::InsertConstraintObj(const std::string& ID, std::shared_ptr<Constraint> obj)
{
	this->ConstraintObjs[ID] = obj;
}
void PhysicsManager::RemoveConstraintObj(const std::string& ID)
{
	auto iter = this->ConstraintObjs.find(ID);
	if(iter != this->ConstraintObjs.end())
	{
		iter->second->Destory();
		this->ConstraintObjs.erase(iter);
	}
}