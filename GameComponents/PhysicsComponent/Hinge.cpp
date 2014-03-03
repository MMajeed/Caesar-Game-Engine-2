#include "Hinge.h"

#include "PhysicsManager.h"
#include <Logger.h>

Hinge::Hinge()
{
	this->Info.BreakingThreshold = 0.0;
}

void Hinge::Init()
{
	PhysicsManager& physicsManager = PhysicsManager::GetInstance();

	if(std::shared_ptr<RigidBody> spRigidBodyA = this->Info.RigidBodyA.second.lock())
	{
		std::shared_ptr<btHingeConstraint> newConstraint;
		if(std::shared_ptr<RigidBody> spRigidBodyB = this->Info.RigidBodyB.second.lock())
		{
			btVector3 btPivotA((float)this->Info.PivotPointA(0), (float)this->Info.PivotPointA(1), (float)this->Info.PivotPointA(2));
			btVector3 btPivotB((float)this->Info.PivotPointB(0), (float)this->Info.PivotPointB(1), (float)this->Info.PivotPointB(2));

			btVector3 btAxisA((float)this->Info.AxesA(0), (float)this->Info.AxesA(1), (float)this->Info.AxesA(2));
			btVector3 btAxisB((float)this->Info.AxesB(0), (float)this->Info.AxesB(1), (float)this->Info.AxesB(2));

			btRigidBody* bodyA = spRigidBodyA->Info.Body.get();
			btRigidBody* bodyB = spRigidBodyB->Info.Body.get();

			newConstraint = std::shared_ptr<btHingeConstraint>(
									new btHingeConstraint(*bodyA, *bodyB, btPivotA, btPivotB, btAxisA, btAxisB));
		}
		else
		{
			btVector3 btPivotA((float)this->Info.PivotPointA(0), (float)this->Info.PivotPointA(1), (float)this->Info.PivotPointA(2));
			btRigidBody* bodyA = spRigidBodyA->Info.Body.get();

			btVector3 btAxisA((float)this->Info.AxesA(0), (float)this->Info.AxesA(1), (float)this->Info.AxesA(2));

			newConstraint = std::shared_ptr<btHingeConstraint>(
								new btHingeConstraint(*bodyA, btPivotA, btAxisA));
		}

		newConstraint->setBreakingImpulseThreshold((float)this->Info.BreakingThreshold);
		/*newConstraint->setLimit((float)this->Info.Low, (float)this->Info.High, 
								(float)this->Info.Softness, 
								(float)this->Info.BiasFactor, (float)this->Info.RelaxationFactor);*/
	/*	newConstraint->enableAngularMotor(true, 10.0, 1000.0);*/
		newConstraint->setMaxMotorImpulse(10.0);
		this->pConstraint = newConstraint;
		physicsManager.Info.dynamicsWorld->addConstraint(this->pConstraint.get());
	}
}


void Hinge::ApplyMotor(double Impulse)
{
	if(std::shared_ptr<btHingeConstraint> spHinge = std::dynamic_pointer_cast<btHingeConstraint>(this->pConstraint))
	{
	}
}

void Hinge::Destory()
{
	PhysicsManager& physicsManager = PhysicsManager::GetInstance();

	if(this->pConstraint)
	{
		physicsManager.Info.dynamicsWorld->removeConstraint(this->pConstraint.get());
	}
}

std::shared_ptr<Hinge> Hinge::Spawn(std::string RigidBodyIDA, CML::Vec3 PivotPointA, CML::Vec3 AxesA,
									std::string RigidBodyIDB, CML::Vec3 PivotPointB, CML::Vec3 AxesB,
									double BreakingThreshold,
									double Low,
									double High,
									double Softness,
									double BiasFactor,
									double RelaxationFactor)
{
	PhysicsManager& physicsManager = PhysicsManager::GetInstance();

	std::shared_ptr<Hinge> newObject(new Hinge());

	auto iter = physicsManager.RigidBodyObjs.find(RigidBodyIDA);
	if(iter != physicsManager.RigidBodyObjs.end())
	{
		newObject->Info.RigidBodyA = std::pair<std::string, std::weak_ptr<RigidBody>>(RigidBodyIDA, iter->second);
	}
	else
	{
		Logger::LogError("Error creating Hinge, the rigid body could not be found");
	}

	newObject->Info.PivotPointA = PivotPointA;
	newObject->Info.AxesA = AxesA;


	iter = physicsManager.RigidBodyObjs.find(RigidBodyIDB);
	if(iter != physicsManager.RigidBodyObjs.end())
	{
		newObject->Info.RigidBodyB = std::pair<std::string, std::weak_ptr<RigidBody>>(RigidBodyIDB, iter->second);
	}
	else
	{
		Logger::LogError("Error creating Hinge, the rigid body could not be found");
	}
	newObject->Info.PivotPointB = PivotPointB;
	newObject->Info.AxesB = AxesB;

	newObject->Info.BreakingThreshold = BreakingThreshold;
	newObject->Info.Low = Low;
	newObject->Info.High = High;
	newObject->Info.Softness = Softness;
	newObject->Info.BiasFactor = BiasFactor;
	newObject->Info.RelaxationFactor = RelaxationFactor;

	newObject->Init();

	return newObject;
}

std::shared_ptr<Hinge> Hinge::Spawn(std::string RigidBodyIDA, CML::Vec3 PivotPointA, CML::Vec3 AxesA,
									double BreakingThreshold,
									double Low,
									double High,
									double Softness,
									double BiasFactor,
									double RelaxationFactor)
{
	PhysicsManager& physicsManager = PhysicsManager::GetInstance();

	std::shared_ptr<Hinge> newObject(new Hinge());

	auto iter = physicsManager.RigidBodyObjs.find(RigidBodyIDA);
	if(iter != physicsManager.RigidBodyObjs.end())
	{
		newObject->Info.RigidBodyA = std::pair<std::string, std::weak_ptr<RigidBody>>(RigidBodyIDA, iter->second);
	}
	else
	{
		Logger::LogError("Error creating Hinge, the rigid body could not be found");
	}

	newObject->Info.PivotPointA = PivotPointA;
	newObject->Info.AxesA = AxesA;

	newObject->Info.BreakingThreshold = BreakingThreshold;
	newObject->Info.Low = Low;
	newObject->Info.High = High;
	newObject->Info.Softness = Softness;
	newObject->Info.BiasFactor = BiasFactor;
	newObject->Info.RelaxationFactor = RelaxationFactor;

	newObject->Init();

	return newObject;
}