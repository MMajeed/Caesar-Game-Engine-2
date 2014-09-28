#ifndef __DepthScreenShot__
#define __DepthScreenShot__

#include "ScreenShot.h"
#include <Vector.h>

class GraphicComponentDLL_API DepthScreenShot : public ScreenShot
{
protected:
	DepthScreenShot();
public:
	void Init();
	void Snap();
	void Snap(const std::unordered_map<std::string, std::shared_ptr<GraphicObjectEntity>>& list);

	void SetupSnapShot(std::shared_ptr<GraphicCameraEntity> Camera, std::shared_ptr<GraphicDrawSettingsEntity> drawSettings, const std::unordered_map<std::string, std::shared_ptr<GraphicObjectEntity>>& list);
	void TakeScreenSnapShot(std::shared_ptr<GraphicCameraEntity> Camera, std::shared_ptr<GraphicDrawSettingsEntity> drawSettings, const std::unordered_map<std::string, std::shared_ptr<GraphicObjectEntity>>& list);
	void CleanupSnapShot(std::shared_ptr<GraphicCameraEntity> Camera, std::shared_ptr<GraphicDrawSettingsEntity> drawSettings, const std::unordered_map<std::string, std::shared_ptr<GraphicObjectEntity>>& list);

	static std::shared_ptr<DepthScreenShot> Spawn(unsigned int width,
												  unsigned int height,
												  const std::string& cameraID,
												  const std::string& drawSettingsID);
	std::shared_ptr<ScreenShot> clone() const;

	
	COMSharedPtr<ID3D11DepthStencilView>	pDepthMapDSV;
	D3D11_VIEWPORT	Viewport;
	unsigned int	width;
	unsigned int	height;
	std::string		cameraID;
	std::string		drawSettingsID;
};


#endif //__DepthScreenShot__
