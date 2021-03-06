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
	void Snap(const std::unordered_map<std::string, std::shared_ptr<GraphicObjectEntity>>& list);

	std::shared_ptr<GraphicCameraEntity> CubeScreenShot::SetupScene(std::size_t side, std::shared_ptr<CameraEntity>& cam);
	void SetupSnapShot(std::size_t side, std::shared_ptr<GraphicCameraEntity> Camera, std::shared_ptr<GraphicDrawSettingsEntity> drawSettings, const std::unordered_map<std::string, std::shared_ptr<GraphicObjectEntity>>& list);
	void TakeScreenSnapShot(std::size_t side, std::shared_ptr<GraphicCameraEntity> Camera, std::shared_ptr<GraphicDrawSettingsEntity> drawSettings, const std::unordered_map<std::string, std::shared_ptr<GraphicObjectEntity>>& list);
	void CleanupSnapShot(std::size_t side, std::shared_ptr<GraphicCameraEntity> Camera, std::shared_ptr<GraphicDrawSettingsEntity> drawSettings, const std::unordered_map<std::string, std::shared_ptr<GraphicObjectEntity>>& list);
	
	static std::shared_ptr<CubeScreenShot> Spawn(unsigned int width,
												 unsigned int height,
												 const std::string& cameraID,
												 const std::string& drawSettingsID);
	std::shared_ptr<ScreenShot> clone() const;

	COMSharedPtr<ID3D11RenderTargetView>	pColorMapRTV[6];
	COMSharedPtr<ID3D11DepthStencilView>	pDepthMapDSV;
	D3D11_VIEWPORT	Viewport;
	unsigned int	width;
	unsigned int	height;
	std::string		cameraID;
	std::string		drawSettingsID;
};


#endif //__iScreenShot__
