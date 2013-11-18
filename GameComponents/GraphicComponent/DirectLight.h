#ifndef __DIRECTLIGHT__
#define __DIRECTLIGHT__

#include <Singleton.h>
#include <DirectionalLightINFO.h>
#include "Buffers.h"

namespace DirectLight
{
	cBuffer::CLightDesc GetLightDesc(std::shared_ptr<DirectionalLightINFO> lightInfo);
}

#endif //__DIRECTLIGHT__