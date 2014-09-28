#ifndef __VertexShader__
#define __VertexShader__

#include "Linker.h"
#include "COMSharedPtr.h"
#include <string>
#include <unordered_map>
#include <ObjectEntity.h>
#include "GraphicCameraEntity.h"
#include "GraphicObjectEntity.h"
#include "CBSetup.h"
#include "TextureSetup.h"

class GraphicModel;
class GraphicComponentDLL_API VertexShader
{
protected:
	VertexShader(){}
	void Init();
public:
	void Setup(std::shared_ptr<GraphicCameraEntity> camera, std::shared_ptr<GraphicDrawSettingsEntity> drawSettings, std::shared_ptr<GraphicObjectEntity> object);

	static std::shared_ptr<VertexShader> Spawn(const std::vector<char>& CompiledShader);
	static std::shared_ptr<VertexShader> Spawn(const std::string& fileName);

	COMSharedPtr<ID3D11InputLayout> GenerateInputLayout(std::shared_ptr<GraphicModel> model);
protected:
	COMSharedPtr<ID3D11VertexShader>	pVertexShader;
	COMSharedPtr<ID3D11Buffer>			pConstantBuffer;
	std::shared_ptr<CBSetup>		pCBSetup;
	std::vector<char>					CompiledShader;

	std::shared_ptr<TextureSetup>		pTexture;
};


#endif //__VertexShader__