#ifndef __AnimationController__
#define __AnimationController__

#include "Linker.h"

#include <memory>
#include <hash_map>
#include <Matrix.h>
#include "AnimationPlayer.h"
#include <vector>
#include <hash_map>

class AnimationComponentDLL_API AnimationController
{
protected:
	AnimationController();
public:
	struct Node
	{
		std::string Name;
		CML::Matrix4x4 Transformation;
		std::shared_ptr<AnimationController::Node> Parent;
		std::vector<std::shared_ptr<AnimationController::Node>> Childern;
	};
	struct MinorAnimation
	{
		std::shared_ptr<AnimationPlayer> Animation;
		std::string StartAtNode;
		double StartRatio;
		double StepRatio;
	};
	
	void Play(double delta);
	void UpdatePlayers(double delta);
	void UpdateMainJoints();
	void UpdateTransitionJoints();
	void UpdateAllMinorAnimations();
	void CalculateMinorAnimationRecursively(const MinorAnimation& ma, std::shared_ptr<AnimationController::Node> ACNode, double ratio);
	void CalculateJointsRecursively(std::shared_ptr<AnimationController::Node> ACNode, const CML::Matrix4x4& parentsJoint);
	

	enum class TransitionType{ None = 0, CrossFade = 1, SnapShot = 2, TimeSync = 3 };
	void ChangeAnimation(std::string basicAnimationID, TransitionType Transition, double TransitionLength, bool StartNextPhase);

	void AddMinorAnimation(std::string minorAnimationNewID, std::string basicAnimationID, std::string startAtNode, double startRatio, double stepRatio );
	void RemoveMinorAnimation(std::string minorAnimationID);

	static std::shared_ptr<AnimationController> Spawn(std::shared_ptr<CHL::Node> rootNode,
													  std::string basicAnimationID,
													  double speed);
	void LoadNodesRecursively(std::shared_ptr<AnimationController::Node>& ACNodes, const std::shared_ptr<CHL::Node>& CHLNode);

	void SetSpeed(double speed);
	double GetSpeed();

	const std::hash_map<std::string, CML::Matrix4x4>& JointsAnimatedTransformation() const;
	CML::Matrix4x4 GetSingleJoint(std::string jointName);
	void SetJoint(std::string name, const CML::Matrix4x4& mat);
protected:
	std::shared_ptr<AnimationPlayer> MainAnimation;
	std::hash_map<std::string, MinorAnimation> AllMinorAnimations;

	struct Transition
	{
		enum class TransitionState{
			CrossFade, SnapShot, TimeSync,
			CrossFadeNext, SnapShotNext, TimeSyncNext
		}State;

		std::shared_ptr<AnimationPlayer> TransitionAnimation;
		double MaxLength;
		double TimeSinceStart;
	}TransitionStage;

	std::hash_map<std::string, CML::Vec3> TranslationJoint;
	std::hash_map<std::string, CML::Vec4> RotationJoint;
	std::hash_map<std::string, CML::Vec3> ScaleJoint;

	std::hash_map<std::string, CML::Matrix4x4> jointsAnimated;

	std::shared_ptr<AnimationController::Node> RootNode;
	std::hash_map<std::string, std::shared_ptr<AnimationController::Node>> AllNodes;

	double	AnimRate;
};


#endif //__AnimationController__