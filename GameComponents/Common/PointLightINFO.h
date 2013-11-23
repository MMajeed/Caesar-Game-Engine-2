#ifndef __PointLightINFO__
#define __PointLightINFO__

#include "Linker.h"
#include "LightINFO.h"
#include <Vector.h>

class PointLightINFO : public LightINFO
{
public:
	CHL::Vec4 Position;
	CHL::Vec4 Attenuation;
	double Range;

	virtual std::shared_ptr<Object> Get(const std::string& ID);
	virtual void Set(const std::string& ID, std::shared_ptr<Object> obj);
	virtual std::shared_ptr<INFO> Clone();
};

#endif //__PointLightINFO__