#ifndef __AnimationPlayer__
#define __AnimationPlayer__

#include "Linker.h"

#include <memory>
#include "BasicAnimation.h"
#include <hash_map>

class AnimationPlayer
{
public:
	AnimationPlayer();

	void Play(float delta);

	double GetCurrentPhase(std::shared_ptr<BasicAnimation> animation) const;
	double GetCurrentPhase() const;
	void SetCurrentPhase(float phasePercentage);

	static std::shared_ptr<AnimationPlayer> Spawn(std::string basicAnimationID,
												  float startPhase,
												  float animRate);

	const std::hash_map<std::string, CHL::Matrix4x4> JointsAnimatedTransformation() const;

	const std::shared_ptr<BasicAnimation> GetAnimation() const;
protected:
	std::hash_map<std::string, CHL::Matrix4x4> jointsAnimated;

	double                   AnimTime;
	double                   AnimRate;
	std::size_t             CurrentFrame;
	std::size_t             PreviousFrame;
	std::string				AnimationID;
};


#endif //__AnimationPlayer__