#include "CollisionShapeFactory.h"

#include <GenerateGUID.h>
#include <Components.h>
#include "Resource.h"
#include "BoxShape.h"
#include "CapsuleShape.h"
#include "ConeShape.h"
#include "CylinderShape.h"
#include "SphereShape.h"
#include "ConvexHullShape.h"
#include "ConvexTriangleMeshShape.h"

std::string CollisionShapeFactory::CreateBoxShape(CML::Vec3 halfExtent)
{
	std::string ID = CHL::GenerateGUID();

	Components::Physics->SubmitMessage([=]()
	{
		std::lock_guard<std::mutex> lock(Components::Physics->Mutex());
		
		std::shared_ptr<BoxShape> newObj = BoxShape::Spawn(halfExtent);
		Resource::CollisionShapeList[ID] = newObj;

		return Message::Status::Complete;
	});

	return ID;
}
std::string CollisionShapeFactory::CreateCapsuleShape(double radius, double height)
{
	std::string ID = CHL::GenerateGUID();

	Components::Physics->SubmitMessage([=]()
	{
		std::lock_guard<std::mutex> lock(Components::Physics->Mutex());

		std::shared_ptr<CapsuleShape> newObj = CapsuleShape::Spawn(radius, height);
		Resource::CollisionShapeList[ID] = newObj;

		return Message::Status::Complete;
	});

	return ID;
}
std::string CollisionShapeFactory::CreateConeShape(double radius, double height)
{
	std::string ID = CHL::GenerateGUID();

	Components::Physics->SubmitMessage([=]()
	{
		std::lock_guard<std::mutex> lock(Components::Physics->Mutex());

		std::shared_ptr<ConeShape> newObj = ConeShape::Spawn(radius, height);
		Resource::CollisionShapeList[ID] = newObj;

		return Message::Status::Complete;
	});

	return ID;
}
std::string CollisionShapeFactory::CreateCylinderShape(CML::Vec3 halfExtent)
{
	std::string ID = CHL::GenerateGUID();

	Components::Physics->SubmitMessage([=]()
	{
		std::lock_guard<std::mutex> lock(Components::Physics->Mutex());

		std::shared_ptr<CylinderShape> newObj = CylinderShape::Spawn(halfExtent);
		Resource::CollisionShapeList[ID] = newObj;

		return Message::Status::Complete;
	});

	return ID;
}
std::string CollisionShapeFactory::CreateSphereShape(double radius)
{
	std::string ID = CHL::GenerateGUID();

	Components::Physics->SubmitMessage([=]()
	{
		std::lock_guard<std::mutex> lock(Components::Physics->Mutex());

		std::shared_ptr<SphereShape> newObj = SphereShape::Spawn(radius);
		Resource::CollisionShapeList[ID] = newObj;

		return Message::Status::Complete;
	});

	return ID;
}

std::string CollisionShapeFactory::CreateConvexHullShape(std::shared_ptr<CHL::Model> model)
{
	std::string ID = CHL::GenerateGUID();

	Components::Physics->SubmitMessage([=]()
	{
		std::lock_guard<std::mutex> lock(Components::Physics->Mutex());

		std::shared_ptr<ConvexHullShape> newObj = ConvexHullShape::Spawn(model);
		Resource::CollisionShapeList[ID] = newObj;

		return Message::Status::Complete;
	});

	return ID;
}
std::string CollisionShapeFactory::CreateConvexTriangleMesh(std::shared_ptr<CHL::Model> model)
{
	std::string ID = CHL::GenerateGUID();

	Components::Physics->SubmitMessage([=]()
	{
		std::lock_guard<std::mutex> lock(Components::Physics->Mutex());

		std::shared_ptr<ConvexTriangleMeshShape> newObj = ConvexTriangleMeshShape::Spawn(model);
		Resource::CollisionShapeList[ID] = newObj;

		return Message::Status::Complete;
	});

	return ID;
}

void CollisionShapeFactory::Release(std::string ID)
{
	Components::Physics->SubmitMessage([=]()
	{
		std::lock_guard<std::mutex> lock(Components::Physics->Mutex());

		Resource::CollisionShapeList.erase(ID);

		return Message::Status::Complete;
	});
}