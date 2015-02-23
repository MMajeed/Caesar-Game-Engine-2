#ifndef __ShaderFactory__
#define __ShaderFactory__

#include "Linker.h"
#include <iShaderFactory.h>

class GraphicComponentDLL_API ShaderFactory : public iShaderFactory
{
public:
	std::string VertexCreate(std::string fileName);
	void VertexRelease(std::string ID);

	std::string PixelCreate(std::string fileName);
	void PixelRelease(std::string ID);

	std::string GeometryCreate(std::string fileName);
	void GeometryRelease(std::string ID);
};

#endif //__ShaderFactory__