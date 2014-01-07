#ifndef __Scene__
#define __Scene__

#include "Linker.h"

#include <INFO.h>
#include <CameraINFO.h>
#include <ObjectINFO.h>
#include <hash_map>
#include <Vector.h>
#include <Matrix.h>
#include <vector>
#include "SceneInfo.h"

namespace Scene
{
	SceneInfo SetupScene(const std::shared_ptr<CameraINFO>& camera, unsigned int width, unsigned int height);
	void SetupConstantBuffer(const SceneInfo& si);
	void ClearScreen(const SceneInfo& si);
	std::vector<DrawableObject> FilterScene(const std::hash_map<std::string, SP_INFO>& objects, const SceneInfo& si);
	void DrawObjects(const std::vector<DrawableObject>& objects, const SceneInfo& si);
};

#endif //__Scene__