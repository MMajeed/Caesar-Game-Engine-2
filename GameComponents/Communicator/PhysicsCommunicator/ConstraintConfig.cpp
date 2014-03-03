#include "ConstraintConfig.h"

#include <Message.h>
#include <GenerateGUID.h>
#include <PhysicsManager.h>
#include <BallSocket.h>
#include <Hinge.h>

namespace ConstraintConfig
{
	std::string CreateBallSocket(std::string RigidBodyIDA, CML::Vec3 PivotPointA, double BreakingThreshold)
	{
		class CreateBallSocket : public Message
		{
		public:
			CreateBallSocket(std::string RigidBodyIDA, CML::Vec3 PivotPointA,
							 double BreakingThreshold)
			{
				this->ID = CHL::GenerateGUID();
				this->RigidBodyIDA = RigidBodyIDA;
				this->PivotPointA = PivotPointA;
				this->BreakingThreshold = BreakingThreshold;
			}

			virtual Message::Status Work()
			{
				std::lock_guard<std::mutex> lock(PhysicsManager::GetInstance().mutex);
				std::shared_ptr<BallSocket> newObj = BallSocket::Spawn(this->RigidBodyIDA, this->PivotPointA, this->BreakingThreshold);
				PhysicsManager::GetInstance().InsertConstraintObj(this->ID, newObj);

				return Message::Status::Complete;
			}

			std::string	ID;
			std::string RigidBodyIDA;
			CML::Vec3 PivotPointA;
			double BreakingThreshold;
		};

		std::shared_ptr<CreateBallSocket> msg(new CreateBallSocket(RigidBodyIDA, PivotPointA, BreakingThreshold));
		PhysicsManager::GetInstance().SubmitMessage(msg);
		return msg->ID;
	}
	std::string CreateBallSocket(std::string RigidBodyIDA, CML::Vec3 PivotPointA,
								 std::string RigidBodyIDB, CML::Vec3 PivotPointB,
								 double BreakingThreshold)
	{
		class CreateBallSocket : public Message
		{
		public:
			CreateBallSocket(std::string RigidBodyIDA, CML::Vec3 PivotPointA,
							 std::string RigidBodyIDB, CML::Vec3 PivotPointB,
							 double BreakingThreshold)
			{
				this->ID = CHL::GenerateGUID();
				this->RigidBodyIDA = RigidBodyIDA;
				this->PivotPointA = PivotPointA;
				this->RigidBodyIDB = RigidBodyIDB;
				this->PivotPointB = PivotPointB;
				this->BreakingThreshold = BreakingThreshold;
			}

			virtual Message::Status Work()
			{
				std::lock_guard<std::mutex> lock(PhysicsManager::GetInstance().mutex);
				std::shared_ptr<BallSocket> newObj = BallSocket::Spawn(this->RigidBodyIDA, this->PivotPointA, this->RigidBodyIDB, this->PivotPointB, this->BreakingThreshold);
				PhysicsManager::GetInstance().InsertConstraintObj(this->ID, newObj);

				return Message::Status::Complete;
			}

			std::string	ID;
			std::string RigidBodyIDA;
			CML::Vec3 PivotPointA;
			std::string RigidBodyIDB;
			CML::Vec3 PivotPointB;
			double BreakingThreshold;
		};

		std::shared_ptr<CreateBallSocket> msg(new CreateBallSocket(RigidBodyIDA, PivotPointA, RigidBodyIDB, PivotPointB, BreakingThreshold));
		PhysicsManager::GetInstance().SubmitMessage(msg);
		return msg->ID;
	}

