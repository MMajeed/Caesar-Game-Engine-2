#ifndef __AnimationControllerFactory__
#define __AnimationControllerFactory__

#include "Linker.h"

#include <iAnimationControllerFactory.h>
#include <mutex>

class AnimationComponentDLL_API AnimationControllerFactory : public iAnimationControllerFactory
{
public:
	virtual std::string Create(std::string basicAnimID, std::shared_ptr<CHL::Node> rootNode, double speed);

	virtual void ChangeAnimation(std::string AnimationControllerID,
								 std::string basicAnimID,
								 TransitionType Transition,
								 double TransitionLength,
								 bool StartNextPhase);
	virtual std::string AddMinorAnimation(std::string AnimationControllerID,
										  std::string basicAnimID,
										  std::string startNodeName,
										  double startingRatio,
										  double stepRatio);
	virtual void RemoveMinorAnimation(std::string AnimationControllerID, std::string minorAnimationID);
	virtual void ChangeSpeed(std::string AnimationControllerID, double speed);
	virtual void Release(std::string ID);
	virtual CML::Matrix4x4 GetSingleJoint(std::string ID, std::string JointName);
};

#endif //__AnimationControllerFactory__
