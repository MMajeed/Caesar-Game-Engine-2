#ifndef __CubeScreenShot__
#define __CubeScreenShot__

#include "ScreenShot.h"
#include <Vector.h>
#include "SceneInfo.h"
#include <CameraINFO.h>

class CubeScreenShot : public ScreenShot
{
protected:
	CubeScreenShot();
public:
	void Init();
	void Release();
	void Update(double realTime, double deltaTime);
	void Snap(std::hash_map<std::string, SP_INFO>& objects);

	SceneInfo SetupScene(std::hash_map<std::string, SP_INFO>& objects, std::size_t side, const std::shared_ptr<CameraINFO>& cam);
	void SetupSnapShot(std::hash_map<std::string, SP_INFO>& objects, std::size_t side, const SceneInfo& si);
	void TakeScreenSnapShot(std::hash_map<std::string, SP_INFO>& objects, std::size_t side, const SceneInfo& si);
	void CleanupSnapShot(std::hash_map<std::string, SP_INFO>& objects);

	static std::shared_ptr<CubeScreenShot> Spawn(unsigned int width, unsigned int height, const std::string& cameraID);
	std::shared_ptr<ScreenShot> clone() const;

	struct
	{
		ID3D11RenderTargetView*		pColorMapRTV[6];
		ID3D11DepthStencilView*		pDepthMapDSV;
		D3D11_VIEWPORT              Viewport;
		unsigned int				width;
		unsigned int				height;
		std::string					cameraID;
	} D3DInfo;
};


#endif //__iScreenShot__
