#ifndef __BallSocket__
#define __BallSocket__

#include "Linker.h"

#include "Constraint.h"
#include <Vector.h>
#include <memory>
#include "RigidBody.h"

class PhysicsComponentDLL_API BallSocket : public Constraint
{
protected:
	BallSocket();
public:
	virtual void Init(); 
	virtual void Destory();

	static std::shared_ptr<BallSocket> Spawn(std::string RigidBodyIDA, CML::Vec3 PivotPointA,
											 double BreakingThreshold);
	static std::shared_ptr<BallSocket> Spawn(std::string RigidBodyIDA, CML::Vec3 PivotPointA, 
											 std::string RigidBodyIDB, CML::Vec3 PivotPointB,
											 double BreakingThreshold);

	struct
	{
		std::pair<std::string, std::weak_ptr<RigidBody>> RigidBodyA;
		CML::Vec3 PivotPointA;
		std::pair<std::string, std::weak_ptr<RigidBody>> RigidBodyB;
		CML::Vec3 PivotPointB;
		double BreakingThreshold;
	}Info;
};

#endif //__BallSocket__
