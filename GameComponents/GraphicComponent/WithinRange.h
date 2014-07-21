#ifndef __WithinRange__
#define __WithinRange__

#include <Entity.h>
#include "SceneInfo.h"

namespace WithinRange
{
	GraphicComponentDLL_API bool Filter(const SceneInfo& si, const DrawableObject& obj);
};


#endif //__WithinRange__