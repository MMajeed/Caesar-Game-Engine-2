#ifndef __Scene__
#define __Scene__

#include "Linker.h"

#include "GraphicCameraEntity.h"
#include "GraphicObjectEntity.h"
#include <string>

namespace Scene
{
	GraphicComponentDLL_API 
		GraphicCameraEntity GetCamera(const std::string& ID);
	GraphicComponentDLL_API 
		std::hash_map<std::string, GraphicObjectEntity> GetAllObjectEntities();

	GraphicComponentDLL_API
		void ClearScreen(const GraphicCameraEntity& Camera);
	GraphicComponentDLL_API
		void DrawObjects(const GraphicCameraEntity& Camera, std::hash_map<std::string, GraphicObjectEntity>& list);
};

#endif //__Scene__