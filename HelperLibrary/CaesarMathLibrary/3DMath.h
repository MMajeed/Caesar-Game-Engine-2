#ifndef __3DMath__
#define __3DMath__

#include "Matrix.h"
#include "Vector.h"
#include "Linker.h"

namespace CHL
{
	CHL::Matrix4x4 OrthographicLHCalculation(double width, double height, double NearZ, double FarZ);
	CHL::Matrix4x4 PerspectiveFovLHCalculation( double FovAngleY, double AspectRatio, double NearZ,  double FarZ);
	CHL::Matrix4x4 ViewCalculation(const CHL::Vec4& vEye, const CHL::Vec4& vTM, const CHL::Vec4& vUp, double pitch, double yaw, double roll );
	CHL::Matrix4x4 ObjectCalculation( const CHL::Vec4& mLocation, const CHL::Vec4& mRotation, const CHL::Vec4& mScale);

	CHL::Vec4 MoveForward(const CHL::Vec4& vEye, const CHL::Vec4& vTM, double pitch, double yaw, double roll, double distance);

	float Length(const CHL::Vec4& a, const CHL::Vec4& b);
};

#endif //__3DMath__