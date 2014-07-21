#ifndef __PixelShader__
#define __PixelShader__

#include "Linker.h"
#include "COMSharedPtr.h"
#include <string>
#include <ObjectEntity.h>
#include "SceneInfo.h"
#include "CBufferSetup.h"

class GraphicComponentDLL_API PixelShader
{
protected:
	PixelShader(){}
	void Init(const std::vector<char>& compiledShader);
public:
	void Setup(std::shared_ptr<ObjectEntity> object, const SceneInfo& si);

	static std::shared_ptr<PixelShader> Spawn(const std::vector<char>& compiledPixelShader);
protected:
	COMSharedPtr<ID3D11PixelShader>		pPixelShader;
	COMSharedPtr<ID3D11Buffer>			pConstantBuffer;
	std::shared_ptr<CBufferSetup>		pCBufferSetup;
};


#endif //__PixelShader__