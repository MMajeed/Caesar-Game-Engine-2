#ifndef __Constraint__
#define __Constraint__

#include "Linker.h"

#include <btBulletDynamicsCommon.h>

class Constraint
{
public:
	Constraint();

	virtual void Init() = 0;
	virtual void Destory();
	virtual ~Constraint(){}

	btTypedConstraint* pConstraint;
};

#endif //__Constraint__
