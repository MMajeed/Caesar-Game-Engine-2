#ifndef __SPOTLIGHT__
#define __SPOTLIGHT__

#include <Singleton.h>
#include "Buffers.h"
#include <SpotLightINFO.h>
#include <Matrix.h>

namespace SpotLight
{
	cBuffer::CLightDesc GetLightDesc(std::shared_ptr<SpotLightINFO> lightInfo);
	CHL::Matrix4x4 CalculateViewMatrix(std::shared_ptr<SpotLightINFO> lightInfo);
	CHL::Matrix4x4 CalculatePrespectiveMatrix(std::shared_ptr<SpotLightINFO> lightInfo);
}

#endif //__SPOTLIGHT__