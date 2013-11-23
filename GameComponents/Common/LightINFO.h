#ifndef __LightINFO__
#define __LightINFO__

#include "Linker.h"
#include "INFO.h"
#include <Vector.h>

class LightINFO : public INFO
{
public:
	LightINFO();

	CHL::Vec4 Diffuse;
	CHL::Vec4 Ambient;
	CHL::Vec4 Specular;
	bool HasShadow;

	virtual std::shared_ptr<Object> Get(const std::string& ID);
	virtual void Set(const std::string& ID, std::shared_ptr<Object> obj);
	virtual std::shared_ptr<INFO> Clone() = 0;
};

#endif //__LightINFO__