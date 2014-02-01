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
	void SetSpeed(double speed);

	static std::shared_ptr<AnimationPlayer> Spawn(std::string basicAnimationID,
												  double startPhase,
												  double animRate);

	const std::hash_map<std::string, CML::Matrix4x4>& JointsAnimatedTransformation() const;
	CML::Matrix4x4 GetSingleJoint(std::string jointName);
	void SetJoint(std::string name, const CML::Matrix4x4& mat);
protected:
	void PlayRecursively(std::shared_ptr<BasicAnimation::Node> BANode, const CML::Matrix4x4& parentsJoint);
	enum class InterpolationType { Lerp, Slerp, };
	CML::Vec3 CaluclateTranslationJoint(std::shared_ptr<BasicAnimation::Node> BANode);
	CML::Vec4 CaluclateRotationJoint(std::shared_ptr<BasicAnimation::Node> BANode);
	CML::Vec3 CaluclateScaleJoint(std::shared_ptr<BasicAnimation::Node> BANode);
	void CalculateNewFrame(std::string Joint, const std::vector<BasicAnimation::Node::Key>& vecKeys);


	std::hash_map<std::string, unsigned int>		LastTranslationFrame;
	std::hash_map<std::string, unsigned int>		LastRotationFrame;
	std::hash_map<std::string, unsigned int>		LastScaleFrame;

	std::hash_map<std::string, unsigned int>		CurrentTranslationFrame;
	std::hash_map<std::string, unsigned int>		CurrentRotationFrame;
	std::hash_map<std::string, unsigned int>		CurrentScaleFrame;


	std::hash_map<std::string, CML::Matrix4x4> jointsAnimated;
	double	AnimTime;
	double	AnimRate;

	std::weak_ptr<BasicAnimation>	Animation;
};


#endif //__AnimationPlayer__