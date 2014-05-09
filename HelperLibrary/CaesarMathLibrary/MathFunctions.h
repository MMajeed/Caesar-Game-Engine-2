#ifndef __MathFunctions__
#define __MathFunctions__

#include "Linker.h"

#include "Vector.h"
#include "Matrix.h"

namespace CML
{
	CaesarMathLibraryDLL_API CML::Matrix4x4 TransformMatrix(CML::Vec3 Translation, CML::Vec4 QuaRotation, CML::Vec3 Scale);

	CaesarMathLibraryDLL_API CML::Matrix4x4 RotationMatrix(CML::Vec4 QuaRotation);
	CaesarMathLibraryDLL_API CML::Matrix4x4 RotationMatrix(double pitch, double yaw, double roll);

	CaesarMathLibraryDLL_API CML::Vec4 PYRToQuaternion(double pitch, double yaw, double roll);
	CaesarMathLibraryDLL_API CML::Vec3 QuaternionToEular(CML::Vec4 qua);

	CaesarMathLibraryDLL_API Vec4 QuaNormalize(const Vec4& rhs);

	CaesarMathLibraryDLL_API Vec3 CrossProduct(const Vec3& rhs, const Vec3& lhs);
	CaesarMathLibraryDLL_API double Dot(const Vec4& rhs, const Vec4& lhs);
	CaesarMathLibraryDLL_API Vec4 Normalize(const Vec4& rhs);

	CaesarMathLibraryDLL_API Vec4 Multiple(Vec4 rhs, Matrix4x4 lhs);
	CaesarMathLibraryDLL_API Matrix4x4 Multiple(Matrix4x4 rhs, Matrix4x4 lhs);

	CaesarMathLibraryDLL_API Matrix4x4 MatrixIdentity();

	CaesarMathLibraryDLL_API Vec4 Lerp(const Vec4& rhs, const Vec4& lhs, double ratio);
	CaesarMathLibraryDLL_API Vec4 Slerp(const Vec4& rhs, const Vec4& lhs, double ratio);

	CaesarMathLibraryDLL_API CML::Matrix4x4 Transpose(const CML::Matrix4x4& mat);
};

#endif //__MathFunctions__