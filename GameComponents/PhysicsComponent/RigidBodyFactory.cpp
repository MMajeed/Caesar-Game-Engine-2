#include "RigidBodyFactory.h"

#include <GenerateGUID.h>
#include <Components.h>
#include "Resource.h"
#include "RigidBody.h"

std::string RigidBodyFactory::Create(std::string CollisionShapeID,
						   CML::Vec3 Location,
						   CML::Vec3 PYRRotation,
						   float mass,
						   bool calculateIntertia,
						   CML::Vec3 intertia)
{
	std::string ID = CHL::GenerateGUID();

	Components::Physics->SubmitMessage([=]()
	{
		std::lock_guard<std::mutex> lock(Components::Physics->Mutex());

		std::shared_ptr<RigidBody> newObj = RigidBody::Spawn(CollisionShapeID, Location, PYRRotation, mass, calculateIntertia, intertia);
		Resource::RigidBodyList[ID] = newObj;

		return Message::Status::Complete;
	});

	return ID;
}

void RigidBodyFactory::ApplyTorque(std::string ID, CML::Vec3 v)
{
	Components::Physics->SubmitMessage([=]()
	{
		std::lock_guard<std::mutex> lock(Components::Physics->Mutex());

		const auto& rididBodies = Resource::RigidBodyList;

		auto iter = rididBodies.find(ID);
		if(iter != rididBodies.end())
		{
			iter->second->ApplyTorque(v);
		}

		return Message::Status::Complete;
	});
}
void RigidBodyFactory::ApplyCentralFroce(std::string ID, CML::Vec3 v)
{
	Components::Physics->SubmitMessage([=]()
	{
		std::lock_guard<std::mutex> lock(Components::Physics->Mutex());

		const auto& rididBodies = Resource::RigidBodyList;

		auto iter = rididBodies.find(ID);
		if(iter != rididBodies.end())
		{
			iter->second->ApplyCentralForce(v);
		}

		return Message::Status::Complete;
	});
}
void RigidBodyFactory::SetTorque(std::string ID, CML::Vec3 v)
{
	Components::Physics->SubmitMessage([=]()
	{
		std::lock_guard<std::mutex> lock(Components::Physics->Mutex());

		const auto& rididBodies = Resource::RigidBodyList;

		auto iter = rididBodies.find(ID);
		if(iter != rididBodies.end())
		{
			iter->second->SetTorque(v);
		}

		return Message::Status::Complete;
	});
}

CML::Vec3 RigidBodyFactory::GetTorque(std::string ID)
{
	CML::Vec3 returnValue;

	std::lock_guard<std::mutex> lock(Components::Physics->Mutex());
	
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

	std::lock_guard<std::mutex> lock(Components::Physics->Mutex());

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

	std::lock_guard<std::mutex> lock(Components::Physics->Mutex());

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

	std::lock_guard<std::mutex> lock(Components::Physics->Mutex());

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
	std::lock_guard<std::mutex> lock(Components::Physics->Mutex());

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
	Components::Physics->SubmitMessage([=]()
	{
		std::lock_guard<std::mutex> lock(Components::Physics->Mutex());

		Resource::RigidBodyList.erase(ID);

		return Message::Status::Complete;
	});
}