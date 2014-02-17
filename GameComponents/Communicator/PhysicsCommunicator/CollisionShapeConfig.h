#ifndef __CollisionShapeConfigcpp__
#define __CollisionShapeConfigcpp__

#include "Linker.h"
#include <string>
#include <Vector.h>
#include <Model.h>
#include <memory>

namespace CollisionShapeConfig
{
	std::string CreateBoxShape(CML::Vec3 halfExtent);
	std::string CreateCapsuleShape(double radius, double height);
	std::string CreateConeShape(double radius, double height);
	std::string CreateCylinderShape(CML::Vec3 halfExtent);
	std::string CreateSphereShape(double radius);

	std::string CreateConvexHullShape(std::shared_ptr<CHL::Model> model);
	std::string CreateConvexTriangleMesh(std::shared_ptr<CHL::Model> model);

	void Release(std::string ID);
}

#endif //__CollisionShapeConfigcpp__
