#ifndef __AnimationControllerConfig__
#define __AnimationControllerConfig__

#include "Linker.h"
#include <Matrix.h>
#include <memory>
#include <string>
#include <Node.h>

namespace AnimationControllerConfig
{
	std::string Create(std::string animPlayerID, std::shared_ptr<CHL::Node> rootNode);
	void Release(std::string ID);
	CML::Matrix4x4 GetSingleJoint(std::string ID, std::string JointName);
}

#endif //__AnimationControllerConfig__