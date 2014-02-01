#ifndef __AnimationPlayerConfig__
#define __AnimationPlayerConfig__

#include "Linker.h"
#include <Animation.h>
#include <Node.h>
#include <memory>
#include <string>

namespace AnimationPlayerConfig
{
	std::string Create(std::string basicAnimationID, double startPhase, double animRate);
	void SetPhase(std::string AnimationPlayerID, double phase);
	void SetSpeed(std::string AnimationPlayerID, double speed);
	void Release(std::string ID);
}

#endif //__AnimationConfig__