#ifndef __BasicTexture__
#define __BasicTexture__

#include "Linker.h"

#include <memory>
#include <string>
#include <D3D11.h>

class GraphicComponentDLL_API BasicTexture
{
protected:
	BasicTexture();
public:
	virtual void Init();
	virtual void Destory();
	
	static std::shared_ptr<BasicTexture> Spawn();
	static std::shared_ptr<BasicTexture> Spawn(const std::string& fileName);
	static std::shared_ptr<BasicTexture> Spawn(ID3D11ShaderResourceView* fileName);

	struct
	{
		std::string					textureFileName;
		ID3D11ShaderResourceView*	pTexture;
	} D3DInfo;
};


#endif //__BasicTexture__