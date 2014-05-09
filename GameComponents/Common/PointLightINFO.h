#ifndef __PointLightINFO__
#define __PointLightINFO__

#include "Linker.h"
#include "LightINFO.h"
#include <Vector.h>

class CommonDLL_API PointLightINFO : public LightINFO
{
public:
	CML::Vec4 Position;
	CML::Vec4 Attenuation;
	double Range;

	virtual std::shared_ptr<Object> Get(const std::string& ID);
	virtual void Set(const std::string& ID, std::shared_ptr<Object> obj);
	virtual std::shared_ptr<INFO> Clone();
};

#endif //__PointLightINFO__