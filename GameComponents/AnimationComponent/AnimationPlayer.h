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

	void Play(double delta);

	double GetCurrentPhase(std::shared_ptr<BasicAnimation> animation) const;
	double GetCurrentPhase() const;
	void SetCurrentPhase(double phasePercentage);

	static std::shared_ptr<AnimationPlayer> Spawn(std::string basicAnimationID,
												  double startPhase,
												  double animRate);

	const std::hash_map<std::string, CML::Matrix4x4>& JointsAnimatedTransformation() const;
	CML::Matrix4x4 GetSingleJoint(std::string jointName);
	void SetJoint(std::string name, const CML::Matrix4x4& mat);
protected:
	std::hash_map<std::string, CML::Matrix4x4> jointsAnimated;
	int		LastTranslationFrame;
	int		LastRotationFrame;
	int		LastScaleFrame;
	double	AnimTime;
	double	AnimRate;
	std::weak_ptr<BasicAnimation>	Animation;
};


#endif //__AnimationPlayer__