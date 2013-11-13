#ifndef __SPOTLIGHT__
#define __SPOTLIGHT__

#include <Singleton.h>
#include <D3D11.h>
#include <Matrix.h>
#include "TypedefObject.h"
#include "Buffers.h"

class SpotLight : public CHL::Singelton<SpotLight>
{
public:
	virtual cBuffer::CLightDesc GetLightDesc(TypedefObject::ObjectInfo& lightInfo);
};

#endif //__SPOTLIGHT__