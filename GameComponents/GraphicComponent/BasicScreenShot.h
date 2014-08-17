#ifndef __BasicScreenShot__
#define __BasicScreenShot__

#include "ScreenShot.h"
#include <Vector.h>

class GraphicComponentDLL_API BasicScreenShot : public ScreenShot
{
protected:
	BasicScreenShot();
public:
	void Init();
	void Snap();
	void Snap(const std::unordered_map<std::string, std::shared_ptr<GraphicObjectEntity>>& list);

	void SetupSnapShot(std::shared_ptr<GraphicCameraEntity> Camera, const std::unordered_map<std::string, std::shared_ptr<GraphicObjectEntity>>& list);
	void TakeScreenSnapShot(std::shared_ptr<GraphicCameraEntity> Camera, const std::unordered_map<std::string, std::shared_ptr<GraphicObjectEntity>>& list);
	void CleanupSnapShot(std::shared_ptr<GraphicCameraEntity> Camera, const std::unordered_map<std::string, std::shared_ptr<GraphicObjectEntity>>& list);

	static std::shared_ptr<BasicScreenShot> Spawn(unsigned int width, unsigned int height, unsigned int numberOfTargets, const std::string& cameraIDs);
	std::shared_ptr<ScreenShot> clone() const;
	
	std::vector<COMSharedPtr<ID3D11RenderTargetView>>	pColorMapRTV;
	COMSharedPtr<ID3D11DepthStencilView>				pDepthMapDSV;
	D3D11_VIEWPORT	Viewport;
	unsigned int	width;
	unsigned int	height;
	unsigned int	numberOfTargets;
	std::string		cameraID;
};


#endif //__iScreenShot__
