#ifndef __DepthTexture__
#define __DepthTexture__

#include "Linker.h"
#include "Texture.h"
#include <D3D11.h>

class DepthTexture : public Texture
{
public:
	DepthTexture(const std::string& inputID);
	virtual void Init();
	virtual void Destory();
	virtual void Update(double realTime, double deltaTime);
	virtual void SettupTexture();
	virtual void CleanupTexture();

	static std::shared_ptr<DepthTexture> Spawn(const std::string& inputID, int slot, const std::string& fileName);

	struct
	{
		int							slot;
		ID3D11ShaderResourceView*	pTexture;
	} D3DInfo;
};


#endif //__DepthTexture__