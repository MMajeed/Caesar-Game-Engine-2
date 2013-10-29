#include "XNAConverter.h"

CHL::Matrix4x4 CHL::Convert4x4(const XMFLOAT4X4& xmMatrix)
{	
	CHL::Matrix4x4 matrix;

	for (unsigned i = 0; i < 4; ++ i)
        for (unsigned j = 0; j < 4; ++ j)
            matrix(i, j) = (double)xmMatrix(i, j);

	return matrix;
}
XMFLOAT4X4 CHL::Convert4x4(const CHL::Matrix4x4& matrix)
{
	XMFLOAT4X4 xmMatrix;

	for (unsigned i = 0; i < 4; ++ i)
        for (unsigned j = 0; j < 4; ++ j)
            xmMatrix(i, j) = (float)matrix(i, j);

	return xmMatrix;
}

XMFLOAT4 CHL::ConvertVec4(const CHL::Vec4& vector)
{
	return XMFLOAT4((float)vector(0), (float)vector(1), (float)vector(2), (float)vector(3));
}
CHL::Vec4 CHL::ConvertVec4(const XMFLOAT4& xmVector)
{
	CHL::Vec4 vector;
	vector(0) = xmVector.x; vector(1) = xmVector.y; vector(2) = xmVector.z; vector(3) = xmVector.w;
	return vector;
}