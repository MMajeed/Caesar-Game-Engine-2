#include "ShadowFilter.h"
#include <ObjectINFO.h>

namespace ShadowFilter
{
	bool Filter(const SceneInfo& si, const DrawableObject& obj)
	{
		if(obj.ObjInfo->Shadow == false){ return false; }
		if(obj.ObjInfo->Depth == false){ return false; }

		return true;
	}
}