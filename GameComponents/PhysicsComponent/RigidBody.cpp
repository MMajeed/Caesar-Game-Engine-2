#include "RigidBody.h"

#include "PhysicsManager.h"
#include <MathFunctions.h>
#include <Logger.h>

RigidBody::RigidBody()
{
}

void RigidBody::Init()
{
	PhysicsManager& physicsManager = PhysicsManager::GetInstance();

	if(std::shared_ptr<CollisionShape> spShape = this->Info.CollisionShape.second.lock())
	{
		btVector3 btLocation((float)this->Info.DefaultLocation(0), 
							 (float)this->Info.DefaultLocation(1), 
							 (float)this->Info.DefaultLocation(2));
		btQuaternion btQuaternion((float)this->Info.DefaultQuaRotation(0), 
								  (float)this->Info.DefaultQuaRotation(1), 
								  (float)this->Info.DefaultQuaRotation(2), 
								  (float)this->Info.DefaultQuaRotation(3));

		this->Info.DefaultMotionState =
			std::shared_ptr<btDefaultMotionState>(new btDefaultMotionState(btTransform(btQuaternion, btLocation)));

		btCollisionShape* pCollisionShape = spShape->pCollisionShape.get();
		btDefaultMotionState* fallMotionState = this->Info.DefaultMotionState.get();
		btScalar mass = this->Info.Mass;
		btVector3 fallInertia((float)this->Info.Inertia(0), (float)this->Info.Inertia(1), (float)this->Info.Inertia(2));
		btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass, fallMotionState, pCollisionShape, fallInertia);
		this->Info.Body = std::shared_ptr<btRigidBody>(new btRigidBody(fallRigidBodyCI));

		physicsManager.Info.dynamicsWorld->addRigidBody(this->Info.Body.get());
	}
}
void RigidBody::Destory()
{
	PhysicsManager& physicsManager = PhysicsManager::GetInstance();

	if(this->Info.Body) 
	{
		physicsManager.Info.dynamicsWorld->removeRigidBody(this->Info.Body.get());
	}
}
void RigidBody::Update()
{
	btTransform trans;
	this->Info.Body->getMotionState()->getWorldTransform(trans);
	CML::Vec3 newLocation = {trans.getOrigin().x(), trans.getOrigin().y(), trans.getOrigin().z()};
	CML::Vec4 newRotation = {trans.getRotation().x(), trans.getRotation().y(), trans.getRotation().z(), trans.getRotation().w()};

	CML::Matrix4x4 translation = CML::TransformMatrix(newLocation, newRotation, {1.0, 1.0, 1.0});

	std::lock_guard<std::mutex> lock(PhysicsManager::GetInstance().mutex);

	this->Translation.Location = newLocation;
	this->Translation.QuaRotation = newRotation;
	this->Translation.TranMatrix = translation;
}

void RigidBody::ApplyTorque(CML::Vec3 v)
{
	btVector3 btV((float)v(0), (float)v(1), (float)v(2));
	this->Info.Body->applyTorque(btV);
	this->Info.Body->activate();
}
void RigidBody::ApplyCentralForce(CML::Vec3 v)
{
	btVector3 btV((float)v(0), (float)v(1), (float)v(2));
	this->Info.Body->applyCentralForce(btV);
	this->Info.Body->activate();
}

CML::Vec3 RigidBody::GetLocation()
{
	return this->Translation.Location;
}
CML::Vec4 RigidBody::GetQuaRotation()
{
	return this->Translation.QuaRotation;
}
CML::Matrix4x4 RigidBody::GetTranMatrix()
{
	return this->Translation.TranMatrix;
}

std::shared_ptr<RigidBody> RigidBody::Spawn(std::string CollisionShapeID,
											CML::Vec3 Location,
											CML::Vec3 PYRRotation,
											float mass,
											bool calculateIntertia,
											CML::Vec3 intertia)
{
	std::shared_ptr<RigidBody> newObject(new RigidBody());

	PhysicsManager& physicsManager = PhysicsManager::GetInstance();

	auto iter = physicsManager.CollisionShapeObjs.find(CollisionShapeID);
	if(iter != physicsManager.CollisionShapeObjs.end())
	{
		CML::Vec4 quaternionRotation = CML::PYRToQuaternion(PYRRotation(0), PYRRotation(1), PYRRotation(2));

		CML::Vec3 finalInertiaValue;
		if(calculateIntertia == true)
		{
			btVector3 btIntertia;
			iter->second->pCollisionShape->calculateLocalInertia(mass, btIntertia);
			finalInertiaValue = {btIntertia.x(), btIntertia.y(), btIntertia.z()};
		}
		else
		{
			finalInertiaValue = intertia;
		}

		newObject->Info.CollisionShape = std::pair<std::string, std::weak_ptr<CollisionShape>>(CollisionShapeID, iter->second);
		newObject->Info.Inertia = finalInertiaValue;
		newObject->Info.Mass = mass;
		newObject->Info.DefaultLocation = Location;
		newObject->Info.DefaultQuaRotation = quaternionRotation;

	}
	else
	{
		Logger::LogError("Error creating RigidBody, the collision shape could not be found");
	}

	newObject->Init();

	return newObject;
}