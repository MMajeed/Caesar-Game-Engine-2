#ifndef __RigidBodyConfig__
#define __RigidBodyConfig__

#include "Linker.h"
#include <string>
#include <Vector.h>
#include <Matrix.h>

namespace RigidBodyConfig
{
	std::string Create(std::string CollisionShapeID,
					   CML::Vec3 Location,
					   CML::Vec3 PYRRotation,
					   float mass,
					   float friction,
					   bool calculateIntertia,
					   CML::Vec3 intertia);
	void ApplyTorque(std::string ID, CML::Vec3 v);
	void ApplyCentralFroce(std::string ID, CML::Vec3 v);
	CML::Vec3 GetLocation(std::string ID);
	CML::Vec4 GetQuaRotation(std::string ID);
	CML::Matrix4x4 GetTranslation(std::string ID);
	void Release(std::string ID);
}

#endif //__RigidBodyConfig__
