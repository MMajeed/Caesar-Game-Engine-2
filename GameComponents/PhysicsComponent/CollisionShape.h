#ifndef __CollisonShape__
#define __CollisonShape__

#include "Linker.h"

#include <btBulletDynamicsCommon.h>
#include <memory>

class PhysicsComponentDLL_API CollisionShape
{
protected:
	CollisionShape();
public:
	virtual void Init()	   = 0;
	virtual void Destory(){};
	virtual ~CollisionShape(){}

	std::shared_ptr<btCollisionShape> pCollisionShape;
};

#endif //__CollisonShape__
