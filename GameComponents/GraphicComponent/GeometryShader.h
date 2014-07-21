#ifndef __GeometryShader__
#define __GeometryShader__

#include "Linker.h"
#include "COMSharedPtr.h"
#include <string>
#include <ObjectEntity.h>
#include "SceneInfo.h"
#include "CBufferSetup.h"

class GraphicComponentDLL_API GeometryShader
{
protected:
	GeometryShader(){}
	void Init(const std::vector<char>& compiledShader);
public:
	void Setup(std::shared_ptr<ObjectEntity> object, const SceneInfo& si);

	static std::shared_ptr<GeometryShader> Spawn(const std::vector<char>& compiledGeometryShader);
protected:
	COMSharedPtr<ID3D11GeometryShader>	pGeometryShader;
	COMSharedPtr<ID3D11Buffer>			pConstantBuffer;
	std::shared_ptr<CBufferSetup>		pCBufferSetup;
};


#endif //__GeometryShader__