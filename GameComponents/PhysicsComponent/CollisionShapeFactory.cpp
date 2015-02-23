#include "CollisionShapeFactory.h"

#include <Message.h>
#include <GenerateGUID.h>
#include "Resource.h"
#include "PhysicsManager.h"
#include "BoxShape.h"
#include "CapsuleShape.h"
#include "ConeShape.h"
#include "CylinderShape.h"
#include "SphereShape.h"
#include "ConvexHullShape.h"
#include "ConvexTriangleMeshShape.h"

std::string CollisionShapeFactory::CreateBoxShape(CML::Vec3 halfExtent)
{
	class  CreateBoxShapeMessage : public Message
	{
	public:
		CreateBoxShapeMessage(CML::Vec3 halfExtent)
		{
			this->ID = CHL::GenerateGUID();
			this->halfExtent = halfExtent;
		}

		virtual Message::Status Work()
		{
			std::lock_guard<std::mutex> lock(PhysicsManager::GetInstance().mutex);
			std::shared_ptr<BoxShape> newObj = BoxShape::Spawn(this->halfExtent);
			Resource::CollisionShapeList[this->ID] = newObj;

			return Message::Status::Complete;
		}

		CML::Vec3 halfExtent;
		std::string	ID;
	};

	std::shared_ptr<CreateBoxShapeMessage> msg(new CreateBoxShapeMessage(halfExtent));
	PhysicsManager::GetInstance().SubmitMessage(msg);
	return msg->ID;
}
std::string CollisionShapeFactory::CreateCapsuleShape(double radius, double height)
{
	class  CreateCapsuleShape : public Message
	{
	public:
		CreateCapsuleShape(double radius, double height)
		{
			this->ID = CHL::GenerateGUID();
			this->radius = radius;
			this->height = height;
		}

		virtual Message::Status Work()
		{
			std::lock_guard<std::mutex> lock(PhysicsManager::GetInstance().mutex);
			std::shared_ptr<CapsuleShape> newObj = CapsuleShape::Spawn(this->radius, this->height);
			Resource::CollisionShapeList[this->ID] = newObj;

			return Message::Status::Complete;
		}

		double radius;
		double height;
		std::string	ID;
	};

	std::shared_ptr<CreateCapsuleShape> msg(new CreateCapsuleShape(radius, height));
	PhysicsManager::GetInstance().SubmitMessage(msg);
	return msg->ID;
}
std::string CollisionShapeFactory::CreateConeShape(double radius, double height)
{
	class  CreateConeShape : public Message
	{
	public:
		CreateConeShape(double radius, double height)
		{
			this->ID = CHL::GenerateGUID();
			this->radius = radius;
			this->height = height;
		}

		virtual Message::Status Work()
		{
			std::lock_guard<std::mutex> lock(PhysicsManager::GetInstance().mutex);
			std::shared_ptr<ConeShape> newObj = ConeShape::Spawn(this->radius, this->height);
			Resource::CollisionShapeList[this->ID] = newObj;

			return Message::Status::Complete;
		}

		double radius;
		double height;
		std::string	ID;
	};

	std::shared_ptr<CreateConeShape> msg(new CreateConeShape(radius, height));
	PhysicsManager::GetInstance().SubmitMessage(msg);
	return msg->ID;
}
std::string CollisionShapeFactory::CreateCylinderShape(CML::Vec3 halfExtent)
{
	class  CreateCylinderShapeMessage : public Message
	{
	public:
		CreateCylinderShapeMessage(CML::Vec3 halfExtent)
		{
			this->ID = CHL::GenerateGUID();
			this->halfExtent = halfExtent;
		}

		virtual Message::Status Work()
		{
			std::lock_guard<std::mutex> lock(PhysicsManager::GetInstance().mutex);
			std::shared_ptr<CylinderShape> newObj = CylinderShape::Spawn(this->halfExtent);
			Resource::CollisionShapeList[this->ID] = newObj;

			return Message::Status::Complete;
		}

		CML::Vec3 halfExtent;
		std::string	ID;
	};

	std::shared_ptr<CreateCylinderShapeMessage> msg(new CreateCylinderShapeMessage(halfExtent));
	PhysicsManager::GetInstance().SubmitMessage(msg);
	return msg->ID;
}
std::string CollisionShapeFactory::CreateSphereShape(double radius)
{
	class  CreateSphereShapeMessage : public Message
	{
	public:
		CreateSphereShapeMessage(double radius)
		{
			this->ID = CHL::GenerateGUID();
			this->radius = radius;
		}

		virtual Message::Status Work()
		{
			std::lock_guard<std::mutex> lock(PhysicsManager::GetInstance().mutex);
			std::shared_ptr<SphereShape> newObj = SphereShape::Spawn(this->radius);
			Resource::CollisionShapeList[this->ID] = newObj;

			return Message::Status::Complete;
		}

		double radius;
		double height;
		std::string	ID;
	};

	std::shared_ptr<CreateSphereShapeMessage> msg(new CreateSphereShapeMessage(radius));
	PhysicsManager::GetInstance().SubmitMessage(msg);
	return msg->ID;
}

std::string CollisionShapeFactory::CreateConvexHullShape(std::shared_ptr<CHL::Model> model)
{
	class  CreateConvexHullMesssage : public Message
	{
	public:
		CreateConvexHullMesssage(std::shared_ptr<CHL::Model> model)
		{
			this->ID = CHL::GenerateGUID();
			this->model = model;
		}

		virtual Message::Status Work()
		{
			std::lock_guard<std::mutex> lock(PhysicsManager::GetInstance().mutex);
			std::shared_ptr<ConvexHullShape> newObj = ConvexHullShape::Spawn(this->model);
			Resource::CollisionShapeList[this->ID] = newObj;

			return Message::Status::Complete;
		}

		std::shared_ptr<CHL::Model> model;
		std::string	ID;
	};
	std::shared_ptr<CHL::Model> newModel = std::shared_ptr<CHL::Model>(new CHL::Model(*model));
	std::shared_ptr<CreateConvexHullMesssage> msg(new CreateConvexHullMesssage(newModel));
	PhysicsManager::GetInstance().SubmitMessage(msg);
	return msg->ID;
}
std::string CollisionShapeFactory::CreateConvexTriangleMesh(std::shared_ptr<CHL::Model> model)
{
	class  CreateConvexTriangleMesssage : public Message
	{
	public:
		CreateConvexTriangleMesssage(std::shared_ptr<CHL::Model> model)
		{
			this->ID = CHL::GenerateGUID();
			this->model = model;
		}

		virtual Message::Status Work()
		{
			std::lock_guard<std::mutex> lock(PhysicsManager::GetInstance().mutex);
			std::shared_ptr<ConvexTriangleMeshShape> newObj = ConvexTriangleMeshShape::Spawn(this->model);
			Resource::CollisionShapeList[this->ID] = newObj;

			return Message::Status::Complete;
		}

		std::shared_ptr<CHL::Model> model;
		std::string	ID;
	};

	std::shared_ptr<CHL::Model> newModel = std::shared_ptr<CHL::Model>(new CHL::Model(*model));
	std::shared_ptr<CreateConvexTriangleMesssage> msg(new CreateConvexTriangleMesssage(newModel));
	PhysicsManager::GetInstance().SubmitMessage(msg);
	return msg->ID;
}

void CollisionShapeFactory::Release(std::string ID)
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

			Resource::CollisionShapeList.erase(this->ID);

			return Message::Status::Complete;
		}
	};

	std::shared_ptr<ReleaseMessage> msg(new ReleaseMessage(ID));
	PhysicsManager::GetInstance().SubmitMessage(msg);
}