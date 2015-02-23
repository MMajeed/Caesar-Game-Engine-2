#include "ConstraintFactory.h"

#include <GenerateGUID.h>
#include <Components.h>
#include "Resource.h"
#include "BallSocket.h"
#include "Hinge.h"

std::string ConstraintFactory::CreateBallSocket(std::string RigidBodyIDA, CML::Vec3 PivotPointA, double BreakingThreshold)
{
	std::string ID = CHL::GenerateGUID();

	Components::Physics->SubmitMessage([=]()
	{
		std::lock_guard<std::mutex> lock(Components::Physics->Mutex());

		std::shared_ptr<BallSocket> newObj = BallSocket::Spawn(RigidBodyIDA, PivotPointA, BreakingThreshold);
		Resource::ConstraintList[ID] = newObj;

		return Message::Status::Complete;
	});

	return ID;
}
std::string ConstraintFactory::CreateBallSocket(std::string RigidBodyIDA,
												CML::Vec3 PivotPointA,
												std::string RigidBodyIDB, CML::Vec3 PivotPointB,
												double BreakingThreshold)
{
	std::string ID = CHL::GenerateGUID();

	Components::Physics->SubmitMessage([=]()
	{
		std::lock_guard<std::mutex> lock(Components::Physics->Mutex());

		std::shared_ptr<BallSocket> newObj = BallSocket::Spawn(RigidBodyIDA, PivotPointA, RigidBodyIDB, PivotPointB, BreakingThreshold);
		Resource::ConstraintList[ID] = newObj;

		return Message::Status::Complete;
	});

	return ID;
}

std::string ConstraintFactory::CreateHinge(std::string RigidBodyIDA, CML::Vec3 PivotPointA, CML::Vec3 AxesA,
										   double BreakingThreshold,
										   double Low, double High,
										   double Softness,
										   double BiasFactor, double RelaxationFactor,
										   double MaxMotorImpulse)
{
	std::string ID = CHL::GenerateGUID();

	Components::Physics->SubmitMessage([=]()
	{
		std::lock_guard<std::mutex> lock(Components::Physics->Mutex());

		std::shared_ptr<Hinge> newObj = Hinge::Spawn(RigidBodyIDA, PivotPointA, AxesA,
													 BreakingThreshold,
													 Low, High,
													 Softness,
													 BiasFactor, RelaxationFactor,
													 MaxMotorImpulse);
		Resource::ConstraintList[ID] = newObj;

		return Message::Status::Complete;
	});

	return ID;
}
std::string ConstraintFactory::CreateHinge(std::string RigidBodyIDA, CML::Vec3 PivotPointA, CML::Vec3 AxesA,
										   std::string RigidBodyIDB, CML::Vec3 PivotPointB, CML::Vec3 AxesB,
										   double BreakingThreshold,
										   double Low, double High,
										   double Softness,
										   double BiasFactor, double RelaxationFactor,
										   double MaxMotorImpulse)
{
	std::string ID = CHL::GenerateGUID();

	Components::Physics->SubmitMessage([=]()
	{
		std::lock_guard<std::mutex> lock(Components::Physics->Mutex());

		std::shared_ptr<Hinge> newObj = Hinge::Spawn(RigidBodyIDA, PivotPointA, AxesA,
													 RigidBodyIDB, PivotPointB, AxesB,
													 BreakingThreshold,
													 Low, High,
													 Softness,
													 BiasFactor, RelaxationFactor,
													 MaxMotorImpulse);
		Resource::ConstraintList[ID] = newObj;

		return Message::Status::Complete;
	});

	return ID;
}

void ConstraintFactory::Release(std::string ID)
{
	Components::Physics->SubmitMessage([=]()
	{
		std::lock_guard<std::mutex> lock(Components::Physics->Mutex());

		Resource::ConstraintList.erase(ID);

		return Message::Status::Complete;
	});
}