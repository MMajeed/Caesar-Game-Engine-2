#ifndef __3DMath__
#define __3DMath__

#include <Vector.h>
#include "Linker.h"
#include <Matrix.h>

GraphicComponentDLL_API CML::Matrix4x4 OrthographicLHCalculation(double width, double height, double NearZ, double FarZ);
GraphicComponentDLL_API CML::Matrix4x4 PerspectiveFovLHCalculation(double FovAngleY, double AspectRatio, double NearZ, double FarZ);
GraphicComponentDLL_API CML::Matrix4x4 ViewCalculation(const CML::Vec4& vEye, const CML::Vec4& vTM, const CML::Vec4& vUp, double pitch, double yaw, double roll);
GraphicComponentDLL_API CML::Matrix4x4 ObjectCalculation(const CML::Vec4& mLocation, const CML::Vec4& mRotation, const CML::Vec4& mScale);

GraphicComponentDLL_API CML::Vec4 MoveForward(const CML::Vec4& vEye, const CML::Vec4& vTM, double pitch, double yaw, double roll, double distance);

GraphicComponentDLL_API float Length(const CML::Vec4& a, const CML::Vec4& b);

#endif //__3DMath__