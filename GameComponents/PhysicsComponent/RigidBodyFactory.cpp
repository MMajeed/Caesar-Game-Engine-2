#include "RigidBodyFactory.h"

#include <Message.h>
#include <GenerateGUID.h>
#include "PhysicsManager.h"
#include "Resource.h"
#include "RigidBody.h"

std::string RigidBodyFactory::Create(std::string CollisionShapeID,
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
			Resource::RigidBodyList[this->ID] = newObj;

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

void RigidBodyFactory::ApplyTorque(std::string ID, CML::Vec3 v)
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

			std::lock_guard<std::mutex> lock(PhysicsManager::GetInstance().mutex);

			const std::unordered_map<std::string, std::shared_ptr<RigidBody>>& rididBodies =
				Resource::RigidBodyList;

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
void RigidBodyFactory::ApplyCentralFroce(std::string ID, CML::Vec3 v)
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

			std::lock_guard<std::mutex> lock(PhysicsManager::GetInstance().mutex);

			const std::unordered_map<std::string, std::shared_ptr<RigidBody>>& rididBodies =
				Resource::RigidBodyList;

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
void RigidBodyFactory::SetTorque(std::string ID, CML::Vec3 v)
{
	class  SetTorqueMesssage : public Message
	{
	public:
		SetTorqueMesssage(std::string ID, CML::Vec3 v)
		{
			this->ID = ID;
			this->v = v;
		}

		virtual Message::Status Work()
		{
			PhysicsManager& physicsManager = PhysicsManager::GetInstance();

			std::lock_guard<std::mutex> lock(PhysicsManager::GetInstance().mutex);

			const std::unordered_map<std::string, std::shared_ptr<RigidBody>>& rididBodies =
				Resource::RigidBodyList;

			auto iter = rididBodies.find(ID);
			if(iter != rididBodies.end())
			{
				iter->second->SetTorque(v);
			}
			return Message::Status::Complete;
		}

		CML::Vec3 v;
		std::string	ID;
	};

	std::shared_ptr<SetTorqueMesssage> msg(new SetTorqueMesssage(ID, v));
	PhysicsManager::GetInstance().SubmitMessage(msg);
}

CML::Vec3 RigidBodyFactory::GetTorque(std::string ID)
{
	CML::Vec3 returnValue;
	PhysicsManager& physicsManager = PhysicsManager::GetInstance();

	std::lock_guard<std::mutex> lock(PhysicsManager::GetInstance().mutex);

	const std::unordered_map<std::string, std::shared_ptr<RigidBody>>& rididBodies =
		Resource::RigidBodyList;

	auto iter = rididBodies.find(ID);
	if(iter != rididBodies.end())
	{
		returnValue = iter->second->GetTorque();
	}
	return returnValue;
}
CML::Vec3 RigidBodyFactory::GetForce(std::string ID)
{
	CML::Vec3 returnValue;
	PhysicsManager& physicsManager = PhysicsManager::GetInstance();

	std::lock_guard<std::mutex> lock(PhysicsManager::GetInstance().mutex);

	const std::unordered_map<std::string, std::shared_ptr<RigidBody>>& rididBodies =
		Resource::RigidBodyList;

	auto iter = rididBodies.find(ID);
	if(iter != rididBodies.end())
	{
		returnValue = iter->second->GetForce();
	}
	return returnValue;
}
CML::Vec3 RigidBodyFactory::GetLocation(std::string ID)
{
	CML::Vec3 returnValue;
	PhysicsManager& physicsManager = PhysicsManager::GetInstance();

	std::lock_guard<std::mutex> lock(PhysicsManager::GetInstance().mutex);

	const std::unordered_map<std::string, std::shared_ptr<RigidBody>>& rididBodies =
		Resource::RigidBodyList;

	auto iter = rididBodies.find(ID);
	if(iter != rididBodies.end())
	{
		returnValue = iter->second->GetLocation();
	}
	return returnValue;
}
CML::Vec4 RigidBodyFactory::GetQuaRotation(std::string ID)
{
	CML::Vec4 returnValue;
	PhysicsManager& physicsManager = PhysicsManager::GetInstance();

	std::lock_guard<std::mutex> lock(PhysicsManager::GetInstance().mutex);

	const std::unordered_map<std::string, std::shared_ptr<RigidBody>>& rididBodies =
		Resource::RigidBodyList;

	auto iter = rididBodies.find(ID);
	if(iter != rididBodies.end())
	{
		returnValue = iter->second->GetQuaRotation();
	}
	return returnValue;
}
CML::Matrix4x4 RigidBodyFactory::GetTranslation(std::string ID)
{
	PhysicsManager& physicsManager = PhysicsManager::GetInstance();

	std::lock_guard<std::mutex> lock(PhysicsManager::GetInstance().mutex);

	const std::unordered_map<std::string, std::shared_ptr<RigidBody>>& rididBodies =
		Resource::RigidBodyList;

	auto iter = rididBodies.find(ID);
	if(iter != rididBodies.end())
	{
		return iter->second->GetTranMatrix();
	}
	else { return CML::Matrix4x4(); }
}

void RigidBodyFactory::Release(std::string ID)
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

			Resource::RigidBodyList.erase(this->ID);

			return Message::Status::Complete;
		}
	};

	std::shared_ptr<ReleaseMessage> msg(new ReleaseMessage(ID));
	PhysicsManager::GetInstance().SubmitMessage(msg);
}