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
	virtual void Snap(const std::hash_map<std::string, GraphicObjectEntity>& list);
	virtual std::shared_ptr<ScreenCapture> clone() const;
	virtual ~CubeScreenCapture(){}

	static std::shared_ptr<CubeScreenCapture> Spawn(const std::string& textureID,
													unsigned int width,
													unsigned int height,
													const std::string& cameraID);

	std::shared_ptr<CubeScreenShot>	ScreenShot[2];
	std::string						cameraID;
	unsigned int					width;
	unsigned int					height;
	unsigned int					current;
};


#endif //__CubeScreenCapture__
