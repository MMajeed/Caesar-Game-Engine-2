#ifndef __PointLight__
#define __PointLight__

#include <Singleton.h>
#include "Buffers.h"
#include <PointLightINFO.h>

namespace PointLight
{
	cBuffer::CLightDesc GetLightDesc(std::shared_ptr<PointLightINFO> lightInfo);
}

#endif //__PointLight__