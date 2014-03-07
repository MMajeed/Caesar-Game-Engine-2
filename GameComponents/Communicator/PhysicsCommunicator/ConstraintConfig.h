#ifndef __ConstraintConfig__
#define __ConstraintConfig__

#include "Linker.h"
#include <string>
#include <Vector.h>

namespace ConstraintConfig
{
	std::string CreateBallSocket(std::string RigidBodyIDA, CML::Vec3 PivotPointA, double BreakingThreshold);
	std::string CreateBallSocket(std::string RigidBodyIDA, CML::Vec3 PivotPointA,
								 std::string RigidBodyIDB, CML::Vec3 PivotPointB,
								 double BreakingThreshold);

	std::string CreateHinge(std::string RigidBodyIDA, CML::Vec3 PivotPointA, CML::Vec3 AxesA, 
							double BreakingThreshold,
							double Low, double High,
							double Softness,
							double BiasFactor, double RelaxationFactor,
							double MaxMotorImpulse);
	std::string CreateHinge(std::string RigidBodyIDA, CML::Vec3 PivotPointA, CML::Vec3 AxesA,
							std::string RigidBodyIDB, CML::Vec3 PivotPointB, CML::Vec3 AxesB,
							double BreakingThreshold,
							double Low, double High,
							double Softness,
							double BiasFactor, double RelaxationFactor,
							double MaxMotorImpulse);

	void Release(std::string ID);
}

#endif //__ConstraintConfig__
