#ifndef __Texture__
#define __Texture__

#include "Linker.h"

#include <Converter.h>
#include "TypedefObject.h"

class Texture
{
public:
	Texture(const std::string& inputID) : ID(inputID){}
	virtual void Init()									    = 0;
	virtual void Destory()								    = 0;
	virtual void Update(double realTime, double deltaTime)	= 0;
	virtual void SettupTexture(int slot)	                = 0;
	virtual void CleanupTexture(int slot)	                = 0;
	virtual ~Texture(){}

	const std::string	ID;
};


#endif //__Texture__