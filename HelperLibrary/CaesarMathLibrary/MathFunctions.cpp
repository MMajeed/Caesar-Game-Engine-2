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
};