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
	struct Node
	{
		CML::Matrix4x4 Transformation;
		std::shared_ptr<AnimationController::Node> Parent;
		std::vector<std::shared_ptr<AnimationController::Node>> Childern;

		std::string Name;
	};

	AnimationController();
	
	void Play(double delta);
	void CalculateJointsRecursively(std::shared_ptr<AnimationController::Node> BANode, const CML::Matrix4x4& parentsJoint);

	static std::shared_ptr<AnimationController> Spawn(std::shared_ptr<CHL::Node> rootNode, std::string animtionPlayerID);

	const std::hash_map<std::string, CML::Matrix4x4>& JointsAnimatedTransformation() const;
	CML::Matrix4x4 GetSingleJoint(std::string jointName);
	void SetJoint(std::string name, const CML::Matrix4x4& mat);
	
protected:
	std::weak_ptr<AnimationPlayer>	MainAnimation;

	std::hash_map<std::string, CML::Vec3> TranslationJoint;
	std::hash_map<std::string, CML::Vec4> RotationJoint;
	std::hash_map<std::string, CML::Vec3> ScaleJoint;

	std::hash_map<std::string, CML::Matrix4x4> jointsAnimated;
	std::shared_ptr<AnimationController::Node> RootNode;
};


#endif //__AnimationController__