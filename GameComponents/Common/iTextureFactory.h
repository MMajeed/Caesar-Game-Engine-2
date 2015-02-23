#ifndef __iTextureFactory__
#define __iTextureFactory__

#include "Linker.h"
#include <memory>
#include <string>

class CommonDLL_API iTextureFactory
{
public:
	virtual std::string Create(std::string texture) = 0;
	virtual void Release(std::string ID) = 0;
};

#endif //__iTextureFactory__