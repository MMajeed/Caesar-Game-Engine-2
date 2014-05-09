#ifndef __BasicScreenCapture__
#define __BasicScreenCapture__

#include "ScreenCapture.h"
#include "BasicScreenShot.h"

class GraphicComponentDLL_API BasicScreenCapture : public ScreenCapture
{
protected:
	BasicScreenCapture();
public:
	virtual void Init();
	virtual void Destory();
	virtual void Update(double realTime, double deltaTime);
	virtual void Snap(std::hash_map<std::string, SP_INFO>& objects);
	virtual std::shared_ptr<ScreenCapture> clone() const;
	virtual ~BasicScreenCapture(){}

	static std::shared_ptr<BasicScreenCapture> Spawn(const std::string& textureID,
													unsigned int width, 
													unsigned int height,
													std::string CameraID);

	std::shared_ptr<BasicScreenShot>	ScreenShot[2];
	std::string							cameraID;
	unsigned int						width;
	unsigned int						height;
	unsigned int						current;
};


#endif //__BasicScreenCapture__
