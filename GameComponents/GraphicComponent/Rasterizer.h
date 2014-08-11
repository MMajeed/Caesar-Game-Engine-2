#ifndef __Rasterizer__
#define __Rasterizer__

#include "Linker.h"
#include <memory>

class GraphicCameraEntity;
class GraphicObjectEntity;

namespace Rasterizer
{
	GraphicComponentDLL_API void Setup(std::shared_ptr<GraphicCameraEntity> camera, std::shared_ptr<GraphicObjectEntity> object);
};


#endif //__Rasterizer__