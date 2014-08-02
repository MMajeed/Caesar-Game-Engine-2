#ifndef __TextureSetup__
#define __TextureSetup__

#include "Linker.h"

#include "GraphicCameraEntity.h"
#include "GraphicObjectEntity.h"
#include <vector>
#include <memory>

struct TextureInfo
{
	std::shared_ptr<BasicTexture> Texture;
	unsigned int Slot;
};

class GraphicComponentDLL_API TextureSetup
{
protected:
	TextureSetup();
	void Init(const std::vector<char>& compiledShader);
public:
	std::vector<TextureInfo> Setup(const GraphicCameraEntity& camera, const GraphicObjectEntity& object);
	static std::shared_ptr<TextureSetup> Spawn(const std::vector<char>& compiledGeometryShader);
protected:
	
	struct Textures
	{
		std::string Name;
		unsigned int Slot;
	};
	std::vector<TextureSetup::Textures> shaderTextures;
};
#endif //__TextureSetup__