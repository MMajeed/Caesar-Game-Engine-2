#ifndef __Constraint__
#define __Constraint__

#include "Linker.h"

#include <btBulletDynamicsCommon.h>
#include <memory>

class Constraint
{
protected:
	Constraint();
public:
	virtual void Init() = 0;
	virtual void Destory(){};
	virtual ~Constraint(){}

	std::shared_ptr<btTypedConstraint> pConstraint;
};

#endif //__Constraint__
