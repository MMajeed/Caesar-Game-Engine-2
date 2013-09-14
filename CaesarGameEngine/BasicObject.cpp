#include "BasicObject.h"

#include "XNAToUblas.h"

BasicObject::BasicObject()
{
	boost::numeric::ublas::vector<double> matrix(4);
	matrix(0) = 0.0f;	matrix(1) = 0.0f;	matrix(2) = 0.0f;	matrix(3) = 0.0f; 
	this->Store(BasicObject::BasicObjectKeys::LOCATION, matrix);
	this->Store(BasicObject::BasicObjectKeys::ROTATION, matrix);
	this->Store(BasicObject::BasicObjectKeys::SCALE, matrix);
	this->Store(BasicObject::BasicObjectKeys::COLOUR, matrix);
}

boost::numeric::ublas::matrix<double> BasicObject::GetWorldLocation(boost::numeric::ublas::matrix<double> world, boost::numeric::ublas::matrix<double> prespective)
{
	XMFLOAT4X4  xmWorld = XNAToUblas::Convert4x4(world);

	XMFLOAT4X4  xmPrespective = XNAToUblas::Convert4x4(prespective);

	boost::numeric::ublas::matrix<double> object = this->GetMatrix();
	XMFLOAT4X4  xmObject = XNAToUblas::Convert4x4(object);

	XMMATRIX xmFinal = XMMatrixIdentity();

	xmFinal = XMMatrixMultiply(xmFinal, XMLoadFloat4x4(&xmWorld));
	xmFinal = XMMatrixMultiply(xmFinal, XMLoadFloat4x4(&xmPrespective));
	xmFinal = XMMatrixMultiply(xmFinal, XMLoadFloat4x4(&xmObject));
	
	XMFLOAT4X4 xm4x4;
	XMStoreFloat4x4(&xm4x4, xmFinal);

	boost::numeric::ublas::matrix<double> mFinal = XNAToUblas::Convert4x4(xm4x4);

	return mFinal;
}

boost::numeric::ublas::matrix<double> BasicObject::GetMatrix()
{
	XMMATRIX xmTranslate = XMMatrixIdentity();
	XMMATRIX xmRotateX = XMMatrixIdentity();	XMMATRIX xmRotateY = XMMatrixIdentity();	XMMATRIX xmRotateZ = XMMatrixIdentity();
	XMMATRIX xmScaling = XMMatrixIdentity();
	XMMATRIX xmObjectFinal = XMMatrixIdentity();

	const boost::numeric::ublas::vector<double> mLocation = this->Location();
	xmTranslate = XMMatrixTranslation( (float)mLocation(0), (float)mLocation(1), (float)mLocation(2));

	const boost::numeric::ublas::vector<double> mRotation = this->Rotation();
	xmRotateX = XMMatrixRotationX((float)mRotation(0));
	xmRotateY = XMMatrixRotationY((float)mRotation(1));
	xmRotateZ = XMMatrixRotationZ((float)mRotation(2));

	const boost::numeric::ublas::vector<double> mScale = this->Scale();
	xmScaling = XMMatrixScaling(mScale(0), mScale(1), mScale(2));

	
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

const boost::numeric::ublas::vector<double> BasicObject::Location()
{
	boost::numeric::ublas::vector<double> vec(4);
	this->Retrieve(BasicObject::BasicObjectKeys::LOCATION, vec);
	return vec;
}
void BasicObject::Location(boost::numeric::ublas::vector<double> value)
{
	this->Store(BasicObject::BasicObjectKeys::LOCATION, value);
}
const boost::numeric::ublas::vector<double> BasicObject::Rotation()
{	
	boost::numeric::ublas::vector<double> vec(4);
	this->Retrieve(BasicObject::BasicObjectKeys::ROTATION, vec);
	return vec;
}
void BasicObject::Rotation(boost::numeric::ublas::vector<double> value)
{
	this->Store(BasicObject::BasicObjectKeys::ROTATION, value);
}
const boost::numeric::ublas::vector<double> BasicObject::Scale()
{	
	boost::numeric::ublas::vector<double> vec(4);
	this->Retrieve(BasicObject::BasicObjectKeys::SCALE, vec);
	return vec;
}
void BasicObject::Scale(boost::numeric::ublas::vector<double> value)
{
	this->Store(BasicObject::BasicObjectKeys::SCALE, value);
}
const boost::numeric::ublas::vector<double> BasicObject::Colour()
{
	boost::numeric::ublas::vector<double> vec(4);
	this->Retrieve(BasicObject::BasicObjectKeys::COLOUR, vec);
	return vec;
}
void BasicObject::Colour(boost::numeric::ublas::vector<double> value)
{
	this->Store(BasicObject::BasicObjectKeys::COLOUR, value);
}

const std::string BasicObject::BasicObjectKeys::LOCATION = "Location";
const std::string BasicObject::BasicObjectKeys::ROTATION = "Rotation";
const std::string BasicObject::BasicObjectKeys::SCALE = "Scale";
const std::string BasicObject::BasicObjectKeys::COLOUR = "Colour";

std::shared_ptr<BasicObject> BasicObject::ConvertObjectPtr(std::shared_ptr<Object> obj)
{
	std::shared_ptr<BasicObject> basicObject = std::dynamic_pointer_cast<BasicObject>(obj);
	if(!basicObject)	
	{
		throw std::exception("Failed at casting std::shared_ptr<Object> to std::shared_ptr<BasicObject>");
	}
	return basicObject;
}