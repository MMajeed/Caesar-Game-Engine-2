#ifndef __VertexShader__
#define __VertexShader__

#include "Linker.h"
#include "COMSharedPtr.h"
#include <string>
#include <hash_map>
#include <ObjectEntity.h>
#include "GraphicCameraEntity.h"
#include "GraphicObjectEntity.h"
#include "CBSetup.h"
#include "TextureSetup.h"

class GraphicComponentDLL_API VertexShader
{
protected:
	VertexShader(){}
	void Init();
public:
	void Setup(const GraphicCameraEntity& camera, const GraphicObjectEntity& object);

	static std::shared_ptr<VertexShader> Spawn(const std::vector<char>& CompiledShader);
	static std::shared_ptr<VertexShader> Spawn(const std::string& fileName);
protected:
	COMSharedPtr<ID3D11VertexShader>	pVertexShader;
	COMSharedPtr<ID3D11Buffer>			pConstantBuffer;
	std::shared_ptr<CBSetup>		pCBSetup;
	std::vector<char>					CompiledShader;

	COMSharedPtr<ID3D11InputLayout> GetVertexLayout(std::string ID);
	COMSharedPtr<ID3D11InputLayout> GenerateInputLayout(std::string ID);

	std::shared_ptr<TextureSetup>		pTexture;

	std::hash_map<std::string, COMSharedPtr<ID3D11InputLayout>> InputLayoutMap;
};


#endif //__VertexShader__