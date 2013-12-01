#ifndef __SetupLight__
#define __SetupLight__

#include <hash_map>
#include <string>
#include <INFO.h>
#include <Singleton.h>
#include <memory>
#include "Buffers.h"
#include "ShadowScreenCapture.h"
#include "ShadowFilter.h"

class Light : public CHL::Singleton<Light>
{
protected:
	Light();
public:
	void SetupLight(std::hash_map<std::string, SP_INFO>& objects);
	std::vector<std::shared_ptr<ShadowScreenCapture>> vecDepthShadow;

	void Init();

	ID3D11Texture2D* shadowTexture;
	ID3D11ShaderResourceView*	shaderShadowTexture;
	static const unsigned int Width = 2048;
	static const unsigned int Height = 2048;
	static const unsigned int NumberOfShadows = cBuffer::numOfLights;
	std::shared_ptr<ShadowFilter> shadowFilter;

	friend CHL::Singleton<Light>;
};

extern cBuffer::cbLight LastLightInput;

#endif //__SetupLight__