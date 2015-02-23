#ifndef __AnimationManager__
#define __AnimationManager__

#include "Linker.h"

#include <Interface.h>
#include <Singleton.h>
#include <unordered_map>
#include "BasicAnimation.h"
#include "AnimationPlayer.h"
#include "AnimationController.h"

class AnimationComponentDLL_API AnimationManager : public Interface, public CHL::Singleton<AnimationManager>
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
};

#endif //__AnimationManager__
