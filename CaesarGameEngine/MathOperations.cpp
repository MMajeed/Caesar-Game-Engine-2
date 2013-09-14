#include "MathOperations.h"

#include "MatrixConverter.h"

#include <Windows.h>
#include <xnamath.h>

boost::numeric::ublas::matrix<double> MathOperation::MatrixPerspectiveFovLH( double FovAngleY, double AspectRatio, double NearZ,  double FarZ)
{
	XMMATRIX xmPrespective =  XMMatrixPerspectiveFovLH( (float)FovAngleY, (float)AspectRatio, (float)NearZ, (float)FarZ);
	xmPrespective = XMMatrixTranspose(xmPrespective);
	XMFLOAT4X4 xmMatrixPrespective;
	XMStoreFloat4x4(&xmMatrixPrespective, xmPrespective);

	boost::numeric::ublas::matrix<double> mMatrixPrespective =  MatrixConverter::Convert4x4(xmMatrixPrespective);

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
	
	boost::numeric::ublas::matrix<double> mView = MatrixConverter::Convert4x4(xmView);

	return mView;
}