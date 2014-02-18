#include "RigidBodyConfig.h"
#include <Message.h>
#include <memory>
#include <GenerateGUID.h>
#include <PhysicsManager.h>
#include <RigidBody.h>


namespace RigidBodyConfig
{
	std::string Create(std::string CollisionShapeID,
					   CML::Vec3 Location,
					   CML::Vec3 PYRRotation,
					   float mass,
					   bool calculateIntertia,
					   CML::Vec3 intertia)
	{
		class  CreateMesssage : public Message
		{
		public:
			CreateMesssage(std::string CollisionShapeID,
						   CML::Vec3 Location,
						   CML::Vec3 PYRRotation,
						   float mass,
						   bool calculateIntertia,
						   CML::Vec3 intertia)
			{
				this->ID = CHL::GenerateGUID();
				this->CollisionShapeID = CollisionShapeID;
				this->Location = Location;
				this->PYRRotation = PYRRotation;
				this->mass = mass;
				this->calculateIntertia = calculateIntertia;
				this->intertia = intertia;
			}

			virtual Message::Status Work()
			{
				std::lock_guard<std::mutex> lock(PhysicsManager::GetInstance().mutex);
				std::shared_ptr<RigidBody> newObj = RigidBody::Spawn(this->CollisionShapeID, this->Location, this->PYRRotation, this->mass, this->calculateIntertia, this->intertia);
				PhysicsManager::GetInstance().InsertRigidBodyObj(this->ID, newObj);

				return Message::Status::Complete;
			}

			std::string CollisionShapeID;
			CML::Vec3 Location;
			CML::Vec3 PYRRotation;
			float mass;
			bool calculateIntertia;
			CML::Vec3 intertia;
			std::string	ID;
		};

		std::shared_ptr<CreateMesssage> msg(new CreateMesssage(CollisionShapeID, Location, PYRRotation, mass, calculateIntertia, intertia));
		PhysicsManager::GetInstance().SubmitMessage(msg);
		return msg->ID;
	}
	void ApplyTorque(std::string ID, CML::Vec3 v)
	{
		class  ApplyTorqueMesssage : public Message
		{
		public:
			ApplyTorqueMesssage(std::string ID, CML::Vec3 v)
			{
				this->ID = ID;
				this->v = v;
			}

			virtual Message::Status Work()
			{
				PhysicsManager& physicsManager = PhysicsManager::GetInstance();

				std::lock_guard<std::mutex> lock(physicsManager.mutex);

				const std::hash_map<std::string, std::shared_ptr<RigidBody>>& rididBodies =
					physicsManager.RigidBodyObjs;

				auto iter = rididBodies.find(ID);
				if(iter != rididBodies.end())
				{
					iter->second->ApplyTorque(v);
				}
				return Message::Status::Complete;
			}

			CML::Vec3 v;
			std::string	ID;
		};

		std::shared_ptr<ApplyTorqueMesssage> msg(new ApplyTorqueMesssage(ID, v));
		PhysicsManager::GetInstance().SubmitMessage(msg);
	}
	void ApplyCentralFroce(std::string ID, CML::Vec3 v)
	{
		class  ApplyCentralFroceMesssage : public Message
		{
		public:
			ApplyCentralFroceMesssage(std::string ID, CML::Vec3 v)
			{
				this->ID = ID;
				this->v = v;
			}

			virtual Message::Status Work()
			{
				PhysicsManager& physicsManager = PhysicsManager::GetInstance();

				std::lock_guard<std::mutex> lock(physicsManager.mutex);

				const std::hash_map<std::string, std::shared_ptr<RigidBody>>& rididBodies =
					physicsManager.RigidBodyObjs;

				auto iter = rididBodies.find(ID);
				if(iter != rididBodies.end())
				{
					iter->second->ApplyCentralForce(v);
				}
				return Message::Status::Complete;
			}

			CML::Vec3 v;
			std::string	ID;
		};

		std::shared_ptr<ApplyCentralFroceMesssage> msg(new ApplyCentralFroceMesssage(ID, v));
		PhysicsManager::GetInstance().SubmitMessage(msg);
	}
	CML::Vec3 GetLocation(std::string ID)
	{
		CML::Vec3 returnValue;
		PhysicsManager& physicsManager = PhysicsManager::GetInstance();

		std::lock_guard<std::mutex> lock(physicsManager.mutex);

		const std::hash_map<std::string, std::shared_ptr<RigidBody>>& rididBodies =
			physicsManager.RigidBodyObjs;

		auto iter = rididBodies.find(ID);
		if(iter != rididBodies.end())
		{
			returnValue = iter->second->GetLocation();
		}
		return returnValue;
	}
	CML::Vec4 GetQuaRotation(std::string ID)
	{
		CML::Vec3 returnValue;
		PhysicsManager& physicsManager = PhysicsManager::GetInstance();

		std::lock_guard<std::mutex> lock(physicsManager.mutex);

		const std::hash_map<std::string, std::shared_ptr<RigidBody>>& rididBodies =
			physicsManager.RigidBodyObjs;

		auto iter = rididBodies.find(ID);
		if(iter != rididBodies.end())
		{
			returnValue = iter->second->GetQuaRotation();
		}
		return returnValue;
	}
	CML::Matrix4x4 GetTranslation(std::string ID)
	{
		CML::Matrix4x4 returnValue;
		PhysicsManager& physicsManager = PhysicsManager::GetInstance();

		std::lock_guard<std::mutex> lock(physicsManager.mutex);

		const std::hash_map<std::string, std::shared_ptr<RigidBody>>& rididBodies =
			physicsManager.RigidBodyObjs;

		auto iter = rididBodies.find(ID);
		if(iter != rididBodies.end())
		{
			returnValue = iter->second->GetTranMatrix();
		}
		return returnValue;
	}

	void Release(std::string ID)
	{
		class ReleaseMessage : public Message
		{
		public:
			std::string ID;
			ReleaseMessage(std::string ID)
			{
				this->ID = ID;
			}

			virtual Message::Status Work()
			{
				std::lock_guard<std::mutex> lock(PhysicsManager::GetInstance().mutex);

				PhysicsManager::GetInstance().RemoveRigidBodyObj(this->ID);

				return Message::Status::Complete;
			}
		};

		std::shared_ptr<ReleaseMessage> msg(new ReleaseMessage(ID));
		PhysicsManager::GetInstance().SubmitMessage(msg);
	}
}