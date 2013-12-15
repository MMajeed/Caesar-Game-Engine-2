#ifndef __CubeScreenCapture__
#define __CubeScreenCapture__

#include "ScreenCapture.h"
#include "CubeScreenShot.h"

class CubeScreenCapture : public ScreenCapture
{
public:
	CubeScreenCapture(const std::string& inputID);

	virtual void Init();
	virtual void Destory();
	virtual void Update(double realTime, double deltaTime);
	virtual void Snap(std::hash_map<std::string, SP_INFO>& objects);
	virtual std::shared_ptr<ScreenCapture> clone() const;
	virtual ~CubeScreenCapture(){}

	static std::shared_ptr<CubeScreenCapture> Spawn(	const std::string& inputID,
															const std::string& textureID,
															unsigned int width,
															unsigned int height,
															CHL::Vec4 eye);

	std::shared_ptr<CubeScreenShot>	ScreenShot[2];
	CHL::Vec4							eye;
	unsigned int						width;
	unsigned int						height;
	unsigned int						current;
};


#endif //__CubeScreenCapture__
