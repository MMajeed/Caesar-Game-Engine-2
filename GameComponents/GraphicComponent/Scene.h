#ifndef __Scene__
#define __Scene__

#include "Linker.h"

#include <Entity.h>
#include <CameraEntity.h>
#include <ObjectEntity.h>
#include <hash_map>
#include <Vector.h>
#include <Vector.h>
#include <vector>
#include "SceneInfo.h"

namespace Scene
{
	GraphicComponentDLL_API void SetupSceneCameraInfo(const std::shared_ptr<CameraEntity>& camera, unsigned int width, unsigned int height, SceneInfo& si);
	GraphicComponentDLL_API void SetupSceneExtraInfo(const std::shared_ptr<CameraEntity>& camera, unsigned int width, unsigned int height, SceneInfo& si);
	GraphicComponentDLL_API SceneInfo SetupScene(const std::shared_ptr<CameraEntity>& camera, unsigned int width, unsigned int height);
	GraphicComponentDLL_API void SetupConstantBuffer(const SceneInfo& si);
	GraphicComponentDLL_API void SetupGlobalTexture(const SceneInfo& si);
	GraphicComponentDLL_API void ClearScreen(const SceneInfo& si);
	GraphicComponentDLL_API std::vector<DrawableObject> FilterScene(const std::hash_map<std::string, std::weak_ptr<ObjectEntity>>& objects, const SceneInfo& si);
	GraphicComponentDLL_API void DrawObjects(const std::vector<DrawableObject>& objects, const SceneInfo& si);
};

#endif //__Scene__