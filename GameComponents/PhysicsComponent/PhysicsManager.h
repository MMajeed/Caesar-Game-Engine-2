#ifndef __PhysicsManager__
#define __PhysicsManager__

#include "Linker.h"

#include <hash_map>
#include <string>
#include <Interface.h>
#include <Singleton.h>
#include <btBulletDynamicsCommon.h>
#include "RigidBody.h"
#include "CollisionShape.h"
#include "Constraint.h"

class PhysicsComponentDLL_API PhysicsManager : public Interface, public CHL::Singleton<PhysicsManager>
{
protected:
	PhysicsManager();
	PhysicsManager(const PhysicsManager&) = delete;
	PhysicsManager& operator=(const PhysicsManager&) = delete;
	friend CHL::Singleton<PhysicsManager>;
public:
	virtual void Init();
	virtual void Work(double realTime, double deltaTime);
	virtual void Shutdown();

	std::hash_map<std::string, std::shared_ptr<CollisionShape>> CollisionShapeObjs;
	void InsertCollisionShapeObj(const std::string& ID, std::shared_ptr<CollisionShape> obj);
	void RemoveCollisionShapeObj(const std::string& ID);

	std::hash_map<std::string, std::shared_ptr<RigidBody>> RigidBodyObjs;
	void InsertRigidBodyObj(const std::string& ID, std::shared_ptr<RigidBody> obj);
	void RemoveRigidBodyObj(const std::string& ID);

	std::hash_map<std::string, std::shared_ptr<Constraint>> ConstraintObjs;
	void InsertConstraintObj(const std::string& ID, std::shared_ptr<Constraint> obj);
	void RemoveConstraintObj(const std::string& ID);

	struct
	{
		std::shared_ptr<btBroadphaseInterface> broadphase;
		std::shared_ptr<btDefaultCollisionConfiguration> collisionConfiguration;
		std::shared_ptr<btCollisionDispatcher> dispatcher;
		std::shared_ptr<btSequentialImpulseConstraintSolver> solver;
		std::shared_ptr<btDiscreteDynamicsWorld> dynamicsWorld;
	}Info;
};

#endif //__PhysicsManager__
