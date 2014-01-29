#include "MathFunctions.h"
#include <Eigen\Dense>
#include "CMLToEigen.h"

namespace CML
{
	CML::Matrix4x4 TransformMatrix(CML::Vec4 Translation, CML::Vec4 Rotation, CML::Vec4 Scale)
	{
		Eigen::Translation3d translation(Translation(0), Translation(1), Translation(2));

		Eigen::AngleAxisd rollAngle(Rotation(0), Eigen::Vector3d::UnitZ());
		Eigen::AngleAxisd yawAngle(Rotation(1), Eigen::Vector3d::UnitY());
		Eigen::AngleAxisd pitchAngle(Rotation(2), Eigen::Vector3d::UnitX());
		Eigen::Quaternion<double> rotation = rollAngle * yawAngle * pitchAngle;

		Eigen::AlignedScaling3d scaling(Scale(0), Scale(1), Scale(2));

		Eigen::Transform<double, 3, Eigen::Affine> transfrom = translation * rotation  * scaling;

		Eigen::Matrix4d tranfromMatix = transfrom.matrix().transpose();
		CML::Matrix4x4 returnValue = CML::ConvertMatrix(tranfromMatix);
		return returnValue;
	}
	CML::Matrix4x4 RotationMatrix(double pitch, double yaw, double roll)
	{
		Eigen::AngleAxisd rollAngle(roll, Eigen::Vector3d::UnitZ());
		Eigen::AngleAxisd yawAngle(yaw, Eigen::Vector3d::UnitY());
		Eigen::AngleAxisd pitchAngle(pitch, Eigen::Vector3d::UnitX());

		Eigen::Quaternion<double> q = rollAngle * yawAngle * pitchAngle;

		Eigen::Matrix3d rotationMatrix = q.matrix();

		CML::Matrix4x4 returnValue = CML::ConvertMatrix(rotationMatrix);
		returnValue[3] = {0.0, 0.0, 0.0, 1.0};
		return returnValue;
	}
	Vec3 CrossProduct(const Vec3& rhs, const Vec3& lhs)
	{
			Eigen::Vector3d eRhs = CML::ConvertVec(rhs);
			Eigen::Vector3d eLhs = CML::ConvertVec(lhs);

			Eigen::Vector3d result = eRhs.cross(eLhs);

			Vec3 returnValue = CML::ConvertVec(result);
			return returnValue;
		}
	Vec3 Dot(const Vec3& rhs, const Vec3& lhs)
	{
		Eigen::Vector3d eRhs = CML::ConvertVec(rhs);
		Eigen::Vector3d eLhs = CML::ConvertVec(lhs);

		Eigen::Vector3d result = eRhs.cross(eLhs);

		Vec3 returnValue = CML::ConvertVec(result);
		return returnValue;
	}
	double Dot(const Vec4& rhs, const Vec4& lhs)
	{
		Eigen::Vector4d eRhs = CML::ConvertVec(rhs);
		Eigen::Vector4d eLhs = CML::ConvertVec(lhs);

		double result = eRhs.dot(eLhs);
		return result;
	}
	Vec4 Normalize(const Vec4& rhs)
	{
		Eigen::Vector4d eRhs = CML::ConvertVec(rhs);
		eRhs.normalize();
		Vec4 returnValue = CML::ConvertVec(eRhs);
		return returnValue;
	}
	Vec4 Multiple(Vec4 rhs, Matrix4x4 lhs)
	{
		Eigen::Vector4d eRhs = CML::ConvertVec(rhs);
		Eigen::Matrix4d eLhs = CML::ConvertMatrix<double, 4, 4>(lhs);

		Eigen::Vector4d result = eLhs * eRhs;

		Vec4 returnValue = CML::ConvertVec(result);
		return returnValue;
	}
	Matrix4x4 Multiple(Matrix4x4 rhs, Matrix4x4 lhs)
	{
		Eigen::Matrix4d eRhs = CML::ConvertMatrix<double, 4, 4>(rhs);
		Eigen::Matrix4d eLhs = CML::ConvertMatrix<double, 4, 4>(lhs);

		Eigen::Matrix4d result = eLhs * eRhs;

		Matrix4x4 returnValue = CML::ConvertMatrix<double, 4, 4>(result);
		return returnValue;
	}
	Matrix4x4 MatrixIdentity()
	{
		return{	{1.0, 0.0, 0.0, 0.0}, 
				{0.0, 1.0, 0.0, 0.0},
				{0.0, 0.0, 1.0, 0.0}, 
				{0.0, 0.0, 0.0, 1.0}, };
	}
	Vec4 Lerp(const Vec4& rhs, const Vec4& lhs, double ratio)
	{
		Vec4 result = {	(rhs(0) + (lhs(0) - rhs(0)) * ratio),
						(rhs(1) + (lhs(1) - rhs(1)) * ratio),
						(rhs(2) + (lhs(2) - rhs(2)) * ratio),
						(rhs(3) + (lhs(3) - rhs(3)) * ratio), };
		return result;
	}
	Vec4 Slerp(const Vec4& rhs, const Vec4& lhs, double ratio)
	{
		Eigen::AngleAxisd rollAngleRhs(rhs(0), Eigen::Vector3d::UnitZ());
		Eigen::AngleAxisd yawAngleRhs(rhs(1), Eigen::Vector3d::UnitY());
		Eigen::AngleAxisd pitchAngleRhs(rhs(2), Eigen::Vector3d::UnitX());
		Eigen::Quaternion<double> qRhs = rollAngleRhs * yawAngleRhs * pitchAngleRhs;

		Eigen::AngleAxisd rollAngleLhs(lhs(0), Eigen::Vector3d::UnitZ());
		Eigen::AngleAxisd yawAngleLhs(lhs(1), Eigen::Vector3d::UnitY());
		Eigen::AngleAxisd pitchAngleLhs(lhs(2), Eigen::Vector3d::UnitX());
		Eigen::Quaternion<double> qLhs = rollAngleLhs * yawAngleLhs * pitchAngleLhs;

		Eigen::Quaternion<double> result = qRhs.slerp(ratio, qLhs);
		Vec4 returnValue = {result.x(), result.y(), result.z(), result.w()};
		return returnValue;
	}
};