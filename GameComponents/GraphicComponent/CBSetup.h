#ifndef __CBSetup__
#define __CBSetup__

#include "Linker.h"

#include "CBVariables.h"
#include "GraphicCameraEntity.h"
#include "GraphicObjectEntity.h"
#include <vector>
#include <memory>

class GraphicComponentDLL_API CBSetup
{
protected:
	CBSetup();
	void Init(const std::vector<char>& compiledShader, unsigned int bufferNum);
public:
	void Run(std::shared_ptr<GraphicCameraEntity> camera, std::shared_ptr<GraphicObjectEntity> object);
	static std::shared_ptr<CBSetup> Spawn(const std::vector<char>& compiledGeometryShader, unsigned int bufferNum);

	const std::vector<char>& GetCBData();
	unsigned int GetCBSize();
protected:
	std::vector<char> cbufferData;
	std::vector<std::shared_ptr<CBVariables>> variables;

};
#endif //__CBSetup__