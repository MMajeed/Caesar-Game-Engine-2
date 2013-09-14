#include "Prespective.h"
#include "ObjectManager.h"
#include "MathOperations.h"
#include "Keys.h"

Prespective::Prespective(std::string ID)
	: Object(ID)
{
	this->Store(Keys::FOVANGLE, 0.0);
	this->Store(Keys::SCREENWIDTH, 0.0);
	this->Store(Keys::SCREENHEIGHT, 0.0);
	this->Store(Keys::MINVIEWABLE, 0.0);
	this->Store(Keys::MAXCIEWABLE, 0.0);
	this->Store(Keys::Class, Keys::ClassType::Prespective);
}

boost::numeric::ublas::matrix<double> Prespective::GetPrespectiveMatrix()
{
	boost::numeric::ublas::matrix<double> mMatrixPrespective =  MathOperation::PerspectiveFovLHCalculation(this->FovAngle(), this->Width() / this->Height(), this->MinViewable(), this->MaxViewable() );

	return mMatrixPrespective;
}

const double Prespective::FovAngle()
{
	double reutrnValue = 0.0f;
	this->Store(Keys::FOVANGLE, reutrnValue);
	return reutrnValue;
}
void Prespective::FovAngle(double value)
{
	this->Store(Keys::FOVANGLE, value);
}
const double Prespective::Width()
{
	double reutrnValue = 0.0f;
	this->Store(Keys::SCREENWIDTH, reutrnValue);
	return reutrnValue;
}
void Prespective::Width(double value)
{
	this->Store(Keys::SCREENWIDTH, value);
}
const double Prespective::Height()
{
	double reutrnValue = 0.0f;
	this->Store(Keys::SCREENHEIGHT, reutrnValue);
	return reutrnValue;
}
void Prespective::Height(double value)
{
	this->Store(Keys::SCREENHEIGHT, value);
}
const double Prespective::MinViewable()
{
	double reutrnValue = 0.0f;
	this->Store(Keys::MINVIEWABLE, reutrnValue);
	return reutrnValue;
}
void Prespective::MinViewable(double value)
{
	this->Store(Keys::MINVIEWABLE, value);
}
const double Prespective::MaxViewable()
{
	double reutrnValue = 0.0f;
	this->Store(Keys::MAXCIEWABLE, reutrnValue);
	return reutrnValue;
}
void Prespective::MaxViewable(double value)
{
	this->Store(Keys::MAXCIEWABLE, value);
}

const std::shared_ptr<Prespective> Prespective::GetFirstOrDefultPrespective()
{
	std::shared_ptr<Object> obj;

	ObjectManager::GetInstance().AllObjects()
		.FirstOrDefault([](const std::shared_ptr<Object> obj){ return (std::dynamic_pointer_cast<Prespective>(obj)); }, obj);

	std::shared_ptr<Prespective> prespective = std::dynamic_pointer_cast<Prespective>(obj);
	return prespective;
}