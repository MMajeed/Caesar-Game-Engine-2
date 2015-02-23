#ifndef __RigidBodyFactory__
#define __RigidBodyFactory__

#include "Linker.h"

#include <iRigidBodyFactory.h>

class PhysicsComponentDLL_API RigidBodyFactory : public iRigidBodyFactory
{
public:
	virtual std::string Create(std::string CollisionShapeID,
							   CML::Vec3 Location,
							   CML::Vec3 PYRRotation,
							   float mass,
							   bool calculateIntertia,
							   CML::Vec3 intertia);
	virtual void ApplyTorque(std::string ID, CML::Vec3 v);
	virtual void ApplyCentralFroce(std::string ID, CML::Vec3 v);
	virtual void SetTorque(std::string ID, CML::Vec3 v);

	virtual CML::Vec3 GetTorque(std::string ID);
	virtual CML::Vec3 GetForce(std::string ID);
	virtual CML::Vec3 GetLocation(std::string ID);
	virtual CML::Vec4 GetQuaRotation(std::string ID);
	virtual CML::Matrix4x4 GetTranslation(std::string ID);

	virtual void Release(std::string ID);
};

#endif //__RigidBodyFactory__