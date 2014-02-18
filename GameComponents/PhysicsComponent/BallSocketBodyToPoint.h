#ifndef __BallSocketBodyToPoint__
#define __BallSocketBodyToPoint__

#include "Linker.h"

#include "Constraint.h"
#include <Vector.h>
#include <memory>
#include "RigidBody.h"

class BallSocketBodyToPoint : public Constraint
{
public:
	BallSocketBodyToPoint();

	virtual void Init();

	static std::shared_ptr<BallSocketBodyToPoint> Spawn(std::string RigidBodyID, CML::Vec3 PivotPoint);

	struct
	{
		CML::Vec3 PivotPoint;
		std::pair<std::string, std::weak_ptr<RigidBody>> RigidBody;
	}Info;
};

#endif //__BallSocketBodyToPoint__
