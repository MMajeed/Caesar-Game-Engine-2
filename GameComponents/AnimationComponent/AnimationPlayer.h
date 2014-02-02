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

	double GetCurrentPhase() const;
	void SetCurrentPhase(double phasePercentage);

	void SetSpeed(double speed);
	double GetSpeed();

	std::hash_map<std::string, CML::Vec3>& GetAllTranslation();
	std::hash_map<std::string, CML::Vec4>& GetAllRotation();
	std::hash_map<std::string, CML::Vec3>& GetAllScale();

	static std::shared_ptr<AnimationPlayer> Spawn(std::string basicAnimationID,
												  double startPhase,
												  double animRate);
protected:
	CML::Vec3 CaluclateTranslationJoint(const BasicAnimation::Joint& BANode);
	CML::Vec4 CaluclateRotationJoint(const BasicAnimation::Joint& BANode);
	CML::Vec3 CaluclateScaleJoint(const BasicAnimation::Joint& BANode);

	std::hash_map<std::string, unsigned int>		LastTranslationFrame;
	std::hash_map<std::string, unsigned int>		LastRotationFrame;
	std::hash_map<std::string, unsigned int>		LastScaleFrame;

	std::hash_map<std::string, unsigned int>		CurrentTranslationFrame;
	std::hash_map<std::string, unsigned int>		CurrentRotationFrame;
	std::hash_map<std::string, unsigned int>		CurrentScaleFrame;

	std::hash_map<std::string, CML::Vec3> CurrentTranslationJoint;
	std::hash_map<std::string, CML::Vec4> CurrentRotationJoint;
	std::hash_map<std::string, CML::Vec3> CurrentScaleJoint;

	double	AnimTime;
	double	AnimRate;

	std::weak_ptr<BasicAnimation>	Animation;

	double GetCurrentPhase(std::shared_ptr<BasicAnimation> animation) const;
};


#endif //__AnimationPlayer__