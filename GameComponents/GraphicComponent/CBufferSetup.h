#ifndef __CBufferSetup__
#define __CBufferSetup__

#include "Linker.h"

#include "COMSharedPtr.h"
#include "CBufferVariables.h"
#include <ObjectEntity.h>
#include "SceneInfo.h"
#include <vector>
#include <memory>

class GraphicComponentDLL_API CBufferSetup
{
protected:
	CBufferSetup();
	void Init(const std::vector<char>& compiledShader, unsigned int bufferNum);
public:
	void Run(std::shared_ptr<ObjectEntity> object, const SceneInfo& si);
	static std::shared_ptr<CBufferSetup> Spawn(const std::vector<char>& compiledGeometryShader, unsigned int bufferNum);

	const std::vector<char>& GetCBData();
	unsigned int GetCBSize();
protected:
	std::vector<char> cbufferData;
	std::vector<std::shared_ptr<CBufferVariables>> variables;

};

extern std::vector<char> bytes;
#endif //__CBufferSetup__