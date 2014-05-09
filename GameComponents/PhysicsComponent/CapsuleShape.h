#ifndef __CapsuleShape__
#define __CapsuleShape__

#include "Linker.h"

#include "CollisionShape.h"
#include <memory>
#include <Vector.h>

class PhysicsComponentDLL_API CapsuleShape : public CollisionShape
{
protected:
	CapsuleShape(){}
public:
	virtual void Init();

	struct
	{
		double Radius;
		double Height;
	}Info;

	static std::shared_ptr<CapsuleShape> Spawn(double radius, double height);
};

#endif //__CapsuleShape__
