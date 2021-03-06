#ifndef __Hinge__
#define __Hinge__

#include "Linker.h"

#include "Constraint.h"
#include <Vector.h>
#include <memory>
#include "RigidBody.h"

class PhysicsComponentDLL_API Hinge : public Constraint
{
protected:
	Hinge();
public:
	virtual void Init();
	virtual void Destory();

	static std::shared_ptr<Hinge> Spawn(std::string RigidBodyIDA, CML::Vec3 PivotPointA, CML::Vec3 AxesA,
										double BreakingThreshold,
										double Low,
										double High,
										double Softness,
										double BiasFactor,
										double RelaxationFactor,
										double MaxMotorImpulse);
	static std::shared_ptr<Hinge> Spawn(std::string RigidBodyIDA, CML::Vec3 PivotPointA, CML::Vec3 AxesA,
										std::string RigidBodyIDB, CML::Vec3 PivotPointB, CML::Vec3 AxesB,
										double BreakingThreshold,
										double Low,
										double High,
										double Softness,
										double BiasFactor,
										double RelaxationFactor,
										double MaxMotorImpulse);

	struct
	{
		std::pair<std::string, std::weak_ptr<RigidBody>> RigidBodyA;
		CML::Vec3 PivotPointA;
		CML::Vec3 AxesA;
		std::pair<std::string, std::weak_ptr<RigidBody>> RigidBodyB;
		CML::Vec3 PivotPointB;
		CML::Vec3 AxesB;
		double BreakingThreshold;
		double Low;
		double High;
		double Softness;
		double BiasFactor;
		double RelaxationFactor;
		double MaxMotorImpulse;
	}Info;
};

#endif //__Hinge__
