#ifndef __MathFunctions__
#define __MathFunctions__

#include "Linker.h"

#include "Vector.h"
#include "Matrix.h"

namespace CML
{
	CML::Matrix4x4 TransformMatrix(CML::Vec4 Translation, CML::Vec4 Rotation, CML::Vec4 Scale);
	CML::Matrix4x4 RotationMatrix(double pitch, double yaw, double roll);
	Vec3 CrossProduct(const Vec3& rhs, const Vec3& lhs);
	double Dot(const Vec4& rhs, const Vec4& lhs);
	Vec4 Normalize(const Vec4& rhs);
	Vec4 Multiple(Vec4 rhs, Matrix4x4 lhs);
	Matrix4x4 Multiple(Matrix4x4 rhs, Matrix4x4 lhs);
	Matrix4x4 MatrixIdentity();
	Vec4 Lerp(const Vec4& rhs, const Vec4& lhs, double ratio);
	Vec4 Slerp(const Vec4& rhs, const Vec4& lhs, double ratio);
};

#endif //__MathFunctions__