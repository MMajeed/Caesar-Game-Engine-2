#ifndef __ConstraintFactory__
#define __ConstraintFactory__

#include "Linker.h"

#include <iConstraintFactory.h>

class PhysicsComponentDLL_API ConstraintFactory : public iConstraintFactory
{
public:
	virtual std::string CreateBallSocket(std::string RigidBodyIDA, CML::Vec3 PivotPointA, double BreakingThreshold);
	virtual std::string CreateBallSocket(std::string RigidBodyIDA,
										 CML::Vec3 PivotPointA,
										 std::string RigidBodyIDB, CML::Vec3 PivotPointB,
										 double BreakingThreshold);

	virtual std::string CreateHinge(std::string RigidBodyIDA, CML::Vec3 PivotPointA, CML::Vec3 AxesA,
									double BreakingThreshold,
									double Low, double High,
									double Softness,
									double BiasFactor, double RelaxationFactor,
									double MaxMotorImpulse);
	virtual std::string CreateHinge(std::string RigidBodyIDA, CML::Vec3 PivotPointA, CML::Vec3 AxesA,
									std::string RigidBodyIDB, CML::Vec3 PivotPointB, CML::Vec3 AxesB,
									double BreakingThreshold,
									double Low, double High,
									double Softness,
									double BiasFactor, double RelaxationFactor,
									double MaxMotorImpulse);

	virtual void Release(std::string ID);
};

#endif //__ConstraintFactory__