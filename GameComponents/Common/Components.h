#ifndef __Components__
#define __Components__

#include "Linker.h"

#include "AnimationFactory.h"
#include "PhysicsFactory.h"
#include "ScriptFactory.h"
#include "GraphicFactory.h"


namespace Components
{
	extern CommonDLL_API std::shared_ptr<AnimationFactory> Animation;
	extern CommonDLL_API std::shared_ptr<PhysicsFactory> Physics;
	extern CommonDLL_API std::shared_ptr<ScriptFactory> Script;
	extern CommonDLL_API std::shared_ptr<GraphicFactory> Graphic;
};

#endif //__Components__