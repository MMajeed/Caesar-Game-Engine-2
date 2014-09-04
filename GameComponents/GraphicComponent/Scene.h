#ifndef __Scene__
#define __Scene__

#include "Linker.h"

#include "GraphicCameraEntity.h"
#include "GraphicObjectEntity.h"
#include <string>

namespace Scene
{
	GraphicComponentDLL_API void SetCameraUpdate(bool v);
	GraphicComponentDLL_API void SetObjectUpdate(bool v);

	GraphicComponentDLL_API void UpdateCameraEntities();
	GraphicComponentDLL_API void UpdateObjectEntities();

	GraphicComponentDLL_API
		std::shared_ptr<GraphicCameraEntity> GetCamera(const std::string& ID, unsigned int width, unsigned int height);
	GraphicComponentDLL_API 
		const std::unordered_map<std::string, std::shared_ptr<GraphicObjectEntity>>& GetAllObjectEntities();

	GraphicComponentDLL_API
		void ClearScreen(std::shared_ptr<GraphicCameraEntity> Camera);
	GraphicComponentDLL_API
		void DrawObjects(std::shared_ptr<GraphicCameraEntity> camera, const std::unordered_map<std::string, std::shared_ptr<GraphicObjectEntity>>& list);
};

#endif //__Scene__