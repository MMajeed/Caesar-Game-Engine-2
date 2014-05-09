#ifndef __WithinRange__
#define __WithinRange__

#include <INFO.h>
#include "SceneInfo.h"

namespace WithinRange
{
	GraphicComponentDLL_API bool Filter(const SceneInfo& si, const DrawableObject& obj);
};


#endif //__WithinRange__