#ifndef __Process2D__
#define __Process2D__

#include <INFO.h>
#include "SceneInfo.h"

namespace Process2D
{
	GraphicComponentDLL_API bool Filter(const SceneInfo& si, const DrawableObject& obj);
};


#endif //__Process2D__