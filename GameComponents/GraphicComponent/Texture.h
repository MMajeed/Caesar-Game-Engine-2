#ifndef __Texture__
#define __Texture__

#include "Linker.h"

#include <Converter.h>
#include <boost/uuid/uuid_generators.hpp> // generators
#include <boost/uuid/uuid_io.hpp>         // streaming operators etc.

class Texture
{
public:
	Texture(const std::string& inputID) : ID(inputID){}
	virtual void Init()				= 0;
	virtual void Destory()			= 0;
	virtual void SettupTexture()	= 0;
	virtual void CleanupTexture()   = 0;
	virtual ~Texture(){}

	const std::string	ID;
};


#endif //__Texture__