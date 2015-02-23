#ifndef __iShaderFactory__
#define __iShaderFactory__

#include "Linker.h"
#include <Model.h>
#include <memory>
#include <string>

class CommonDLL_API iShaderFactory
{
public:
	virtual std::string VertexCreate(std::string fileName) = 0;
	virtual void VertexRelease(std::string ID) = 0;
	
	virtual std::string PixelCreate(std::string fileName) = 0;
	virtual void PixelRelease(std::string ID) = 0;

	virtual std::string GeometryCreate(std::string fileName) = 0;
	virtual void GeometryRelease(std::string ID) = 0;
};

#endif //__iShaderFactory__