#ifndef __TextureFactory__
#define __TextureFactory__

#include "Linker.h"
#include <iTextureFactory.h>

class GraphicComponentDLL_API TextureFactory : public iTextureFactory
{
public:
	virtual std::string Create(std::string texture);
	virtual void Release(std::string ID);
};

#endif //__TextureFactory__