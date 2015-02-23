#ifndef __Resource__
#define __Resource__

#include "Linker.h"

#include <string>
#include <unordered_map>
#include <memory>

#include "CollisionShape.h"
#include "Constraint.h"
#include "RigidBody.h"

#include <btBulletDynamicsCommon.h>

namespace Resource
{
	extern PhysicsComponentDLL_API std::unordered_map<std::string, std::shared_ptr<CollisionShape>> CollisionShapeList;
	extern PhysicsComponentDLL_API std::unordered_map<std::string, std::shared_ptr<Constraint>> ConstraintList;
	extern PhysicsComponentDLL_API std::unordered_map<std::string, std::shared_ptr<RigidBody>> RigidBodyList;

	extern PhysicsComponentDLL_API std::shared_ptr<btBroadphaseInterface> broadphase;
	extern PhysicsComponentDLL_API std::shared_ptr<btDefaultCollisionConfiguration> collisionConfiguration;
	extern PhysicsComponentDLL_API std::shared_ptr<btCollisionDispatcher> dispatcher;
	extern PhysicsComponentDLL_API std::shared_ptr<btSequentialImpulseConstraintSolver> solver;
	extern PhysicsComponentDLL_API std::shared_ptr<btDiscreteDynamicsWorld> dynamicsWorld;
	
};

#endif //__Resource__