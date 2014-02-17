#ifndef __CylinderShape__
#define __CylinderShape__

#include "Linker.h"

#include "CollisionShape.h"
#include <memory>
#include <Vector.h>

class CylinderShape : public CollisionShape
{
public:
	virtual void Init();

	struct
	{
		CML::Vec3 HalfExtents;
	}Info;

	static std::shared_ptr<CylinderShape> Spawn(CML::Vec3 halfExtent);
};

#endif //__CylinderShape__
