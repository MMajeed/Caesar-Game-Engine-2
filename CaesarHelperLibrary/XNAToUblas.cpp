#include "XNAToUblas.h"

using namespace boost::numeric::ublas;

matrix<double> XNAToUblas::Convert4x4(const XMFLOAT4X4& xmMatrix)
{	
	matrix<double> matrix(4, 4);

	for (unsigned i = 0; i < matrix.size1(); ++ i)
        for (unsigned j = 0; j < matrix.size2(); ++ j)
            matrix(i, j) = (double)xmMatrix(i, j);

	return matrix;
}
XMFLOAT4X4 XNAToUblas::Convert4x4(const matrix<double>& matrix)
{
	XMFLOAT4X4 xmMatrix;

	for (unsigned i = 0; i < matrix.size1(); ++ i)
        for (unsigned j = 0; j < matrix.size2(); ++ j)
            xmMatrix(i, j) = (float)matrix(i, j);

	return xmMatrix;
}

XMFLOAT4 XNAToUblas::ConvertVec4(const vector<double>& vector)
{
	return XMFLOAT4((float)vector(0), (float)vector(1), (float)vector(2), (float)vector(3));
}
vector<double> XNAToUblas::ConvertVec4(const XMFLOAT4& xmVector)
{
	vector<double> vector(4);
	vector(0) = xmVector.x; vector(1) = xmVector.y; vector(2) = xmVector.z; vector(3) = xmVector.w;
	return vector;
}