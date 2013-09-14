#include "Camera.h"

#include "MathOperations.h"
#include "XNAToUblas.h"
#include "ObjectManager.h"
#include "Keys.h"

Camera::Camera(std::string ID)
	: Object(ID)
{
	boost::numeric::ublas::vector<double> eye(4);
	eye(0) = 0.0f;	eye(1) = 5.0f;	eye(2) = -20.0f;	eye(3) = 0.0f; 
	this->Store(Keys::EYE, eye);
	boost::numeric::ublas::vector<double> target(4);
	target(0) = 0.0f;	target(1) = 0.0f;	target(2) = 10.0f;	target(3) = 0.0f; 
	this->Store(Keys::TARGETMAGNITUDE, target);
	boost::numeric::ublas::vector<double> up(4);
	up(0) = 0.0f;	up(1) = 1.0f;	up(2) = 0.0f;	up(3) = 0.0f; 
	this->Store(Keys::UP, up);

	this->Store(Keys::RADIANROLL, 0.0);
	this->Store(Keys::RADIANPITCH, 0.0);
	this->Store(Keys::RADIANYAW, 0.0);

	this->Store(Keys::Class, Keys::ClassType::Camera);
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
	this->Retrieve(Keys::EYE, vec);
	return vec;
}
const boost::numeric::ublas::vector<double> Camera::TargetMagnitude()
{
	boost::numeric::ublas::vector<double> vec(4);
	this->Retrieve(Keys::TARGETMAGNITUDE, vec);
	return vec;
}
const boost::numeric::ublas::vector<double> Camera::Up()
{
	boost::numeric::ublas::vector<double> vec(4);
	this->Retrieve(Keys::UP, vec);
	return vec;
}
void Camera::Eye(boost::numeric::ublas::vector<double> vec)
{
	this->Store(Keys::EYE, vec);
}
void Camera::TargetMagnitude(boost::numeric::ublas::vector<double> vec)
{
	this->Store(Keys::TARGETMAGNITUDE, vec);
}
void Camera::Up(boost::numeric::ublas::vector<double> vec)
{
	this->Store(Keys::UP, vec);
}
const double Camera::RadianRoll()
{
	double reutrnValue = 0.0f;
	this->Store(Keys::RADIANROLL, reutrnValue);
	return reutrnValue;
}
const double Camera::RadianPitch()
{
	double reutrnValue = 0.0f;
	this->Store(Keys::RADIANPITCH, reutrnValue);
	return reutrnValue;
}
const double Camera::RadianYaw()
{	
	double reutrnValue = 0.0f;
	this->Store(Keys::RADIANYAW, reutrnValue);
	return reutrnValue;
}
void Camera::RadianRoll(double value)
{
	this->Store(Keys::RADIANROLL, value);
}
void Camera::RadianPitch(double value)
{
	this->Store(Keys::RADIANPITCH, value);
}
void Camera::RadianYaw(double value)
{
	this->Store(Keys::RADIANYAW, value);
}

const std::shared_ptr<Camera> Camera::GetFirstOrDefultCamera()
{
	std::shared_ptr<Object> obj;

	ObjectManager::GetInstance().AllObjects()
		.FirstOrDefault([](const std::shared_ptr<Object> obj){ return (std::dynamic_pointer_cast<Camera>(obj)); }, obj);

	std::shared_ptr<Camera> camera = std::dynamic_pointer_cast<Camera>(obj);
	return camera;
}