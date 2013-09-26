#ifndef __XNAToUblas__
#define __XNAToUblas__

#include <boost/numeric/ublas/matrix.hpp>
#include <Windows.h>
#include <xnamath.h>

namespace XNAToUblas
{
	using namespace boost::numeric::ublas;

	matrix<double> Convert4x4(const XMFLOAT4X4& xmMatrix);
	XMFLOAT4X4 Convert4x4(const matrix<double>& matrix);

	XMFLOAT4 ConvertVec4(const vector<double>& vector);
	vector<double> ConvertVec4(const XMFLOAT4& xmVector);
};

#endif //__XNAToUblas__