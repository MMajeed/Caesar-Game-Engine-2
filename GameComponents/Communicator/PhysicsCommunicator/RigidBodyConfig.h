#ifndef __RigidBodyConfig__
#define __RigidBodyConfig__

#include "Linker.h"
#include <string>
#include <Vector.h>
#include <Matrix.h>

namespace RigidBodyConfig
{
	PhysicsCommunicatorDLL_API
		std::string Create(std::string CollisionShapeID,
						   CML::Vec3 Location,
						   CML::Vec3 PYRRotation,
						   float mass,
						   bool calculateIntertia,
						   CML::Vec3 intertia);
	PhysicsCommunicatorDLL_API void ApplyTorque(std::string ID, CML::Vec3 v);
	PhysicsCommunicatorDLL_API void ApplyCentralFroce(std::string ID, CML::Vec3 v);
	PhysicsCommunicatorDLL_API void SetTorque(std::string ID, CML::Vec3 v);

	PhysicsCommunicatorDLL_API CML::Vec3 GetTorque(std::string ID);
	PhysicsCommunicatorDLL_API CML::Vec3 GetForce(std::string ID);
	PhysicsCommunicatorDLL_API CML::Vec3 GetLocation(std::string ID);
	PhysicsCommunicatorDLL_API CML::Vec4 GetQuaRotation(std::string ID);
	PhysicsCommunicatorDLL_API CML::Matrix4x4 GetTranslation(std::string ID);

	PhysicsCommunicatorDLL_API void Release(std::string ID);
}

#endif //__RigidBodyConfig__
