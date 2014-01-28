#ifndef __XNAConverter__
#define __XNAConverter__

#include "Linker.h"
#include <Vector.h>
#include <Windows.h>
#include <xnamath.h>
#include <Matrix.h>

CML::Matrix4x4 Convert4x4(const XMFLOAT4X4& xmMatrix);
XMFLOAT4X4 Convert4x4(const CML::Matrix4x4& matrix);

XMFLOAT4 ConvertVec4(const CML::Vec4& vector);
CML::Vec4 ConvertVec4(const XMFLOAT4& xmVector);

#endif //__XNAConverter__