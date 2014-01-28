#ifndef __XNAConverter__
#define __XNAConverter__

#include "Linker.h"
#include "Matrix.h"
#include "Vector.h"
#include <Windows.h>
#include <xnamath.h>

namespace CHL
{
	CHL::Matrix4x4 Convert4x4(const XMFLOAT4X4& xmMatrix);
	XMFLOAT4X4 Convert4x4(const CHL::Matrix4x4& matrix);

	XMFLOAT4 ConvertVec4(const CHL::Vec4& vector);
	CHL::Vec4 ConvertVec4(const XMFLOAT4& xmVector);
};

#endif //__XNAConverter__