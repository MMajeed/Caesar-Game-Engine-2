#include "PhysicsFactorySetup.h"

#include "CollisionShapeFactory.h"
#include "ConstraintFactory.h"
#include "RigidBodyFactory.h"
#include "PhysicsManager.h"

namespace PhysicsFactorySetup
{
	PhysicsFactory::PhysicsItem Load()
	{
		PhysicsFactory::PhysicsItem returnValue;

		returnValue._CollisionShapeFactory = std::shared_ptr<CollisionShapeFactory>(new CollisionShapeFactory);
		returnValue._ConstraintFactory = std::shared_ptr<ConstraintFactory>(new ConstraintFactory);
		returnValue._RigidBodyFactory = std::shared_ptr<RigidBodyFactory>(new RigidBodyFactory);
		returnValue._PhysicsInterface = PhysicsManager::GetPointer();

		return returnValue;
	}
};