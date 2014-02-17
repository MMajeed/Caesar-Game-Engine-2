#ifndef __ConvexHullShape__
#define __ConvexHullShape__

#include "Linker.h"

#include "CollisionShape.h"
#include <memory>
#include <Model.h>
#include <vector>

class ConvexHullShape  : public CollisionShape
{
public:
	virtual void Init();

	struct
	{
		std::vector<float> points;
		unsigned int stride;
	}Info;

	static std::shared_ptr<ConvexHullShape > Spawn(std::shared_ptr<CHL::Model> model);
};

#endif //__ConvexHullShape __
