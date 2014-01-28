#ifndef __OBJECTINFO__
#define __OBJECTINFO__

#include "Linker.h"
#include "INFO.h"
#include <Vector.h>
#include <vector>
#include <array>

class ObjectINFO : public INFO
{
public:
	static const unsigned int USERDATASIZE = 16;

	CML::Vec4 Location;
	CML::Vec4 Rotation;
	CML::Vec4 Scale;
	CML::Vec4 Diffuse;
	CML::Vec4 Ambient;
	CML::Vec4 Specular;
	std::string DrawObjID;
	std::vector<std::string> Texture2DVecs;
	std::vector<std::string> TextureCubeVecs;
	bool Light;
	bool Shadow;
	bool Depth;

	std::array<float, USERDATASIZE> UserData;

	ObjectINFO();
	virtual std::shared_ptr<Object> Get(const std::string& ID);
	virtual void Set(const std::string& ID, std::shared_ptr<Object> obj);
	virtual std::shared_ptr<INFO> Clone();
};

#endif //__OBJECTINFO__