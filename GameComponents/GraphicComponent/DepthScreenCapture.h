#ifndef __DepthScreenCapture__
#define __DepthScreenCapture__

#include "ScreenCapture.h"
#include "DepthScreenShot.h"

class GraphicComponentDLL_API DepthScreenCapture : public ScreenCapture
{
protected:
	DepthScreenCapture();
public:
	virtual void Init();
	virtual void Snap(const std::hash_map<std::string, std::shared_ptr<GraphicObjectEntity>>& list);
	virtual std::shared_ptr<ScreenCapture> clone() const;
	virtual ~DepthScreenCapture(){}

	static std::shared_ptr<DepthScreenCapture> Spawn(
		const std::string& textureID,
		unsigned int width,
		unsigned int height,
		std::string CameraID);

	std::shared_ptr<DepthScreenShot>	ScreenShot;
	std::string							cameraID;
	unsigned int						width;
	unsigned int						height;
};


#endif //__DepthScreenCapture__
