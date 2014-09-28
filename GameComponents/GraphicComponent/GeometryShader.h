#ifndef __GeometryShader__
#define __GeometryShader__

#include "Linker.h"
#include "COMSharedPtr.h"
#include <string>
#include <ObjectEntity.h>
#include "CBSetup.h"
#include "TextureSetup.h"

class GraphicComponentDLL_API GeometryShader
{
protected:
	GeometryShader(){}
	void Init();
public:
	void Setup(std::shared_ptr<GraphicCameraEntity> camera, std::shared_ptr<GraphicDrawSettingsEntity> drawSettings, std::shared_ptr<GraphicObjectEntity> object);

	static std::shared_ptr<GeometryShader> Spawn(const std::vector<char>& compiledGeometryShader);
	static std::shared_ptr<GeometryShader> Spawn(const std::string& fileName);
protected:
	COMSharedPtr<ID3D11GeometryShader>	pGeometryShader;
	COMSharedPtr<ID3D11Buffer>			pConstantBuffer;
	std::shared_ptr<CBSetup>		pCBSetup;
	std::vector<char>					CompiledShader;

	std::shared_ptr<TextureSetup>		pTexture;
};


#endif //__GeometryShader__