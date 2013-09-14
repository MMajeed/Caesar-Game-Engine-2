#include "MathOperations.h"

#include "XNAToUblas.h"

#include <Windows.h>
#include <xnamath.h>

boost::numeric::ublas::matrix<double> MathOperation::PerspectiveFovLHCalculation( double FovAngleY, double AspectRatio, double NearZ,  double FarZ)
{
	XMMATRIX xmPrespective =  XMMatrixPerspectiveFovLH( (float)FovAngleY, (float)AspectRatio, (float)NearZ, (float)FarZ);
	xmPrespective = XMMatrixTranspose(xmPrespective);
	XMFLOAT4X4 xmMatrixPrespective;
	XMStoreFloat4x4(&xmMatrixPrespective, xmPrespective);

	boost::numeric::ublas::matrix<double> mMatrixPrespective =  XNAToUblas::Convert4x4(xmMatrixPrespective);

	return mMatrixPrespective;
}

boost::numeric::ublas::matrix<double> MathOperation::ViewCalculation( boost::numeric::ublas::vector<double> vEye, boost::numeric::ublas::vector<double> vTM,  boost::numeric::ublas::vector<double> vUp, double pitch, double yaw, double roll)
{
	XMVECTOR xmEye = XMVectorSet( (float)vEye(0), (float)vEye(1), (float)vEye(2), (float)vEye(3) );
	XMVECTOR xmTM = XMVectorSet(  (float)vTM(0), (float)vTM(1), (float)vTM(2), (float)vTM(3) );
	XMVECTOR xmUp = XMVectorSet(  (float)vUp(0), (float)vUp(1), (float)vUp(2), (float)vUp(3) );

	XMMATRIX RotationMatrix( XMMatrixRotationRollPitchYaw( (float)pitch, (float)yaw, (float)roll ));

	xmTM = XMVector3TransformCoord( xmTM, RotationMatrix );
    xmUp = XMVector3TransformCoord( xmUp, RotationMatrix );
	
	xmTM += xmEye;
	
	XMFLOAT4X4  xmView;
	XMStoreFloat4x4(&xmView, XMMatrixTranspose(XMMatrixLookAtLH( xmEye, xmTM, xmUp )));
	
	boost::numeric::ublas::matrix<double> mView = XNAToUblas::Convert4x4(xmView);

	return mView;
}

boost::numeric::ublas::matrix<double> MathOperation::ObjectCalculation( boost::numeric::ublas::vector<double> mLocation, boost::numeric::ublas::vector<double> mRotation, boost::numeric::ublas::vector<double> mScale)
{
	XMMATRIX xmTranslate = XMMatrixIdentity();
	XMMATRIX xmRotateX = XMMatrixIdentity();	XMMATRIX xmRotateY = XMMatrixIdentity();	XMMATRIX xmRotateZ = XMMatrixIdentity();
	XMMATRIX xmScaling = XMMatrixIdentity();
	XMMATRIX xmObjectFinal = XMMatrixIdentity();

	xmTranslate = XMMatrixTranslation( (float)mLocation(0), (float)mLocation(1), (float)mLocation(2));

	xmRotateX = XMMatrixRotationX((float)mRotation(0));
	xmRotateY = XMMatrixRotationY((float)mRotation(1));
	xmRotateZ = XMMatrixRotationZ((float)mRotation(2));

	xmScaling = XMMatrixScaling((float)mScale(0), (float)mScale(1), (float)mScale(2));

	
	xmObjectFinal = XMMatrixMultiply(xmObjectFinal, xmScaling);
	xmObjectFinal = XMMatrixMultiply(xmObjectFinal, xmRotateX);
	xmObjectFinal = XMMatrixMultiply(xmObjectFinal, xmRotateY);
	xmObjectFinal = XMMatrixMultiply(xmObjectFinal, xmRotateZ);
	xmObjectFinal = XMMatrixMultiply(xmObjectFinal, xmTranslate);
	xmObjectFinal = XMMatrixTranspose(xmObjectFinal);

	XMFLOAT4X4 xmFinal4x4;
	XMStoreFloat4x4(&xmFinal4x4, xmObjectFinal);

	boost::numeric::ublas::matrix<double> mObjectFinal = XNAToUblas::Convert4x4(xmFinal4x4);

	return mObjectFinal;
}