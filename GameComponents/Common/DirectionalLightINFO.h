#ifndef __DirectionalLightINFO__
#define __DirectionalLightINFO__

#include "Linker.h"
#include "LightINFO.h"
#include <Vector.h>

class DirectionalLightINFO : public LightINFO
{
public:
	CHL::Vec4 Direction;

	virtual std::shared_ptr<Object> Get(const std::string& ID);
	virtual void Set(const std::string& ID, std::shared_ptr<Object> obj);
	virtual std::shared_ptr<INFO> Clone();
};

#endif //__DirectionalLightINFO__