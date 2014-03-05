#ifndef __SetupLight__
#define __SetupLight__

#include <hash_map>
#include <string>
#include <INFO.h>
#include <Singleton.h>
#include <memory>
#include "Buffers.h"
#include "ShadowScreenShot.h"

class Light : public CHL::Singleton<Light>
{
protected:
	Light();
public:
	void Init();

	void SetupLight(std::hash_map<std::string, SP_INFO>& objects, const CML::Vec4& eye);
	void SetupShadow(unsigned int numberOfShadows);

	std::vector<std::shared_ptr<ShadowScreenShot>>	vecDepthShadow;
	ID3D11Texture2D*									shadowTexture;
	ID3D11ShaderResourceView*							shaderShadowTexture;
	static const unsigned int Width = 1024;
	static const unsigned int Height = 1024;

	friend CHL::Singleton<Light>;
};

#endif //__SetupLight__