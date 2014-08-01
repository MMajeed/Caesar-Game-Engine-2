#ifndef __PixelShader__
#define __PixelShader__

#include "Linker.h"
#include "COMSharedPtr.h"
#include <string>
#include <ObjectEntity.h>
#include "CBSetup.h"
#include "TextureSetup.h"

class GraphicComponentDLL_API PixelShader
{
protected:
	PixelShader(){}
	void Init();
public:
	void Setup(const GraphicCameraEntity& camera, const GraphicObjectEntity& object);

	static std::shared_ptr<PixelShader> Spawn(const std::vector<char>& compiledPixelShader);
	static std::shared_ptr<PixelShader> Spawn(const std::string& fileName);
protected:
	COMSharedPtr<ID3D11PixelShader>		pPixelShader;
	COMSharedPtr<ID3D11Buffer>			pConstantBuffer;
	std::shared_ptr<CBSetup>		pCBSetup;
	std::vector<char>					CompiledShader;

	std::shared_ptr<TextureSetup>		pTexture;
};


#endif //__PixelShader__