#ifndef __ShaderSetup__
#define __ShaderSetup__

#include "Linker.h"
#include <string>
#include <ObjectEntity.h>
#include "SceneInfo.h"

namespace ShaderSetup
{
	void SetupVertexShader(std::string ID, std::shared_ptr<ObjectEntity> object, const SceneInfo& si);
	void SetupGeometryShader(std::string ID, std::shared_ptr<ObjectEntity> object, const SceneInfo& si);
	void SetupPixelShader(std::string ID, std::shared_ptr<ObjectEntity> object, const SceneInfo& si);

};


#endif //__ShaderSetup__