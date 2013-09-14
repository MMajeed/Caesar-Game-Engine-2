#include "Prespective.h"
#include "ObjectManager.h"
#include "MathOperations.h"

Prespective::Prespective()
{
	this->Store(Prespective::PrespectiveKeys::FOVANGLE, 0.0);
	this->Store(Prespective::PrespectiveKeys::WIDTH, 0.0);
	this->Store(Prespective::PrespectiveKeys::HEIGHT, 0.0);
	this->Store(Prespective::PrespectiveKeys::MINVIEWABLE, 0.0);
	this->Store(Prespective::PrespectiveKeys::MAXCIEWABLE, 0.0);
}

boost::numeric::ublas::matrix<double> Prespective::GetPrespectiveMatrix()
{
	boost::numeric::ublas::matrix<double> mMatrixPrespective =  MathOperation::MatrixPerspectiveFovLH(this->FovAngle(), this->Width() / this->Height(), this->MinViewable(), this->MaxViewable() );

	return mMatrixPrespective;
}

const double Prespective::FovAngle()
{
	double reutrnValue = 0.0f;
	this->Store(Prespective::PrespectiveKeys::FOVANGLE, reutrnValue);
	return reutrnValue;
}
void Prespective::FovAngle(double value)
{
	this->Store(Prespective::PrespectiveKeys::FOVANGLE, value);
}
const double Prespective::Width()
{
	double reutrnValue = 0.0f;
	this->Store(Prespective::PrespectiveKeys::WIDTH, reutrnValue);
	return reutrnValue;
}
void Prespective::Width(double value)
{
	this->Store(Prespective::PrespectiveKeys::WIDTH, value);
}
const double Prespective::Height()
{
	double reutrnValue = 0.0f;
	this->Store(Prespective::PrespectiveKeys::HEIGHT, reutrnValue);
	return reutrnValue;
}
void Prespective::Height(double value)
{
	this->Store(Prespective::PrespectiveKeys::HEIGHT, value);
}
const double Prespective::MinViewable()
{
	double reutrnValue = 0.0f;
	this->Store(Prespective::PrespectiveKeys::MINVIEWABLE, reutrnValue);
	return reutrnValue;
}
void Prespective::MinViewable(double value)
{
	this->Store(Prespective::PrespectiveKeys::MINVIEWABLE, value);
}
const double Prespective::MaxViewable()
{
	double reutrnValue = 0.0f;
	this->Store(Prespective::PrespectiveKeys::MAXCIEWABLE, reutrnValue);
	return reutrnValue;
}
void Prespective::MaxViewable(double value)
{
	this->Store(Prespective::PrespectiveKeys::MAXCIEWABLE, value);
}

const std::string Prespective::PrespectiveKeys::FOVANGLE = "FOVANGLE";
const std::string Prespective::PrespectiveKeys::WIDTH  = "WIDTH";
const std::string Prespective::PrespectiveKeys::HEIGHT  = "HEIGHT";
const std::string Prespective::PrespectiveKeys::MINVIEWABLE = "MINVIEWABLE";
const std::string Prespective::PrespectiveKeys::MAXCIEWABLE = "MAXVIEWABLE";

const std::shared_ptr<Prespective> Prespective::GetFirstOrDefultPrespective()
{
	std::shared_ptr<Object> obj;

	ObjectManager::GetInstance().AllObjects()
		.FirstOrDefault([](const std::shared_ptr<Object> obj){ return (std::dynamic_pointer_cast<Prespective>(obj)); }, obj);

	std::shared_ptr<Prespective> prespective = std::dynamic_pointer_cast<Prespective>(obj);
	return prespective;
}