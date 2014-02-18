#ifndef __ConstraintConfig__
#define __ConstraintConfig__

#include "Linker.h"
#include <string>
#include <Vector.h>

namespace ConstraintConfig
{
	std::string CreateBallSocketBodyToPoint(std::string RigidBodyID, CML::Vec3 PivotPoint);

	void Release(std::string ID);
}

#endif //__ConstraintConfig__
