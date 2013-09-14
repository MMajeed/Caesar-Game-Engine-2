#include "BasicObject.h"

#include "XNAToUblas.h"
#include "MathOperations.h"
#include "Keys.h"

BasicObject::BasicObject(std::string ID)
	: Object(ID)
{
	boost::numeric::ublas::vector<double> matrix(4);
	matrix(0) = 0.0f;	matrix(1) = 0.0f;	matrix(2) = 0.0f;	matrix(3) = 0.0f; 
	this->Store(Keys::LOCATION, matrix);
	this->Store(Keys::ROTATION, matrix);
	this->Store(Keys::SCALE, matrix);
	this->Store(Keys::COLOUR, matrix);

	this->Store(Keys::Class, Keys::ClassType::BasicObject);
}

boost::numeric::ublas::matrix<double> BasicObject::GetWorldLocation(boost::numeric::ublas::matrix<double> camera, boost::numeric::ublas::matrix<double> prespective)
{
	boost::numeric::ublas::matrix<double> mFinal(4,4);

	mFinal = boost::numeric::ublas::prod(mFinal, this->GetMatrix());
	mFinal = boost::numeric::ublas::prod(mFinal, camera);
	mFinal = boost::numeric::ublas::prod(mFinal, prespective);

	return mFinal;
}

boost::numeric::ublas::matrix<double> BasicObject::GetMatrix()
{
	boost::numeric::ublas::matrix<double> mObjectFinal = MathOperation::ObjectCalculation(this->Location(), this->Rotation(), this->Scale());
	return mObjectFinal;
}

const boost::numeric::ublas::vector<double> BasicObject::Location()
{
	boost::numeric::ublas::vector<double> vec(4);
	this->Retrieve(Keys::LOCATION, vec);
	return vec;
}
void BasicObject::Location(boost::numeric::ublas::vector<double> value)
{
	this->Store(Keys::LOCATION, value);
}
const boost::numeric::ublas::vector<double> BasicObject::Rotation()
{	
	boost::numeric::ublas::vector<double> vec(4);
	this->Retrieve(Keys::ROTATION, vec);
	return vec;
}
void BasicObject::Rotation(boost::numeric::ublas::vector<double> value)
{
	this->Store(Keys::ROTATION, value);
}
const boost::numeric::ublas::vector<double> BasicObject::Scale()
{	
	boost::numeric::ublas::vector<double> vec(4);
	this->Retrieve(Keys::SCALE, vec);
	return vec;
}
void BasicObject::Scale(boost::numeric::ublas::vector<double> value)
{
	this->Store(Keys::SCALE, value);
}
const boost::numeric::ublas::vector<double> BasicObject::Colour()
{
	boost::numeric::ublas::vector<double> vec(4);
	this->Retrieve(Keys::COLOUR, vec);
	return vec;
}
void BasicObject::Colour(boost::numeric::ublas::vector<double> value)
{
	this->Store(Keys::COLOUR, value);
}

std::shared_ptr<BasicObject> BasicObject::ConvertObjectPtr(std::shared_ptr<Object> obj)
{
	std::shared_ptr<BasicObject> basicObject = std::dynamic_pointer_cast<BasicObject>(obj);
	if(!basicObject)	
	{
		throw std::exception("Failed at casting Object to std::shared_ptr<BasicObject>");
	}
	return basicObject;
}