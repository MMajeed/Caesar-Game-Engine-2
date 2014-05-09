#ifndef __AnimationControllerConfig__
#define __AnimationControllerConfig__

#include "Linker.h"
#include <Matrix.h>
#include <memory>
#include <string>
#include <Node.h>

namespace AnimationControllerConfig
{
	AnimationCommunicatorDLL_API  
		std::string Create(std::string basicAnimID, std::shared_ptr<CHL::Node> rootNode, double speed);
	enum class TransitionType{ None = 0, CrossFade = 1, SnapShot = 2, TimeSync = 3 };
	AnimationCommunicatorDLL_API 
		void ChangeAnimation(std::string AnimationControllerID,
						 std::string basicAnimID, 
						 TransitionType Transition, 
						 double TransitionLength, 
						 bool StartNextPhase);
	AnimationCommunicatorDLL_API 
		std::string AddMinorAnimation(std::string AnimationControllerID,
								  std::string basicAnimID,
								  std::string startNodeName,
								  double startingRatio, 
								  double stepRatio);
	AnimationCommunicatorDLL_API void RemoveMinorAnimation(std::string AnimationControllerID, std::string minorAnimationID);
	AnimationCommunicatorDLL_API void ChangeSpeed(std::string AnimationControllerID, double speed);
	AnimationCommunicatorDLL_API void Release(std::string ID);
	AnimationCommunicatorDLL_API CML::Matrix4x4 GetSingleJoint(std::string ID, std::string JointName);
}

#endif //__AnimationControllerConfig__