	std::string CreateHinge(std::string RigidBodyIDA, CML::Vec3 PivotPointA, CML::Vec3 AxesA,
							double BreakingThreshold,
							double Low, double High,
							double Softness,
							double BiasFactor, double RelaxationFactor)
	{
		class CreateHingeSocket : public Message
		{
		public:
			CreateHingeSocket(std::string RigidBodyIDA, CML::Vec3 PivotPointA, CML::Vec3 AxesA,
							  double BreakingThreshold,
							  double Low, double High,
							  double Softness,
							  double BiasFactor, double RelaxationFactor)
			{
				this->ID = CHL::GenerateGUID();
				this->RigidBodyIDA = RigidBodyIDA;
				this->PivotPointA = PivotPointA;
				this->AxesA = AxesA;
				this->BreakingThreshold = BreakingThreshold;
				this->Low = Low;
				this->High = High;
				this->Softness = Softness;
				this->BiasFactor = BiasFactor;
				this->RelaxationFactor = RelaxationFactor;
			}

			virtual Message::Status Work()
			{
				std::lock_guard<std::mutex> lock(PhysicsManager::GetInstance().mutex);
				std::shared_ptr<Hinge> newObj =
					Hinge::Spawn(this->RigidBodyIDA, this->PivotPointA, this->AxesA,
					this->BreakingThreshold,
					this->Low, this->High,
					this->Softness,
					this->BiasFactor, this->RelaxationFactor);
				PhysicsManager::GetInstance().InsertConstraintObj(this->ID, newObj);

				return Message::Status::Complete;
			}

			std::string	ID;
			std::string RigidBodyIDA; CML::Vec3 PivotPointA; CML::Vec3 AxesA;
			double BreakingThreshold;
			double Low; double High;
			double Softness;
			double BiasFactor; double RelaxationFactor;
		};

		std::shared_ptr<CreateHingeSocket> msg(new CreateHingeSocket(RigidBodyIDA, PivotPointA, AxesA,
																	 BreakingThreshold,
																	 Low, High,
																	 Softness,
																	 BiasFactor, RelaxationFactor));
		PhysicsManager::GetInstance().SubmitMessage(msg);
		return msg->ID;
	}
	std::string CreateHinge(std::string RigidBodyIDA, CML::Vec3 PivotPointA, CML::Vec3 AxesA,
							std::string RigidBodyIDB, CML::Vec3 PivotPointB, CML::Vec3 AxesB,
							double BreakingThreshold,
							double Low, double High,
							double Softness,
							double BiasFactor, double RelaxationFactor)
	{
		class CreateHingeSocket : public Message
		{
		public:
			CreateHingeSocket(std::string RigidBodyIDA, CML::Vec3 PivotPointA, CML::Vec3 AxesA,
							  std::string RigidBodyIDB, CML::Vec3 PivotPointB, CML::Vec3 AxesB,
							  double BreakingThreshold,
							  double Low, double High,
							  double Softness,
							  double BiasFactor, double RelaxationFactor)
			{
				this->ID = CHL::GenerateGUID();
				this->RigidBodyIDA = RigidBodyIDA;
				this->PivotPointA = PivotPointA;
				this->AxesA = AxesA;
				this->RigidBodyIDB = RigidBodyIDB;
				this->PivotPointB = PivotPointB;
				this->AxesB = AxesB;
				this->BreakingThreshold = BreakingThreshold;
				this->Low = Low;
				this->High = High;
				this->Softness = Softness;
				this->BiasFactor = BiasFactor;
				this->RelaxationFactor = RelaxationFactor;
			}

			virtual Message::Status Work()
			{
				std::lock_guard<std::mutex> lock(PhysicsManager::GetInstance().mutex);
				std::shared_ptr<Hinge> newObj = 
					Hinge::Spawn(this->RigidBodyIDA, this->PivotPointA, this->AxesA,
								this->RigidBodyIDB, this->PivotPointB, this->AxesB,
								this->BreakingThreshold,
								this->Low, this->High,
								this->Softness, 
								this->BiasFactor, this->RelaxationFactor);
				PhysicsManager::GetInstance().InsertConstraintObj(this->ID, newObj);

				return Message::Status::Complete;
			}

			std::string	ID;
			std::string RigidBodyIDA; CML::Vec3 PivotPointA; CML::Vec3 AxesA;
			std::string RigidBodyIDB; CML::Vec3 PivotPointB; CML::Vec3 AxesB;
			double BreakingThreshold;
			double Low; double High;
			double Softness;
			double BiasFactor; double RelaxationFactor;
		};

		std::shared_ptr<CreateHingeSocket> msg(new CreateHingeSocket(RigidBodyIDA, PivotPointA, AxesA,
																	 RigidBodyIDB, PivotPointB, AxesB,
																	 BreakingThreshold,
																	 Low, High,
																	 Softness,
																	 BiasFactor, RelaxationFactor));
		PhysicsManager::GetInstance().SubmitMessage(msg);
		return msg->ID;
	}

	void Release(std::string ID)
	{
		class ReleaseMessage : public Message
		{
		public:
			std::string ID;
			ReleaseMessage(std::string ID)
			{
				this->ID = ID;
			}

			virtual Message::Status Work()
			{
				std::lock_guard<std::mutex> lock(PhysicsManager::GetInstance().mutex);

				PhysicsManager::GetInstance().RemoveConstraintObj(this->ID);

				return Message::Status::Complete;
			}
		};

		std::shared_ptr<ReleaseMessage> msg(new ReleaseMessage(ID));
		PhysicsManager::GetInstance().SubmitMessage(msg);
	}
}