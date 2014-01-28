#ifndef __SpotLightINFO__
#define __SpotLightINFO__

#include "Linker.h"
#include "LightINFO.h"
#include <Vector.h>

class SpotLightINFO : public LightINFO
{
public:
	CML::Vec4 Position;
	CML::Vec4 Direction;
	CML::Vec4 Attenuation;
	double Range;
	double Spot;

	virtual std::shared_ptr<Object> Get(const std::string& ID);
	virtual void Set(const std::string& ID, std::shared_ptr<Object> obj);
	virtual std::shared_ptr<INFO> Clone();
};

#endif //__SpotLightINFO__