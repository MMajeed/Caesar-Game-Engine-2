#ifndef __Draw__
#define __Draw__

#include "Linker.h"

#include "GraphicCameraEntity.h"
#include "GraphicDrawSettingsEntity.h"
#include "GraphicObjectEntity.h"

namespace Draw
{
	GraphicComponentDLL_API 
		std::shared_ptr<VertexShader> GetVertexShader(std::shared_ptr<GraphicCameraEntity> camera, std::shared_ptr<GraphicDrawSettingsEntity> drawSettings, std::shared_ptr<GraphicObjectEntity> object);
	GraphicComponentDLL_API
		std::shared_ptr<GeometryShader> GetGeometryShader(std::shared_ptr<GraphicCameraEntity> camera, std::shared_ptr<GraphicDrawSettingsEntity> drawSettings, std::shared_ptr<GraphicObjectEntity> object);
	GraphicComponentDLL_API
		std::shared_ptr<PixelShader> GetPixelShader(std::shared_ptr<GraphicCameraEntity> camera, std::shared_ptr<GraphicDrawSettingsEntity> drawSettings, std::shared_ptr<GraphicObjectEntity> object);
	GraphicComponentDLL_API
		std::shared_ptr<GraphicModel> GetGraphicModel(std::shared_ptr<GraphicCameraEntity> camera, std::shared_ptr<GraphicDrawSettingsEntity> drawSettings, std::shared_ptr<GraphicObjectEntity> object);

	GraphicComponentDLL_API
		void Setup(std::shared_ptr<GraphicCameraEntity> camera, std::shared_ptr<GraphicDrawSettingsEntity> drawSettings, std::shared_ptr<GraphicObjectEntity> object);
};

#endif //__Draw__