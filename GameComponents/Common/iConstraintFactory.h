#ifndef __iConstraintFactory__
#define __iConstraintFactory__

#include "Linker.h"

#include <string>
#include <memory>
#include <Model.h>
#include <Vector.h>
#include <Matrix.h>

class CommonDLL_API iConstraintFactory
{
public:
	virtual std::string CreateBallSocket(std::string RigidBodyIDA, CML::Vec3 PivotPointA, double BreakingThreshold) = 0;
	virtual std::string CreateBallSocket(std::string RigidBodyIDA,
										 CML::Vec3 PivotPointA,
										 std::string RigidBodyIDB, CML::Vec3 PivotPointB,
										 double BreakingThreshold) = 0;

	virtual std::string CreateHinge(std::string RigidBodyIDA, CML::Vec3 PivotPointA, CML::Vec3 AxesA,
									double BreakingThreshold,
									double Low, double High,
									double Softness,
									double BiasFactor, double RelaxationFactor,
									double MaxMotorImpulse) = 0;
	virtual std::string CreateHinge(std::string RigidBodyIDA, CML::Vec3 PivotPointA, CML::Vec3 AxesA,
									std::string RigidBodyIDB, CML::Vec3 PivotPointB, CML::Vec3 AxesB,
									double BreakingThreshold,
									double Low, double High,
									double Softness,
									double BiasFactor, double RelaxationFactor,
									double MaxMotorImpulse) = 0;

	virtual void Release(std::string ID) = 0;
};

#endif //__iConstraintFactory__