#include "ConstraintConfig.h"

#include <Message.h>
#include <GenerateGUID.h>
#include <PhysicsManager.h>
#include <BallSocketBodyToPoint.h>

namespace ConstraintConfig
{
	std::string CreateBallSocketBodyToPoint(std::string RigidBodyID, CML::Vec3 PivotPoint)
	{
		class  CreateBallSocketBodyToPointMessage : public Message
		{
		public:
			CreateBallSocketBodyToPointMessage(std::string RigidBodyID, CML::Vec3 PivotPoint)
			{
				this->ID = CHL::GenerateGUID();
				this->RigidBodyID = RigidBodyID;
				this->PivotPoint = PivotPoint;
			}

			virtual Message::Status Work()
			{
				std::lock_guard<std::mutex> lock(PhysicsManager::GetInstance().mutex);
				std::shared_ptr<BallSocketBodyToPoint> newObj = BallSocketBodyToPoint::Spawn(this->RigidBodyID, this->PivotPoint);
				PhysicsManager::GetInstance().InsertConstraintObj(this->ID, newObj);

				return Message::Status::Complete;
			}

			std::string	ID; 
			std::string RigidBodyID; 
			CML::Vec3 PivotPoint;
		};

		std::shared_ptr<CreateBallSocketBodyToPointMessage> msg(new CreateBallSocketBodyToPointMessage(RigidBodyID, PivotPoint));
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