#ifndef __BasicTexture__
#define __BasicTexture__

#include "Linker.h"

#include <memory>
#include <string>
#include <D3D11.h>

class BasicTexture
{
public:
	BasicTexture(const std::string& inputID);
	virtual void Init();
	virtual void Destory();
	virtual void Update(double realTime, double deltaTime);
	
	static std::shared_ptr<BasicTexture> Spawn(const std::string& inputID);
	static std::shared_ptr<BasicTexture> Spawn(const std::string& inputID, const std::string& fileName);
	static std::shared_ptr<BasicTexture> Spawn(const std::string& inputID, ID3D11ShaderResourceView*& fileName);

	struct
	{
		std::string					textureFileName;
		ID3D11ShaderResourceView*	pTexture;
	} D3DInfo;
	std::string ID;
};


#endif //__BasicTexture__