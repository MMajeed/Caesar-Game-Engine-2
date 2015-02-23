#include "Resource.h"

namespace Resource
{
	std::unordered_map<std::string, std::shared_ptr<GraphicModel>> GraphicModelList;
	std::unordered_map<std::string, std::shared_ptr<BasicTexture>> TextureList;
	std::unordered_map<std::string, std::shared_ptr<ScreenCapture>> ScreenCaptureList;
	std::unordered_map<std::string, std::shared_ptr<ScreenCapture>> RigidBodyList;
	std::unordered_map<std::string, std::shared_ptr<VertexShader>> VertexShaderList;
	std::unordered_map<std::string, std::shared_ptr<GeometryShader>> GeometryShaderList;
	std::unordered_map<std::string, std::shared_ptr<PixelShader>> PixelShaderList;

	D3D D3DStuff;

	Win window;

	std::string DefaultCamera;
	std::string DefaultDrawSettings;
}