#ifndef __OBJECTINFO__
#define __OBJECTINFO__

#include "Linker.h"
#include "INFO.h"
#include <Vector.h>
#include <hash_map>

class ObjectINFO : public INFO
{
public:
	CHL::Vec4 Location;
	CHL::Vec4 Rotation;
	CHL::Vec4 Scale;
	CHL::Vec4 Diffuse;
	CHL::Vec4 Ambient;
	CHL::Vec4 Specular;
	std::string DrawObjID;
	std::hash_map<unsigned int, std::string> TextureVecs;

	virtual std::shared_ptr<Object> Get(const std::string& ID);
	virtual void Set(const std::string& ID, std::shared_ptr<Object> obj);
	virtual std::shared_ptr<INFO> Clone();
};

#endif //__OBJECTINFO__