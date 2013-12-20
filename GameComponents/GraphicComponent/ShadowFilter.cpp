#include "ShadowFilter.h"
#include <ObjectINFO.h>

ShadowFilter::ShadowFilter(const std::string& inputID)
	: SceneFilter(inputID)
{

}

bool ShadowFilter::Filter(const SP_INFO& object)
{
	std::shared_ptr<ObjectINFO> objInfo = std::dynamic_pointer_cast<ObjectINFO>(object);

	if(!objInfo){ return false; }
	if(objInfo->Shadow == false){ return false; }
	if(objInfo->Depth == false){ return false; }

	return true ;
}

std::shared_ptr<ShadowFilter> ShadowFilter::Spawn(const std::string& inputID)
{
	std::shared_ptr<ShadowFilter> returnValue(new ShadowFilter(inputID));
	return returnValue;
}