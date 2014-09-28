#ifndef __Scene__
#define __Scene__

#include "Linker.h"

#include "GraphicCameraEntity.h"
#include "GraphicDrawSettingsEntity.h"
#include "GraphicObjectEntity.h"
#include <string>

namespace Scene
{
	GraphicComponentDLL_API void UpdateCameraEntities();
	GraphicComponentDLL_API void UpdateDrawSettingsEntities();
	GraphicComponentDLL_API void UpdateObjectEntities();

	GraphicComponentDLL_API
		std::shared_ptr<GraphicCameraEntity> GetCamera(const std::string& ID, unsigned int width, unsigned int height);
	GraphicComponentDLL_API
		std::shared_ptr<GraphicDrawSettingsEntity> GetDrawSettings(const std::string& ID);
	GraphicComponentDLL_API 
		const std::unordered_map<std::string, std::shared_ptr<GraphicObjectEntity>>& GetAllObjectEntities();

	GraphicComponentDLL_API	void ClearScreen(std::shared_ptr<GraphicCameraEntity> Camera, std::shared_ptr<GraphicDrawSettingsEntity> drawSettings );
	GraphicComponentDLL_API	void DrawObjects(std::shared_ptr<GraphicCameraEntity> camera, 
											 std::shared_ptr<GraphicDrawSettingsEntity> drawSettings,
											 const std::unordered_map<std::string, std::shared_ptr<GraphicObjectEntity>>& list);
};

#endif //__Scene__