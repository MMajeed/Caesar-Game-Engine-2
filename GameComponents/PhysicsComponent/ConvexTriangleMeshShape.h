#ifndef __ConvexTriangleMeshShape__
#define __ConvexTriangleMeshShape__

#include "Linker.h"

#include "CollisionShape.h"
#include <memory>
#include <Model.h>
#include <vector>

class ConvexTriangleMeshShape : public CollisionShape
{
public:
	ConvexTriangleMeshShape();

	virtual void Init();

	struct
	{
		btTriangleMesh* Mesh;
	}Info;

	static std::shared_ptr<ConvexTriangleMeshShape > Spawn(std::shared_ptr<CHL::Model> model);
};

#endif //__ConvexTriangleMeshShape __
