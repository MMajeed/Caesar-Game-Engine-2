#ifndef __VertexShader__
#define __VertexShader__

#include "Linker.h"
#include "COMSharedPtr.h"
#include <string>
#include <ObjectEntity.h>
#include "SceneInfo.h"
#include "CBufferSetup.h"

class GraphicComponentDLL_API VertexShader
{
protected:
	VertexShader(){}
	void Init(const std::vector<char>& compiledShader);
public:
	void Setup(std::shared_ptr<ObjectEntity> object, const SceneInfo& si);

	static std::shared_ptr<VertexShader> Spawn(const std::vector<char>& compiledVertexShader);
protected:
	COMSharedPtr<ID3D11VertexShader>	pVertexShader;
	COMSharedPtr<ID3D11Buffer>			pConstantBuffer;
	std::shared_ptr<CBufferSetup>		pCBufferSetup;
};


#endif //__VertexShader__