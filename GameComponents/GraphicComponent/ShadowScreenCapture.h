#ifndef __ShadowScreenCapture__
#define __ShadowScreenCapture__

#include "ScreenCapture.h"
#include <Matrix.h>

class ShadowScreenCapture : public ScreenCapture
{
public:
	ShadowScreenCapture(const std::string& inputID);

	void Init();
	void Destory();
	void Update(double realTime, double deltaTime);
	void Snap(std::hash_map<std::string, SP_INFO>& objects);

	void SetupScene(std::hash_map<std::string, SP_INFO>& objects);
	void SetupSnapShot(std::hash_map<std::string, SP_INFO>& objects);
	void TakeScreenSnapShot(std::hash_map<std::string, SP_INFO>& objects);
	void CleanupSnapShot(std::hash_map<std::string, SP_INFO>& objects);

	static std::shared_ptr<ShadowScreenCapture> Spawn(unsigned int width, unsigned int height, ID3D11Texture2D*& tex, unsigned int index, unsigned int arraySize);
	std::shared_ptr<ScreenCapture> clone() const;

	struct
	{
		ID3D11DepthStencilView*	pDepthMapDSV;
		D3D11_VIEWPORT          Viewport;
		unsigned int			width;
		unsigned int			height;
		CHL::Matrix4x4			prespectiveMatrix;
		CHL::Matrix4x4			cameraMatrix;
	} D3DInfo;
};


#endif //__ShadowScreenCapture__
