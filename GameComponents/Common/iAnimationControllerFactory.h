#ifndef __iAnimationControllerFactory__
#define __iAnimationControllerFactory__

#include "Linker.h"
#include <Matrix.h>
#include <memory>
#include <string>
#include <Node.h>

class CommonDLL_API iAnimationControllerFactory
{
public:
	enum class TransitionType{ None = 0, CrossFade = 1, SnapShot = 2, TimeSync = 3 };

	virtual std::string Create(std::string basicAnimID, std::shared_ptr<CHL::Node> rootNode, double speed) = 0;
	virtual void ChangeAnimation(std::string AnimationControllerID,
						 std::string basicAnimID,
						 TransitionType Transition,
						 double TransitionLength,
						 bool StartNextPhase) = 0;
	virtual std::string AddMinorAnimation(std::string AnimationControllerID,
								  std::string basicAnimID,
								  std::string startNodeName,
								  double startingRatio,
								  double stepRatio) = 0;
	virtual void RemoveMinorAnimation(std::string AnimationControllerID, std::string minorAnimationID) = 0;
	virtual void ChangeSpeed(std::string AnimationControllerID, double speed) = 0;
	virtual void Release(std::string ID) = 0;
	virtual CML::Matrix4x4 GetSingleJoint(std::string ID, std::string JointName) = 0;
};

#endif //__iAnimationControllerFactory__