#ifndef __CollisonShape__
#define __CollisonShape__

#include "Linker.h"

#include <btBulletDynamicsCommon.h>

class CollisionShape
{
public:
	CollisionShape();

	virtual void Init()	   = 0;
	virtual void Destory();
	virtual ~CollisionShape(){}

	btCollisionShape* pCollisionShape;
};

#endif //__CollisonShape__
