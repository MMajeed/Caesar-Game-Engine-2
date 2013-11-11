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
	virtual void Update(double realTime, double deltaTime);
	virtual void SettupTexture(TypedefObject::ObjectInfo& object);
	virtual void CleanupTexture(TypedefObject::ObjectInfo& object);
	
	static std::shared_ptr<BasicTexture> Spawn(const std::string& inputID, const std::string& fileName);

	struct
	{
		std::string					textureFileName;
		ID3D11ShaderResourceView*	pTexture;
	} D3DInfo;
};


#endif //__BasicTexture__