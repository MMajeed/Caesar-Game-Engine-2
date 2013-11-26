#ifndef __CubeScreenCapture__
#define __CubeScreenCapture__

#include "ScreenCapture.h"
#include <Vector.h>

class CubeScreenCapture : public ScreenCapture
{
public:
	CubeScreenCapture(const std::string& inputID);

	void Init();
	void Destory();
	void Update(double realTime, double deltaTime);
	void Snap(std::hash_map<std::string, SP_INFO>& objects);

	void SetupScene(std::hash_map<std::string, SP_INFO>& objects, std::size_t side);
	void SetupSnapShot(std::hash_map<std::string, SP_INFO>& objects, std::size_t side);
	void TakeScreenSnapShot(std::hash_map<std::string, SP_INFO>& objects, std::size_t side);
	void CleanupSnapShot(std::hash_map<std::string, SP_INFO>& objects, std::size_t side);

	static std::shared_ptr<CubeScreenCapture> Spawn(std::string id, unsigned int width, unsigned int height);
	std::shared_ptr<ScreenCapture> clone() const;

	struct
	{
		ID3D11RenderTargetView*		pColorMapRTV[6];
		ID3D11DepthStencilView*		pDepthMapDSV;
		D3D11_VIEWPORT              Viewport;
		unsigned int				width;
		unsigned int				height;
		CHL::Vec4					Eye;
	} D3DInfo;
};


#endif //__iScreenCapture__
