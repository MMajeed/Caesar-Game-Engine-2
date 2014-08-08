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
	void Snap(const std::hash_map<std::string, GraphicObjectEntity>& list);

	void SetupSnapShot(const GraphicCameraEntity& Camera, const std::hash_map<std::string, GraphicObjectEntity>& list);
	void TakeScreenSnapShot(const GraphicCameraEntity& Camera, const std::hash_map<std::string, GraphicObjectEntity>& list);
	void CleanupSnapShot(const GraphicCameraEntity& Camera, const std::hash_map<std::string, GraphicObjectEntity>& list);

	static std::shared_ptr<BasicScreenShot> Spawn(unsigned int width, unsigned int height, const std::string& cameraID);
	std::shared_ptr<ScreenShot> clone() const;
	
	COMSharedPtr<ID3D11RenderTargetView>	pColorMapRTV;
	COMSharedPtr<ID3D11DepthStencilView>	pDepthMapDSV;
	D3D11_VIEWPORT	Viewport;
	unsigned int	width;
	unsigned int	height;
	std::string		cameraID;
};


#endif //__iScreenShot__
