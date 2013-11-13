#ifndef __DIRECTLIGHT__
#define __DIRECTLIGHT__

#include <Singleton.h>
#include <D3D11.h>
#include <Matrix.h>
#include "TypedefObject.h"
#include "Buffers.h"

class DirectLight : public CHL::Singelton<DirectLight>
{
public:
	virtual cBuffer::CLightDesc GetLightDesc(TypedefObject::ObjectInfo& lightInfo);
};

#endif //__DIRECTLIGHT__