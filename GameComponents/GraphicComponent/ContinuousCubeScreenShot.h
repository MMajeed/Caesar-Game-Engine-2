#ifndef __ContinuousCubeScreenShot__
#define __ContinuousCubeScreenShot__

#include "ContinuousScreenShot.h"
#include "CubeScreenCapture.h"

class ContinuousCubeScreenShot : public ContinuousScreenShot
{
public:
	ContinuousCubeScreenShot(const std::string& inputID);

	virtual void Init();
	virtual void Destory();
	virtual void Update(double realTime, double deltaTime);
	virtual void Snap(std::hash_map<std::string, SP_INFO>& objects);
	virtual std::shared_ptr<ContinuousScreenShot> clone() const;
	virtual ~ContinuousCubeScreenShot(){}

	static std::shared_ptr<ContinuousCubeScreenShot> Spawn(	const std::string& inputID,
															const std::string& textureID,
															unsigned int width,
															unsigned int height,
															CHL::Vec4 eye);

	std::shared_ptr<CubeScreenCapture>	ScreenShot[2];
	CHL::Vec4							eye;
	unsigned int						width;
	unsigned int						height;
	unsigned int						current;
};


#endif //__ContinuousCubeScreenShot__
