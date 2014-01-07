#ifndef __CameraINFO__
#define __CameraINFO__

#include "Linker.h"
#include "INFO.h"
#include <Vector.h>

class CameraINFO : public INFO
{
public:
	CameraINFO();

	// Camera Stuff
	CHL::Vec4 Eye;
	CHL::Vec4 TargetMagnitude;
	CHL::Vec4 Up;
	double Roll;
	double Pitch;
	double Yaw;

	// Prespective Stuff
	double FovAngleY;
	double nearZ;
	double farZ;

	CHL::Vec4 ClearColor;

	bool process2D;

	virtual std::shared_ptr<Object> Get(const std::string& ID);
	virtual void Set(const std::string& ID, std::shared_ptr<Object> obj);
	virtual std::shared_ptr<INFO> Clone();
};

#endif //__CameraINFO__