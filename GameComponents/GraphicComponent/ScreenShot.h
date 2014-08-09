#ifndef __ScreenShot__
#define __ScreenShot__

#include "Linker.h"
#include "COMSharedPtr.h"
#include "GraphicObjectEntity.h"
#include "GraphicCameraEntity.h"
#include <D3D11.h>
#include <string>
#include <hash_map>
#include <memory>

class GraphicComponentDLL_API ScreenShot
{
protected:
	ScreenShot(){}
public:
	virtual void Snap(const std::hash_map<std::string, std::shared_ptr<GraphicObjectEntity>>& list) = 0;
	virtual ~ScreenShot(){}

	COMSharedPtr<ID3D11ShaderResourceView>	pScreenTexture;
};


#endif //__iScreenShot__
