#ifndef __iRigidBodyFactory__
#define __iRigidBodyFactory__

#include "Linker.h"

#include <string>
#include <memory>
#include <Model.h>
#include <Vector.h>
#include <Matrix.h>

class CommonDLL_API iRigidBodyFactory
{
public:
	virtual std::string Create(std::string CollisionShapeID,
							   CML::Vec3 Location,
							   CML::Vec3 PYRRotation,
							   float mass,
							   bool calculateIntertia,
							   CML::Vec3 intertia) = 0;
	virtual void ApplyTorque(std::string ID, CML::Vec3 v) = 0;
	virtual void ApplyCentralFroce(std::string ID, CML::Vec3 v) = 0;
	virtual void SetTorque(std::string ID, CML::Vec3 v) = 0;

	virtual CML::Vec3 GetTorque(std::string ID) = 0;
	virtual CML::Vec3 GetForce(std::string ID) = 0;
	virtual CML::Vec3 GetLocation(std::string ID) = 0;
	virtual CML::Vec4 GetQuaRotation(std::string ID) = 0;
	virtual CML::Matrix4x4 GetTranslation(std::string ID) = 0;

	virtual void Release(std::string ID) = 0;
};

#endif //__iRigidBodyFactory__