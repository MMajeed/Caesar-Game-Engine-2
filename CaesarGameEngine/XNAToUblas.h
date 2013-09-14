#ifndef __XNAToUblas__
#define __XNAToUblas__

#include <boost/numeric/ublas/matrix.hpp>
#include <Windows.h>
#include <xnamath.h>

class XNAToUblas
{
public:
	static boost::numeric::ublas::matrix<double> Convert4x4(XMFLOAT4X4 xmMatrix);
	static XMFLOAT4X4 Convert4x4(boost::numeric::ublas::matrix<double> matrix);

	static XMFLOAT4 ConvertVec4(boost::numeric::ublas::vector<double> vector);
	static boost::numeric::ublas::vector<double> ConvertVec4(XMFLOAT4 xmVector);
};

#endif //__XNAToUblas__