#ifndef __iCollisionShapeFactory__
#define __iCollisionShapeFactory__

#include "Linker.h"

#include <string>
#include <memory>
#include <Model.h>
#include <Vector.h>
#include <Matrix.h>

class CommonDLL_API iCollisionShapeFactory
{
public:
	virtual std::string CreateBoxShape(CML::Vec3 halfExtent) = 0;
	virtual std::string CreateCapsuleShape(double radius, double height) = 0;
	virtual std::string CreateConeShape(double radius, double height) = 0;
	virtual std::string CreateCylinderShape(CML::Vec3 halfExtent) = 0;
	virtual std::string CreateSphereShape(double radius) = 0;

	virtual std::string CreateConvexHullShape(std::shared_ptr<CHL::Model> model) = 0;
	virtual std::string CreateConvexTriangleMesh(std::shared_ptr<CHL::Model> model) = 0;

	virtual void Release(std::string ID) = 0;
};

#endif //__iCollisionShapeFactory__