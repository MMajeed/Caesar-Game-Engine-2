#ifndef __CollisionShapeFactory__
#define __CollisionShapeFactory__

#include "Linker.h"

#include <iCollisionShapeFactory.h>

class PhysicsComponentDLL_API CollisionShapeFactory : public iCollisionShapeFactory
{
public:
	virtual std::string CreateBoxShape(CML::Vec3 halfExtent);
	virtual std::string CreateCapsuleShape(double radius, double height);
	virtual std::string CreateConeShape(double radius, double height);
	virtual std::string CreateCylinderShape(CML::Vec3 halfExtent);
	virtual std::string CreateSphereShape(double radius);

	virtual std::string CreateConvexHullShape(std::shared_ptr<CHL::Model> model);
	virtual std::string CreateConvexTriangleMesh(std::shared_ptr<CHL::Model> model);

	virtual void Release(std::string ID);
};

#endif //__CollisionShapeFactory__