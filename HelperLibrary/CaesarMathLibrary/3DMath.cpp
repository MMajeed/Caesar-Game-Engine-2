#include "3DMath.h"
#include "XNAConverter.h"
#include <Windows.h>
#include <xnamath.h>

namespace CHL
{
	Matrix4x4 OrthographicLHCalculation(double width, double height, double NearZ, double FarZ)
	{
		XMMATRIX xmPrespective = XMMatrixOrthographicLH((float)width, (float)height, (float)NearZ, (float)FarZ);
		XMFLOAT4X4 xmMatrixPrespective;
		XMStoreFloat4x4(&xmMatrixPrespective, xmPrespective);

		Matrix4x4 mMatrixPrespective = Convert4x4(xmMatrixPrespective);

		return mMatrixPrespective;
	}
	Matrix4x4 PerspectiveFovLHCalculation(double FovAngleY, double AspectRatio, double NearZ, double FarZ)
	{
		XMMATRIX xmPrespective = XMMatrixPerspectiveFovLH((float)FovAngleY, (float)AspectRatio, (float)NearZ, (float)FarZ);
		XMFLOAT4X4 xmMatrixPrespective;
		XMStoreFloat4x4(&xmMatrixPrespective, xmPrespective);

		Matrix4x4 mMatrixPrespective = Convert4x4(xmMatrixPrespective);

		return mMatrixPrespective;
	}

	Matrix4x4 ViewCalculation(const Vec4& vEye, const Vec4& vTM, const Vec4& vUp, double pitch, double yaw, double roll)
	{
		XMVECTOR xmEye = XMVectorSet((float)vEye(0), (float)vEye(1), (float)vEye(2), (float)vEye(3));
		XMVECTOR xmTM = XMVectorSet((float)vTM(0), (float)vTM(1), (float)vTM(2), (float)vTM(3));
		XMVECTOR xmUp = XMVectorSet((float)vUp(0), (float)vUp(1), (float)vUp(2), (float)vUp(3));

		XMMATRIX RotationMatrix = XMMatrixRotationRollPitchYaw((float)pitch, (float)yaw, (float)roll);

		xmTM = XMVector3TransformCoord(xmTM, RotationMatrix);
		xmUp = XMVector3TransformCoord(xmUp, RotationMatrix);

		xmTM += xmEye;

		XMFLOAT4X4  xmView;
		XMStoreFloat4x4(&xmView, XMMatrixLookAtLH(xmEye, xmTM, xmUp));

		Matrix4x4 mView = Convert4x4(xmView);

		return mView;
	}

	Matrix4x4 ObjectCalculation(const Vec4& mLocation, const Vec4& mRotation, const Vec4& mScale)
	{
		XMMATRIX xmTranslate = XMMatrixIdentity();
		XMMATRIX xmRotateX = XMMatrixIdentity();	XMMATRIX xmRotateY = XMMatrixIdentity();	XMMATRIX xmRotateZ = XMMatrixIdentity();
		XMMATRIX xmScaling = XMMatrixIdentity();
		XMMATRIX xmObjectFinal = XMMatrixIdentity();

		xmTranslate = XMMatrixTranslation((float)mLocation(0), (float)mLocation(1), (float)mLocation(2));

		xmRotateX = XMMatrixRotationX((float)mRotation(0));
		xmRotateY = XMMatrixRotationY((float)mRotation(1));
		xmRotateZ = XMMatrixRotationZ((float)mRotation(2));

		xmScaling = XMMatrixScaling((float)mScale(0), (float)mScale(1), (float)mScale(2));


		xmObjectFinal = XMMatrixMultiply(xmObjectFinal, xmScaling);
		xmObjectFinal = XMMatrixMultiply(xmObjectFinal, xmRotateX);
		xmObjectFinal = XMMatrixMultiply(xmObjectFinal, xmRotateY);
		xmObjectFinal = XMMatrixMultiply(xmObjectFinal, xmRotateZ);
		xmObjectFinal = XMMatrixMultiply(xmObjectFinal, xmTranslate);

		XMFLOAT4X4 xmFinal4x4;
		XMStoreFloat4x4(&xmFinal4x4, xmObjectFinal);

		Matrix4x4 mObjectFinal = Convert4x4(xmFinal4x4);

		return mObjectFinal;
	}

	Vec4 MoveForward(const Vec4& vEye, const Vec4& vTM, double pitch, double yaw, double roll, double distance)
	{
		XMVECTOR Eye = XMVectorSet((float)vEye(0), (float)vEye(1), (float)vEye(2), (float)vEye(3));
		XMVECTOR At = XMVectorSet((float)vTM(0), (float)vTM(1), (float)vTM(2), (float)vTM(3));

		At = XMVector4Normalize(At);

		XMMATRIX RotationMatrix(XMMatrixRotationRollPitchYaw((float)pitch, (float)yaw, (float)roll));

		At = XMVector3TransformCoord(At, RotationMatrix);
		At = XMVector4Normalize(At);
		Eye += At * (float)distance;

		XMFLOAT4 tempEye;
		XMStoreFloat4(&tempEye, Eye);

		return ConvertVec4(tempEye);
	}

	float Length(const Vec4& a, const Vec4& b)
	{
		XMVECTOR vector1 = XMVectorSet((float)a(0), (float)a(1), (float)a(2), (float)a(3));
		XMVECTOR vector2 = XMVectorSet((float)b(0), (float)b(1), (float)b(2), (float)b(3));
		XMVECTOR vectorSub = XMVectorSubtract(vector1, vector2);
		XMVECTOR length = XMVector4Length(vectorSub);

		float distance = 0.0f;
		XMStoreFloat(&distance, length);
		return distance;

	}
}