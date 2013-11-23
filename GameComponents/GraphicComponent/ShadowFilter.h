#ifndef __ShadowFilter__
#define __ShadowFilter__

#include "Linker.h"

#include "SceneFilter.h"
#include <memory>

class ShadowFilter : public SceneFilter
{
public:
	ShadowFilter(const std::string& inputID);

	virtual bool Filter(SP_INFO);

	static std::shared_ptr<ShadowFilter> Spawn(const std::string& inputID);
};


#endif //__ShadowFilter__