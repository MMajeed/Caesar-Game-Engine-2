#include "BallSocketBodyToPoint.h"

#include "PhysicsManager.h"
#include <Logger.h>

BallSocketBodyToPoint::BallSocketBodyToPoint()
{

}

void BallSocketBodyToPoint::Init()
{
	PhysicsManager& physicsManager = PhysicsManager::GetInstance();

	if(std::shared_ptr<RigidBody> spRigidBody = this->Info.RigidBody.second.lock())
	{
		btVector3 btPivot((float)this->Info.PivotPoint(0), (float)this->Info.PivotPoint(1), (float)this->Info.PivotPoint(2));
		this->pConstraint = new btPoint2PointConstraint(*spRigidBody->Info.Body, btPivot);

		physicsManager.Info.dynamicsWorld->addConstraint(this->pConstraint);
	}
}

std::shared_ptr<BallSocketBodyToPoint> BallSocketBodyToPoint::Spawn(std::string RigidBodyID, CML::Vec3 PivotPoint)
{
	std::shared_ptr<BallSocketBodyToPoint> newObject(new BallSocketBodyToPoint());

	PhysicsManager& physicsManager = PhysicsManager::GetInstance();

	auto iter = physicsManager.RigidBodyObjs.find(RigidBodyID);
	if(iter != physicsManager.RigidBodyObjs.end())
	{
		newObject->Info.RigidBody = std::pair<std::string, std::weak_ptr<RigidBody>>(RigidBodyID, iter->second);
	}
	else
	{
		Logger::LogError("Error creating BallSocketBodyToPoint, the rigid body could not be found");
	}

	newObject->Info.PivotPoint = PivotPoint;

	newObject->Init();

	return newObject;
}