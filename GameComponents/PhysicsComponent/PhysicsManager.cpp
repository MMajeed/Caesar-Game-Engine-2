#include "PhysicsManager.h"

PhysicsManager::PhysicsManager()
{
	this->Info.broadphase = 0;
	this->Info.collisionConfiguration = 0;
	this->Info.dispatcher = 0;
	this->Info.solver = 0;
	this->Info.dynamicsWorld = 0;
}

void PhysicsManager::Init()
{
	this->Info.broadphase = new btDbvtBroadphase();
	this->Info.collisionConfiguration = new btDefaultCollisionConfiguration();
	this->Info.dispatcher = new btCollisionDispatcher(this->Info.collisionConfiguration);
	this->Info.solver = new btSequentialImpulseConstraintSolver;
	this->Info.dynamicsWorld = 
		new btDiscreteDynamicsWorld(this->Info.dispatcher, this->Info.broadphase, this->Info.solver, this->Info.collisionConfiguration);

	this->Info.dynamicsWorld->setGravity(btVector3(0.0f, -9.81f, 0.0f));
}
void PhysicsManager::Work(double realTime, double deltaTime)
{
	this->Info.dynamicsWorld->stepSimulation((float)deltaTime, 10);
	for(auto iter = this->RigidBodyObjs.begin();
		iter != this->RigidBodyObjs.end();
		++iter)
	{
		iter->second->Update();
	}
}
void PhysicsManager::Shutdown()
{
	if(this->Info.broadphase)				{ delete this->Info.broadphase; }
	if(this->Info.collisionConfiguration)	{ delete this->Info.collisionConfiguration; }
	if(this->Info.dispatcher)				{ delete this->Info.dispatcher; }
	if(this->Info.solver)					{ delete this->Info.solver; }
	if(this->Info.dynamicsWorld)			{ delete this->Info.dynamicsWorld; }
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