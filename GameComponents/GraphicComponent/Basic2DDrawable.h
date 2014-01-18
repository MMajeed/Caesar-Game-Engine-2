#ifndef __Basic2DDrawable__
#define __Basic2DDrawable__

#include "Linker.h"

#include "BasicDrawable.h"

class Basic2DDrawable : public BasicDrawable
{
public:
	Basic2DDrawable();

	static std::shared_ptr<Basic2DDrawable> Spawn(std::shared_ptr<CHL::Model>	model,
												  const std::string&			vertexFile,
												  const std::string&			pixelFile,
												  const std::string&			geometryFile,
												  D3D11_CULL_MODE				cullMode,
												  D3D11_FILL_MODE				fillMode);

	virtual void ProcessModel(std::shared_ptr<CHL::Model> model);

	void CalculateWVP(const std::shared_ptr<ObjectINFO>& object, const SceneInfo& si, XMFLOAT4X4& worldFloat4x4, XMFLOAT4X4& finalFloat4x4);
};


#endif //__Basic2DDrawable__