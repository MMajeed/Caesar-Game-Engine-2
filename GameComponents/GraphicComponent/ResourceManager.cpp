#include "ResourceManager.h"

namespace ResourceManager
{
	ResourceManager::Resource<GraphicModel>		GraphicModelList;
	ResourceManager::Resource<BasicTexture>		TextureList;
	ResourceManager::Resource<ScreenCapture>	ScreenCaptureList;
	ResourceManager::Resource<VertexShader>		VertexShaderList;
	ResourceManager::Resource<GeometryShader>	GeometryShaderList;
	ResourceManager::Resource<PixelShader>		PixelShaderList;
}