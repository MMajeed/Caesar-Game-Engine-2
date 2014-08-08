#ifndef __CubeScreenShot__
#define __CubeScreenShot__

#include "ScreenShot.h"
#include <Vector.h>

class GraphicComponentDLL_API CubeScreenShot : public ScreenShot
{
protected:
	CubeScreenShot();
public:
	void Init();
	void Snap();
	void Snap(const std::hash_map<std::string, GraphicObjectEntity>& list);

	GraphicCameraEntity CubeScreenShot::SetupScene(std::size_t side, std::shared_ptr<CameraEntity>& cam);
	void SetupSnapShot(std::size_t side, const GraphicCameraEntity& Camera, const std::hash_map<std::string, GraphicObjectEntity>& list);
	void TakeScreenSnapShot(std::size_t side, const GraphicCameraEntity& Camera, const std::hash_map<std::string, GraphicObjectEntity>& list);
	void CleanupSnapShot(std::size_t side, const GraphicCameraEntity& Camera, const std::hash_map<std::string, GraphicObjectEntity>& list);
	
	static std::shared_ptr<CubeScreenShot> Spawn(unsigned int width, unsigned int height, const std::string& cameraID);
	std::shared_ptr<ScreenShot> clone() const;

	COMSharedPtr<ID3D11RenderTargetView>	pColorMapRTV[6];
	COMSharedPtr<ID3D11DepthStencilView>	pDepthMapDSV;
	D3D11_VIEWPORT	Viewport;
	unsigned int	width;
	unsigned int	height;
	std::string		cameraID;
};


#endif //__iScreenShot__
