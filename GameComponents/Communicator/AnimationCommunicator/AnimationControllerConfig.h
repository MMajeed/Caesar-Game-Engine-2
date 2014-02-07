#ifndef __AnimationControllerConfig__
#define __AnimationControllerConfig__

#include "Linker.h"
#include <Matrix.h>
#include <memory>
#include <string>
#include <Node.h>

namespace AnimationControllerConfig
{
	std::string Create(std::string basicAnimID, std::shared_ptr<CHL::Node> rootNode, double speed);
	enum class TransitionType{ None = 0, CrossFade = 1, SnapShot = 2, TimeSync = 3 };
	void ChangeAnimation(std::string AnimationControllerID,
						 std::string basicAnimID, 
						 TransitionType Transition, 
						 double TransitionLength, 
						 bool StartNextPhase);
	std::string AddMinorAnimation(std::string AnimationControllerID, 
								  std::string basicAnimID,
								  std::string startNodeName,
								  double startingRatio, 
								  double stepRatio);
	void RemoveMinorAnimation(std::string AnimationControllerID, std::string minorAnimationID);
	void ChangeSpeed(std::string AnimationControllerID, double speed);
	void Release(std::string ID);
	CML::Matrix4x4 GetSingleJoint(std::string ID, std::string JointName);
}

#endif //__AnimationControllerConfig__