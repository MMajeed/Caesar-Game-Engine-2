#ifndef __RigidBody__
#define __RigidBody__

#include "Linker.h"

#include <btBulletDynamicsCommon.h>
#include <string>
#include <Vector.h>
#include "CollisionShape.h"
#include <memory>
#include <Matrix.h>

class RigidBody
{
public:
	RigidBody();

	virtual void Init();
	virtual void Destory();
	void Update();

	void ApplyTorque(CML::Vec3 v);
	void ApplyCentralForce(CML::Vec3 v);

	CML::Vec3 GetLocation();
	CML::Vec4 GetQuaRotation(); 
	CML::Matrix4x4 GetTranMatrix();

	struct
	{
		std::pair<std::string, std::weak_ptr<CollisionShape>> CollisionShape;
		btDefaultMotionState* DefaultMotionState;
		btRigidBody* Body;
		CML::Vec3 DefaultLocation;
		CML::Vec4 DefaultQuaRotation;
		CML::Vec3 Inertia;
		float Mass;
	}Info;

	struct
	{
		CML::Vec3 Location;
		CML::Vec4 QuaRotation;
		CML::Matrix4x4 TranMatrix;
	}Translation;

	static std::shared_ptr<RigidBody> Spawn(std::string CollisionShapeID,
											CML::Vec3 Location, 
											CML::Vec3 PYRRotation, 
											float mass,
											bool calculateIntertia, 
											CML::Vec3 intertia );
};

#endif //__RigidBody__
