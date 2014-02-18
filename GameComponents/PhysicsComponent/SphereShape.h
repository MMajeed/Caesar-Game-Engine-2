#ifndef __SphereShape__
#define __SphereShape__

#include "Linker.h"

#include "CollisionShape.h"
#include <memory>

class SphereShape : public CollisionShape
{
protected:
	SphereShape(){}
public:
	virtual void Init();

	struct
	{
		double Radius;
	}Info;
	
	static std::shared_ptr<SphereShape> Spawn(double radius);
};

#endif //__SphereShape__
