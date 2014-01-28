#include "XNAConverter.h"

CML::Matrix4x4 Convert4x4(const XMFLOAT4X4& xmMatrix)
{	
	CML::Matrix4x4 matrix;

	for (unsigned i = 0; i < 4; ++ i)
        for (unsigned j = 0; j < 4; ++ j)
            matrix(i, j) = (double)xmMatrix(i, j);

	return matrix;
}
XMFLOAT4X4 Convert4x4(const CML::Matrix4x4& matrix)
{
	XMFLOAT4X4 xmMatrix;

	for (unsigned i = 0; i < 4; ++ i)
        for (unsigned j = 0; j < 4; ++ j)
            xmMatrix(i, j) = (float)matrix(i, j);

	return xmMatrix;
}

XMFLOAT4 ConvertVec4(const CML::Vec4& vector)
{
	return XMFLOAT4((float)vector(0), (float)vector(1), (float)vector(2), (float)vector(3));
}
CML::Vec4 ConvertVec4(const XMFLOAT4& xmVector)
{
	CML::Vec4 vector{xmVector.x, xmVector.y, xmVector.z, xmVector.w};
	return vector;
}