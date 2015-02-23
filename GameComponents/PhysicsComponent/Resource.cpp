#include "Resource.h"

namespace Resource
{
	std::unordered_map<std::string, std::shared_ptr<CollisionShape>> CollisionShapeList;
	std::unordered_map<std::string, std::shared_ptr<Constraint>> ConstraintList;
	std::unordered_map<std::string, std::shared_ptr<RigidBody>> RigidBodyList;

	std::shared_ptr<btBroadphaseInterface> broadphase;
	std::shared_ptr<btDefaultCollisionConfiguration> collisionConfiguration;
	std::shared_ptr<btCollisionDispatcher> dispatcher;
	std::shared_ptr<btSequentialImpulseConstraintSolver> solver;
	std::shared_ptr<btDiscreteDynamicsWorld> dynamicsWorld;
};