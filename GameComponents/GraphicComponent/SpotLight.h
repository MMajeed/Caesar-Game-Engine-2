#ifndef __SPOTLIGHT__
#define __SPOTLIGHT__

#include <Singleton.h>
#include "Buffers.h"
#include <SpotLightINFO.h>

namespace SpotLight
{
	cBuffer::CLightDesc GetLightDesc(std::shared_ptr<SpotLightINFO> lightInfo);
}

#endif //__SPOTLIGHT__