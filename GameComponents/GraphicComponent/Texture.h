#ifndef __Texture__
#define __Texture__

#include "Linker.h"

#include <Converter.h>
#include <boost/uuid/uuid_generators.hpp> // generators
#include <boost/uuid/uuid_io.hpp>         // streaming operators etc.

class Texture
{
public:
	Texture(){this->ID = CHL::ToString(boost::uuids::random_generator()()); }
	virtual void Init()				= 0;
	virtual void Destory()			= 0;
	virtual void SettupTexture()	= 0;
	virtual void CleanupTexture()	= 0;

	std::string	ID;

	virtual ~Texture(){}
};


#endif //__Texture__