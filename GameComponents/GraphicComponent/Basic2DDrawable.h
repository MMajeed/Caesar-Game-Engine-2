#ifndef __Basic2DDrawable__
#define __Basic2DDrawable__

#include "Linker.h"

#include "BasicDrawable.h"

class Basic2DDrawable : public BasicDrawable
{
public:
	Basic2DDrawable();

	static std::shared_ptr<Basic2DDrawable> Spawn(const std::vector<Vertex>&	vectorVertices,
												  const std::vector<WORD>&	vectorIndices,
												  const std::string&			vertexFile,
												  const std::string&			pixelFile,
												  D3D11_CULL_MODE				cullMode,
												  D3D11_FILL_MODE				fillMode);

	void CalculateWVP(const std::shared_ptr<ObjectINFO>& object, const SceneInfo& si, XMFLOAT4X4& worldFloat4x4, XMFLOAT4X4& finalFloat4x4);
};


#endif //__Basic2DDrawable__