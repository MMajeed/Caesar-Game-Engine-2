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

class PhysicsManager : public Interface, public CHL::Singleton<PhysicsManager>
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

	struct
	{
		btBroadphaseInterface* broadphase; 
		btDefaultCollisionConfiguration* collisionConfiguration;
		btCollisionDispatcher* dispatcher;
		btSequentialImpulseConstraintSolver* solver;
		btDiscreteDynamicsWorld* dynamicsWorld;
	}Info;

	std::hash_map<std::string, std::shared_ptr<CollisionShape>> CollisionShapeObjs;
	void InsertCollisionShapeObj(const std::string& ID, std::shared_ptr<CollisionShape> obj);
	void RemoveCollisionShapeObj(const std::string& ID);

	std::hash_map<std::string, std::shared_ptr<RigidBody>> RigidBodyObjs;
	void InsertRigidBodyObj(const std::string& ID, std::shared_ptr<RigidBody> obj);
	void RemoveRigidBodyObj(const std::string& ID);
};

#endif //__PhysicsManager__
