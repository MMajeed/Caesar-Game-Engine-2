#ifndef __ShadowScreenShot__
#define __ShadowScreenShot__

#include "ScreenShot.h"
#include <Vector.h>
#include "SceneInfo.h"

class ShadowScreenShot : public ScreenShot
{
public:
	ShadowScreenShot();

	void Init();
	void Release();
	void Update(double realTime, double deltaTime);
	void Snap(std::hash_map<std::string, SP_INFO>& objects);

	void SetupScene(std::hash_map<std::string, SP_INFO>& objects);
	void SetupSnapShot(std::hash_map<std::string, SP_INFO>& objects);
	void TakeScreenSnapShot(std::hash_map<std::string, SP_INFO>& objects);
	void CleanupSnapShot(std::hash_map<std::string, SP_INFO>& objects);

	static std::shared_ptr<ShadowScreenShot> Spawn(unsigned int width, unsigned int height, ID3D11Texture2D*& tex, unsigned int index, unsigned int arraySize);
	std::shared_ptr<ScreenShot> clone() const;

	struct
	{
		ID3D11DepthStencilView*	pDepthMapDSV;
		D3D11_VIEWPORT          Viewport;
		unsigned int			width;
		unsigned int			height;
		SceneInfo				scene;
	} D3DInfo;
};


#endif //__ShadowScreenShot__
