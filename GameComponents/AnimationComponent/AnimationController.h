#ifndef __AnimationController__
#define __AnimationController__

#include "Linker.h"

#include <memory>
#include <hash_map>
#include <Matrix.h>
#include "AnimationPlayer.h"

class AnimationController
{
public:
	AnimationController();

	void Play(double delta);

	static std::shared_ptr<AnimationController> Spawn(std::string animtionPlayerID);

	const std::hash_map<std::string, CML::Matrix4x4>& JointsAnimatedTransformation() const;

	CML::Matrix4x4 GetSingleJoint(std::string jointName);
protected:
	std::weak_ptr<AnimationPlayer>	Animation;
};


#endif //__AnimationController__