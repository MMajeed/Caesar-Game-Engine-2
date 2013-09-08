#include "Prespective.h"

#include <windows.h>
#include <xnamath.h>

Prespective::Prespective()
{
	this->Store(Prespective::PrespectiveKeys::FOVANGLE, 0.0);
	this->Store(Prespective::PrespectiveKeys::WIDTH, 0.0);
	this->Store(Prespective::PrespectiveKeys::HEIGHT, 0.0);
	this->Store(Prespective::PrespectiveKeys::MINVIEWABLE, 0.0);
	this->Store(Prespective::PrespectiveKeys::MAXCIEWABLE, 0.0);
}

boost::numeric::ublas::matrix<double> Prespective::GetPrespective()
{
	XMMATRIX xmPrespective =  XMMatrixPerspectiveFovLH( (float)this->FovAngle(), (float)this->Width() / (float)this->Height(), (float)this->MinViewable(), (float)this->MaxViewable() );
	XMFLOAT4X4 xmMatrixPrespective;
	XMStoreFloat4x4(&xmMatrixPrespective, xmPrespective);

	boost::numeric::ublas::matrix<double> mMatrixPrespective(4, 4);

	for (unsigned i = 0; i < mMatrixPrespective.size1 (); ++ i)
        for (unsigned j = 0; j < mMatrixPrespective.size2 (); ++ j)
            mMatrixPrespective(i, j) = xmMatrixPrespective(i, j);

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