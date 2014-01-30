#ifndef __ShadowFilter__
#define __ShadowFilter__

#include <ObjectINFO.h>
#include "SceneInfo.h" 

namespace ShadowFilter 
{
	bool Filter(const SceneInfo& si, const DrawableObject& obj);
};


#endif //__ShadowFilter__