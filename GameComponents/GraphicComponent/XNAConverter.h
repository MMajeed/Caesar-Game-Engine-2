#ifndef __XNAConverter__
#define __XNAConverter__

#include "Linker.h"
#include <Vector.h>
#include <Windows.h>
#include <xnamath.h>
#include <Matrix.h>

GraphicComponentDLL_API CML::Matrix4x4 Convert4x4(const XMFLOAT4X4& xmMatrix);
GraphicComponentDLL_API XMFLOAT4X4 Convert4x4(const CML::Matrix4x4& matrix);

GraphicComponentDLL_API XMFLOAT4 ConvertVec4(const CML::Vec4& vector);
GraphicComponentDLL_API CML::Vec4 ConvertVec4(const XMFLOAT4& xmVector);

#endif //__XNAConverter__