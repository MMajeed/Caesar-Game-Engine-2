#ifndef __BoxShape__
#define __BoxShape__

#include "Linker.h"

#include "CollisionShape.h"
#include <memory>
#include <Vector.h>

class BoxShape : public CollisionShape
{
protected:
	BoxShape(){}
public:
	virtual void Init();

	struct
	{
		CML::Vec3 HalfExtents;
	}Info;

	static std::shared_ptr<BoxShape> Spawn(CML::Vec3 halfExtent);
};

#endif //__BoxShape__
