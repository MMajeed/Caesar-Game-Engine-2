#ifndef __CollisionShapeConfig__
#define __CollisionShapeConfig__

#include "Linker.h"
#include <string>
#include <Vector.h>
#include <Model.h>
#include <memory>

namespace CollisionShapeConfig
{
	PhysicsCommunicatorDLL_API std::string CreateBoxShape(CML::Vec3 halfExtent);
	PhysicsCommunicatorDLL_API std::string CreateCapsuleShape(double radius, double height);
	PhysicsCommunicatorDLL_API std::string CreateConeShape(double radius, double height);
	PhysicsCommunicatorDLL_API std::string CreateCylinderShape(CML::Vec3 halfExtent);
	PhysicsCommunicatorDLL_API std::string CreateSphereShape(double radius);

	PhysicsCommunicatorDLL_API std::string CreateConvexHullShape(std::shared_ptr<CHL::Model> model);
	PhysicsCommunicatorDLL_API std::string CreateConvexTriangleMesh(std::shared_ptr<CHL::Model> model);

	PhysicsCommunicatorDLL_API void Release(std::string ID);
}

#endif //__CollisionShapeConfig__
