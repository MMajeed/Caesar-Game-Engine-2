#ifndef __DIRECTLIGHT__
#define __DIRECTLIGHT__

#include <Singleton.h>
#include <DirectionalLightINFO.h>
#include "Buffers.h"
#include <Matrix.h>

namespace DirectLight
{
	cBuffer::CLightDesc GetLightDesc(std::shared_ptr<DirectionalLightINFO> lightInfo);
	CHL::Matrix4x4 CalculateViewMatrix(std::shared_ptr<DirectionalLightINFO> lightInfo);
	CHL::Matrix4x4 CalculatePrespectiveMatrix(std::shared_ptr<DirectionalLightINFO> lightInfo);
	static const float radius = 50.0f; 
}

#endif //__DIRECTLIGHT__