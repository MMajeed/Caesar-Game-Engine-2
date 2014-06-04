#include "MathFunctions.h"
#include "Eigen\Dense"
#include "CMLToEigen.h"

namespace CML
{
	CML::Matrix4x4 TransformMatrix(CML::Vec3 Translation, CML::Vec4 QuaRotation, CML::Vec3 Scale)
	{
		Eigen::Translation3d translation(Translation(0), Translation(1), Translation(2));

		Eigen::Quaternion<double> rotation(QuaRotation(3), QuaRotation(0), QuaRotation(1), QuaRotation(2));
		
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
	CML::Matrix4x4 RotationMatrix(CML::Vec4 QuaRotation)
	{
		Eigen::Quaternion<double> q(QuaRotation(3), QuaRotation(0), QuaRotation(1), QuaRotation(2));
		return CML::ConvertMatrix(q.matrix());
	}

	CML::Vec4 PYRToQuaternion(double pitch, double yaw, double roll)
	{
		Eigen::AngleAxisd rollAngle(roll, Eigen::Vector3d::UnitZ());
		Eigen::AngleAxisd yawAngle(yaw, Eigen::Vector3d::UnitY());
		Eigen::AngleAxisd pitchAngle(pitch, Eigen::Vector3d::UnitX());

		Eigen::Quaternion<double> q = rollAngle * yawAngle * pitchAngle;

		CML::Vec4 returnValue = {q.x(), q.y(), q.z(), q.w()};
		return returnValue;
	}
	CML::Vec3 QuaternionToEular(CML::Vec4 qua)
	{
		double x = qua[0];
		double y = qua[1];
		double z = qua[2];
		double w = qua[3];

		double sqw = w*w;
		double sqx = x*x;
		double sqy = y*y;
		double sqz = z*z;

		double eularZ = atan2(2.0 * (x*y + z*w), (sqx - sqy - sqz + sqw));
		double eularX = atan2(2.0 * (y*z + x*w), (-sqx - sqy + sqz + sqw));
		double eularY = sin(-2.0 * (x*z - y*w));

		return{eularX, eularY, eularZ};
	}

	Vec4 QuaNormalize(const Vec4& rhs)
	{
		Eigen::Quaternion<double> q(rhs(3), rhs(0), rhs(1), rhs(2));
		q.normalize();

		CML::Vec4 returnValue = {q.x(), q.y(), q.z(), q.w()};
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
		Vec4 result = {	rhs(0) + ((lhs(0) - rhs(0)) * ratio),
						rhs(1) + ((lhs(1) - rhs(1)) * ratio),
						rhs(2) + ((lhs(2) - rhs(2)) * ratio),
						rhs(3) + ((lhs(3) - rhs(3)) * ratio), };
		return result;
	}
	Vec4 Slerp(const Vec4& rhs, const Vec4& lhs, double ratio)
	{
		Eigen::Quaternion<double> qRhs(rhs(3), rhs(0), rhs(1), rhs(2));
		Eigen::Quaternion<double> qLhs(lhs(3), lhs(0), lhs(1), lhs(2));

		Eigen::Quaternion<double> result = qRhs.slerp(ratio, qLhs);
		Vec4 returnValue = {result.x(), result.y(), result.z(), result.w()};
		return returnValue;
	}

	CML::Matrix4x4 Transpose(const CML::Matrix4x4& mat)
	{
		return{	{mat[0][0], mat[1][0], mat[2][0], mat[3][0]},
				{mat[0][1], mat[1][1], mat[2][1], mat[3][1]},
				{mat[0][2], mat[1][2], mat[2][2], mat[3][2]},
				{mat[0][3], mat[1][3], mat[2][3], mat[3][3]},
			  };
	}
};