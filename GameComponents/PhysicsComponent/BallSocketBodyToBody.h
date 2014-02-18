#ifndef __BallSocketBodyToBody__
#define __BallSocketBodyToBody__

#include "Linker.h"

#include <btBulletDynamicsCommon.h>

class BallSocketBodyToBody
{
public:
	BallSocketBodyToBody();

	virtual void Init() = 0;
	virtual void Destory();
	virtual ~BallSocketBodyToBody(){}
};

#endif //__BallSocketBodyToBody__
