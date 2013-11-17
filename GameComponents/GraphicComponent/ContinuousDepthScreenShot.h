#ifndef __ContinuousDepthScreenShot__
#define __ContinuousDepthScreenShot__

#include "ContinuousScreenShot.h"
#include "DepthScreenCapture.h"

class ContinuousDepthScreenShot : public ContinuousScreenShot
{
public:
	ContinuousDepthScreenShot(const std::string& inputID);

	virtual void Init();
	virtual void Destory();
	virtual void Update(double realTime, double deltaTime);
	virtual void Snap(TypedefObject::ObjectVector& objects);
	virtual std::shared_ptr<ContinuousScreenShot> clone() const;
	virtual ~ContinuousDepthScreenShot(){}

	static std::shared_ptr<ContinuousDepthScreenShot> Spawn(const std::string& inputID,
		const std::string& textureID,
		unsigned int width,
		unsigned int height,
		CHL::Matrix4x4 cameraMatrix,
		CHL::Matrix4x4 prespectiveMatrix);

	std::shared_ptr<DepthScreenCapture>	ScreenShot;
	CHL::Matrix4x4						prespectiveMatrix;
	CHL::Matrix4x4						cameraMatrix;
	unsigned int						width;
	unsigned int						height;
};


#endif //__ContinuousDepthScreenShot__
