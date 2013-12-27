#include "ShadowFilter.h"
#include <ObjectINFO.h>

namespace ShadowFilter
{
	bool Filter(const SP_INFO& object)
	{
		std::shared_ptr<ObjectINFO> objInfo = std::dynamic_pointer_cast<ObjectINFO>(object);

		if(!objInfo){ return false; }
		if(objInfo->Shadow == false){ return false; }
		if(objInfo->Depth == false){ return false; }

		return true;
	}
}