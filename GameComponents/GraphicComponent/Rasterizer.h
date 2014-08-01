#ifndef __Rasterizer__
#define __Rasterizer__

#include "Linker.h"

class GraphicCameraEntity;
class GraphicObjectEntity;

namespace Rasterizer
{
	void Setup(const GraphicCameraEntity& camera, const GraphicObjectEntity& object);
};


#endif //__Rasterizer__