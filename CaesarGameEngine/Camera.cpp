#include "Camera.h"

#include "MathOperations.h"
#include "MatrixConverter.h"
#include "ObjectManager.h"

Camera::Camera()
{
	boost::numeric::ublas::vector<double> eye(4);
	eye(0) = 0.0f;	eye(1) = 5.0f;	eye(2) = -20.0f;	eye(3) = 0.0f; 
	this->Store(Camera::CameraKeys::EYE, eye);
	boost::numeric::ublas::vector<double> target(4);
	target(0) = 0.0f;	target(1) = 0.0f;	target(2) = 10.0f;	target(3) = 0.0f; 
	this->Store(Camera::CameraKeys::TARGETMAGNITUDE, target);
	boost::numeric::ublas::vector<double> up(4);
	up(0) = 0.0f;	up(1) = 1.0f;	up(2) = 0.0f;	up(3) = 0.0f; 
	this->Store(Camera::CameraKeys::UP, up);

	this->Store(Camera::CameraKeys::RADIANROLL, 0.0);
	this->Store(Camera::CameraKeys::RADIANPITCH, 0.0);
	this->Store(Camera::CameraKeys::RADIANYAW, 0.0);
}

void Camera::MoveForward(float delta)
{
	boost::numeric::ublas::vector<double> vEye = this->Eye();
	XMVECTOR xmEye = XMVectorSet( (float)vEye(0), (float)vEye(1), (float)vEye(2), (float)vEye(3) );
	boost::numeric::ublas::vector<double> vTM = this->TargetMagnitude();
	XMVECTOR xmTM = XMVectorSet(  (float)vTM(0), (float)vTM(1), (float)vTM(2), (float)vTM(3) );
	
	XMMATRIX RotationMatrix( XMMatrixRotationRollPitchYaw( (float)this->RadianPitch(), (float)this->RadianYaw(), (float)this->RadianRoll() ));

	xmTM = XMVector3TransformCoord( xmTM, RotationMatrix );
	xmTM = XMVector4Normalize(xmTM);
	xmEye += xmTM * delta;

	XMFLOAT4 xmNewEye;	
	XMStoreFloat4(&xmNewEye, xmEye);
	boost::numeric::ublas::vector<double> vNewEye(4);

	vNewEye(0) = xmNewEye.x; vNewEye(1) = xmNewEye.w;  vNewEye(2) = xmNewEye.z;  vNewEye(3) = xmNewEye.w;
	this->Eye(vNewEye);
}

boost::numeric::ublas::matrix<double> Camera::GetViewMatrix()
{
	boost::numeric::ublas::matrix<double> mView = MathOperation::ViewCalculation(this->Eye(), this->TargetMagnitude(), this->Up(), this->RadianPitch(),  this->RadianYaw(),  this->RadianRoll());

	return mView;
}

const boost::numeric::ublas::vector<double> Camera::Eye()
{
	boost::numeric::ublas::vector<double> vec(4);
	this->Retrieve(Camera::CameraKeys::EYE, vec);
	return vec;
}
const boost::numeric::ublas::vector<double> Camera::TargetMagnitude()
{
	boost::numeric::ublas::vector<double> vec(4);
	this->Retrieve(Camera::CameraKeys::TARGETMAGNITUDE, vec);
	return vec;
}
const boost::numeric::ublas::vector<double> Camera::Up()
{
	boost::numeric::ublas::vector<double> vec(4);
	this->Retrieve(Camera::CameraKeys::UP, vec);
	return vec;
}
void Camera::Eye(boost::numeric::ublas::vector<double> vec)
{
	this->Store(Camera::CameraKeys::EYE, vec);
}
void Camera::TargetMagnitude(boost::numeric::ublas::vector<double> vec)
{
	this->Store(Camera::CameraKeys::TARGETMAGNITUDE, vec);
}
void Camera::Up(boost::numeric::ublas::vector<double> vec)
{
	this->Store(Camera::CameraKeys::UP, vec);
}
const double Camera::RadianRoll()
{
	double reutrnValue = 0.0f;
	this->Store(Camera::CameraKeys::RADIANROLL, reutrnValue);
	return reutrnValue;
}
const double Camera::RadianPitch()
{
	double reutrnValue = 0.0f;
	this->Store(Camera::CameraKeys::RADIANPITCH, reutrnValue);
	return reutrnValue;
}
const double Camera::RadianYaw()
{	
	double reutrnValue = 0.0f;
	this->Store(Camera::CameraKeys::RADIANYAW, reutrnValue);
	return reutrnValue;
}
void Camera::RadianRoll(double value)
{
	this->Store(Camera::CameraKeys::RADIANROLL, value);
}
void Camera::RadianPitch(double value)
{
	this->Store(Camera::CameraKeys::RADIANPITCH, value);
}
void Camera::RadianYaw(double value)
{
	this->Store(Camera::CameraKeys::RADIANYAW, value);
}

const std::string Camera::CameraKeys::EYE = "EYE";
const std::string Camera::CameraKeys::TARGETMAGNITUDE  = "TARGETMAGNITUDE";
const std::string Camera::CameraKeys::UP  = "UP";
const std::string Camera::CameraKeys::RADIANROLL  = "RADIANROLL";
const std::string Camera::CameraKeys::RADIANPITCH  = "RADIANPITCH";
const std::string Camera::CameraKeys::RADIANYAW  = "RADIANYAW";

const std::shared_ptr<Camera> Camera::GetFirstOrDefultCamera()
{
	std::shared_ptr<Object> obj;

	ObjectManager::GetInstance().AllObjects()
		.FirstOrDefault([](const std::shared_ptr<Object> obj){ return (std::dynamic_pointer_cast<Camera>(obj)); }, obj);

	std::shared_ptr<Camera> camera = std::dynamic_pointer_cast<Camera>(obj);
	return camera;
}