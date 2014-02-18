#ifndef __ConeShape__
#define __ConeShape__

#include "Linker.h"

#include "CollisionShape.h"
#include <memory>
#include <Vector.h>

class ConeShape : public CollisionShape
{
protected:
	ConeShape(){}
public:
	virtual void Init();

	struct
	{
		double Radius;
		double Height;
	}Info;

	static std::shared_ptr<ConeShape> Spawn(double radius, double height);
};

#endif //__ConeShape__
