#include "PhysicsManager.h"

#include "PhysicsFactorySetup.h"
#include "Resource.h"
#include <Components.h>

PhysicsManager::PhysicsManager()
{
}
void PhysicsManager::Init()
{
	Resource::broadphase = std::shared_ptr<btDbvtBroadphase>(new btDbvtBroadphase());
	Resource::collisionConfiguration = std::shared_ptr<btDefaultCollisionConfiguration>(new btDefaultCollisionConfiguration());
	Resource::dispatcher = std::shared_ptr<btCollisionDispatcher>(new btCollisionDispatcher(Resource::collisionConfiguration.get()));
	Resource::solver = std::shared_ptr<btSequentialImpulseConstraintSolver>(new btSequentialImpulseConstraintSolver);
	Resource::dynamicsWorld = std::shared_ptr<btDiscreteDynamicsWorld>(
		new btDiscreteDynamicsWorld(Resource::dispatcher.get(),
									Resource::broadphase.get(), 
									Resource::solver.get(),
									Resource::collisionConfiguration.get()));

	Resource::dynamicsWorld->setGravity(btVector3(0.0f, -9.81f, 0.0f));
}
void PhysicsManager::Work(double realTime, double deltaTime)
{
	std::lock_guard<std::mutex> lock(this->mutex);

	Resource::dynamicsWorld->stepSimulation((float)deltaTime, 10);
	
}
void PhysicsManager::Shutdown()
{
}