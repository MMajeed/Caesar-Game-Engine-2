#ifndef __AnimationManager__
#define __AnimationManager__

#include "Linker.h"

#include <Interface.h>
#include <Singleton.h>
#include <InputKeysEnum.h>

class AnimationManager : public Interface, public CHL::Singleton<AnimationManager>
{
protected:
	AnimationManager();
	AnimationManager(const AnimationManager&) = delete;
	AnimationManager& operator=(const AnimationManager&) = delete;
	friend CHL::Singleton<AnimationManager>;
public:
	virtual void Init();
	virtual void Update(double realTime, double deltaTime);
	virtual void Work();
	virtual void Shutdown();
};

#endif //__AnimationManager__
