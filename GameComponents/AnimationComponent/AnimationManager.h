#ifndef __AnimationManager__
#define __AnimationManager__

#include "Linker.h"

#include <Interface.h>
#include <Singleton.h>
#include <hash_map>
#include "BasicAnimation.h"
#include "AnimationPlayer.h"
#include "AnimationController.h"

class AnimationManager : public Interface, public CHL::Singleton<AnimationManager>
{
protected:
	AnimationManager();
	AnimationManager(const AnimationManager&) = delete;
	AnimationManager& operator=(const AnimationManager&) = delete;
	friend CHL::Singleton<AnimationManager>;
public:
	virtual void Init();
	virtual void Work(double realTime, double deltaTime);
	virtual void Shutdown();

	std::hash_map<std::string, std::shared_ptr<BasicAnimation>> AnimationsContainer;
	void InsertAnimation(const std::string& ID, std::shared_ptr<BasicAnimation> obj);
	void RemoveAnimation(const std::string& ID);
	const std::hash_map<std::string, std::shared_ptr<BasicAnimation>>& AllAnimation();

	std::hash_map<std::string, std::shared_ptr<AnimationPlayer>> AnimationsPlayerContainer;
	void InsertAnimationPlayer(const std::string& ID, std::shared_ptr<AnimationPlayer> obj);
	void RemoveAnimationPlayer(const std::string& ID);
	const std::hash_map<std::string, std::shared_ptr<AnimationPlayer>>& AllAnimationPlayer();

	std::hash_map<std::string, std::shared_ptr<AnimationController>> AnimationControllerContainer;
	void InsertAnimationController(const std::string& ID, std::shared_ptr<AnimationController> obj);
	void RemoveAnimationController(const std::string& ID);
	const std::hash_map<std::string, std::shared_ptr<AnimationController>>& AllAnimationController();
};

#endif //__AnimationManager__
