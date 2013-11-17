#ifndef __ContinuousBasicScreenShot__
#define __ContinuousBasicScreenShot__

#include "ContinuousScreenShot.h"
#include "BasicScreenCapture.h"

class ContinuousBasicScreenShot : public ContinuousScreenShot
{
public:
	ContinuousBasicScreenShot(const std::string& inputID);

	virtual void Init();
	virtual void Destory();
	virtual void Update(double realTime, double deltaTime);
	virtual void Snap(TypedefObject::ObjectVector& objects);
	virtual std::shared_ptr<ContinuousScreenShot> clone() const;
	virtual ~ContinuousBasicScreenShot(){}

	static std::shared_ptr<ContinuousBasicScreenShot> Spawn(const std::string& inputID,
															const std::string& textureID,
															unsigned int width, 
															unsigned int height, 
															CHL::Matrix4x4 cameraMatrix,
															CHL::Matrix4x4 prespectiveMatrix);

	std::shared_ptr<BasicScreenCapture>	ScreenShot[2];
	CHL::Matrix4x4						prespectiveMatrix;
	CHL::Matrix4x4						cameraMatrix;
	unsigned int						width;
	unsigned int						height;
	unsigned int						current;
};


#endif //__ContinuousBasicScreenShot__
