#include "BallSocket.h"

#include "PhysicsManager.h"
#include <Logger.h>

BallSocket::BallSocket()
{
	this->Info.BreakingThreshold = 0.0;
}

void BallSocket::Init()
{
	PhysicsManager& physicsManager = PhysicsManager::GetInstance();

	if(std::shared_ptr<RigidBody> spRigidBodyA = this->Info.RigidBodyA.second.lock())
	{
		if(std::shared_ptr<RigidBody> spRigidBodyB = this->Info.RigidBodyB.second.lock())
		{
			btVector3 btPivotA((float)this->Info.PivotPointA(0), (float)this->Info.PivotPointA(1), (float)this->Info.PivotPointA(2));
			btVector3 btPivotB((float)this->Info.PivotPointB(0), (float)this->Info.PivotPointB(1), (float)this->Info.PivotPointB(2));

			btRigidBody* bodyA = spRigidBodyA->Info.Body.get();
			btRigidBody* bodyB = spRigidBodyB->Info.Body.get();

			this->pConstraint = std::shared_ptr<btPoint2PointConstraint>(
									new btPoint2PointConstraint(*bodyA, *bodyB,
																btPivotA, btPivotB));
		}
		else
		{
			btVector3 btPivotA((float)this->Info.PivotPointA(0), (float)this->Info.PivotPointA(1), (float)this->Info.PivotPointA(2));
			btRigidBody* bodyA = spRigidBodyA->Info.Body.get();

			this->pConstraint = std::shared_ptr<btPoint2PointConstraint>(
								new btPoint2PointConstraint(*bodyA, btPivotA));
		}

		this->pConstraint->setBreakingImpulseThreshold((float)this->Info.BreakingThreshold);

		physicsManager.Info.dynamicsWorld->addConstraint(this->pConstraint.get());
	}
}

void BallSocket::Destory()
{
	PhysicsManager& physicsManager = PhysicsManager::GetInstance();

	if(this->pConstraint)
	{
		physicsManager.Info.dynamicsWorld->removeConstraint(this->pConstraint.get());
	}
}

std::shared_ptr<BallSocket> BallSocket::Spawn(std::string RigidBodyIDA, CML::Vec3 PivotPointA,
											  std::string RigidBodyIDB, CML::Vec3 PivotPointB,
											  double BreakingThreshold)
{
	PhysicsManager& physicsManager = PhysicsManager::GetInstance();

	std::shared_ptr<BallSocket> newObject(new BallSocket());

	auto iter = physicsManager.RigidBodyObjs.find(RigidBodyIDA);
	if(iter != physicsManager.RigidBodyObjs.end())
	{
		newObject->Info.RigidBodyA = std::pair<std::string, std::weak_ptr<RigidBody>>(RigidBodyIDA, iter->second);
	}
	else
	{
		Logger::LogError("Error creating BallSocket, the rigid body could not be found");
	}

	newObject->Info.PivotPointA = PivotPointA;

	
	iter = physicsManager.RigidBodyObjs.find(RigidBodyIDB);
	if(iter != physicsManager.RigidBodyObjs.end())
	{
		newObject->Info.RigidBodyB = std::pair<std::string, std::weak_ptr<RigidBody>>(RigidBodyIDB, iter->second);
	}
	else
	{
		Logger::LogError("Error creating BallSocket, the rigid body could not be found");
	}
	newObject->Info.PivotPointB = PivotPointB;

	newObject->Info.BreakingThreshold = BreakingThreshold;

	newObject->Init();

	return newObject;
}

std::shared_ptr<BallSocket> BallSocket::Spawn(std::string RigidBodyIDA, CML::Vec3 PivotPointA,
											  double BreakingThreshold)
{
	PhysicsManager& physicsManager = PhysicsManager::GetInstance();

	std::shared_ptr<BallSocket> newObject(new BallSocket());

	auto iter = physicsManager.RigidBodyObjs.find(RigidBodyIDA);
	if(iter != physicsManager.RigidBodyObjs.end())
	{
		newObject->Info.RigidBodyA = std::pair<std::string, std::weak_ptr<RigidBody>>(RigidBodyIDA, iter->second);
	}
	else
	{
		Logger::LogError("Error creating BallSocket, the rigid body could not be found");
	}

	newObject->Info.PivotPointA = PivotPointA;

	newObject->Info.BreakingThreshold = BreakingThreshold;

	newObject->Init();

	return newObject;
}