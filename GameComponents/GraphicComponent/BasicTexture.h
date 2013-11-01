#ifndef __BasicTexture__
#define __BasicTexture__

#include "Linker.h"

#include "Texture.h"

#include <string>
#include <D3D11.h>

class BasicTexture : public Texture
{
public:
	BasicTexture(const std::string& inputID);
	virtual void Init();
	virtual void Destory();
	virtual void SettupTexture();
	virtual void CleanupTexture();
	
	static std::shared_ptr<BasicTexture> Spawn(const std::string& inputID, int slot, const std::string& fileName);

	struct
	{
		int							slot;
		std::string					textureFileName;
		ID3D11ShaderResourceView*	pTexture;
	} D3DInfo;
};


#endif //__BasicTexture__