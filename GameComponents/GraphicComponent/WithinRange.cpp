#include "WithinRange.h"
#include "3DMath.h"
#include <ObjectINFO.h>

namespace WithinRange
{
	bool Filter(const SceneInfo& si, const DrawableObject& obj)
	{
		auto difference = Length(si.Eye, obj.ObjInfo->Location);
		if(difference > si.farZ)
		{
			return false;
		}
		
		return true;
	}
}