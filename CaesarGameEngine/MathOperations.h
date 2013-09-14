#ifndef __MathOperation__
#define __MathOperation__

#include <boost/numeric/ublas/matrix.hpp>

class MathOperation
{
public:
	static boost::numeric::ublas::matrix<double> MatrixPerspectiveFovLH( double FovAngleY, double AspectRatio, double NearZ,  double FarZ);
	static boost::numeric::ublas::matrix<double> ViewCalculation( boost::numeric::ublas::vector<double> vEye, boost::numeric::ublas::vector<double> vTM,  boost::numeric::ublas::vector<double> vUp, double pitch, double yaw, double roll );
};

#endif //__MathOperation__