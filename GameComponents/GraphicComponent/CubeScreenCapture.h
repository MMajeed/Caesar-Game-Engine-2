#ifndef __CubeScreenCapture__
#define __CubeScreenCapture__

#include "ScreenCapture.h"
#include "CubeScreenShot.h"

class GraphicComponentDLL_API CubeScreenCapture : public ScreenCapture
{
protected:
	CubeScreenCapture();
public:
	virtual void Init();
	virtual void Snap(const std::unordered_map<std::string, std::shared_ptr<GraphicObjectEntity>>& list);
	virtual std::shared_ptr<ScreenCapture> clone() const;
	virtual ~CubeScreenCapture(){}

	static std::shared_ptr<CubeScreenCapture> Spawn(const std::string& textureID,
													unsigned int width,
													unsigned int height,
													unsigned int Priority,
													const std::string& cameraID,
													const std::string& drawSettingsID);

	std::shared_ptr<CubeScreenShot>	ScreenShot;
	std::string						cameraID;
	std::string						drawSettingsID;
	unsigned int					width;
	unsigned int					height;
};


#endif //__CubeScreenCapture__
