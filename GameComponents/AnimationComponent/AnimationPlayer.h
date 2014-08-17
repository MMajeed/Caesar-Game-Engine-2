#ifndef __AnimationPlayer__
#define __AnimationPlayer__

#include "Linker.h"

#include <memory>
#include "BasicAnimation.h"
#include <unordered_map>

class AnimationComponentDLL_API AnimationPlayer
{
protected:
	AnimationPlayer();
public:
	void Play(double delta);

	double GetCurrentPhase() const;
	void SetCurrentPhase(double phasePercentage);

	std::unordered_map<std::string, CML::Vec3> CurrentTranslationJoint;
	std::unordered_map<std::string, CML::Vec4> CurrentRotationJoint;
	std::unordered_map<std::string, CML::Vec3> CurrentScaleJoint;

	static std::shared_ptr<AnimationPlayer> Spawn(std::string basicAnimationID, double startPhase);
protected:
	CML::Vec3 CaluclateTranslationJoint(const BasicAnimation::Joint& ACNode);
	CML::Vec4 CaluclateRotationJoint(const BasicAnimation::Joint& ACNode);
	CML::Vec3 CaluclateScaleJoint(const BasicAnimation::Joint& ACNode);

	std::unordered_map<std::string, unsigned int>		LastTranslationFrame;
	std::unordered_map<std::string, unsigned int>		LastRotationFrame;
	std::unordered_map<std::string, unsigned int>		LastScaleFrame;

	std::unordered_map<std::string, unsigned int>		CurrentTranslationFrame;
	std::unordered_map<std::string, unsigned int>		CurrentRotationFrame;
	std::unordered_map<std::string, unsigned int>		CurrentScaleFrame;

	double	AnimTime;

	std::weak_ptr<BasicAnimation>	Animation;

	double GetCurrentPhase(std::shared_ptr<BasicAnimation> animation) const;
};


#endif //__AnimationPlayer__