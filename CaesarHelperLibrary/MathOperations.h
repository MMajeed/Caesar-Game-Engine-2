#ifndef __MathOperations__
#define __MathOperations__

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>

namespace MathOperations
{
	using namespace boost::numeric::ublas;

	matrix<double> PerspectiveFovLHCalculation( double FovAngleY, double AspectRatio, double NearZ,  double FarZ);
	matrix<double> ViewCalculation(const vector<double>& vEye, const vector<double>& vTM,  const vector<double>& vUp, double pitch, double yaw, double roll );

	matrix<double> ObjectCalculation( const vector<double>& mLocation, const vector<double>& mRotation, const vector<double>& mScale);

	void Normalize(matrix<double>& matrix);

	vector<double> MoveForward(const vector<double>& vEye, const vector<double>& vTM, double pitch, double yaw, double roll, double distance);
};

#endif //__MathOperations__