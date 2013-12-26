#ifndef __BasicScreenCapture__
#define __BasicScreenCapture__

#include "ScreenCapture.h"
#include "BasicScreenShot.h"

class BasicScreenCapture : public ScreenCapture
{
public:
	BasicScreenCapture(const std::string& inputID);

	virtual void Init();
	virtual void Destory();
	virtual void Update(double realTime, double deltaTime);
	virtual void Snap(std::hash_map<std::string, SP_INFO>& objects);
	virtual std::shared_ptr<ScreenCapture> clone() const;
	virtual ~BasicScreenCapture(){}

	static std::shared_ptr<BasicScreenCapture> Spawn(const std::string& inputID,
													const std::string& textureID,
													unsigned int width, 
													unsigned int height, 
													CHL::Matrix4x4 cameraMatrix,
													CHL::Matrix4x4 prespectiveMatrix);

	std::shared_ptr<BasicScreenShot>	ScreenShot[2];
	CHL::Matrix4x4						prespectiveMatrix;
	CHL::Matrix4x4						cameraMatrix;
	unsigned int						width;
	unsigned int						height;
	unsigned int						current;
};


#endif //__BasicScreenCapture__
