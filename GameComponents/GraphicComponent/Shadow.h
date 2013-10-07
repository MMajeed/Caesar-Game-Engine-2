#ifndef _SHADOW__
#define _SHADOW__

#include "TypedefObject.h"

class Shadow
{
public:
	virtual void Init()	= 0;
	virtual void GenerateShadowTexture(TypedefObject::ObjectInfo& light,
									  TypedefObject::ObjectVector& objects) = 0;
};

#endif //_SHADOW__