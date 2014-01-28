#include "Node.h"
#include "3DMath.h"

namespace CHL
{
	Node::Node()
		: Transformation({{1.0, 0.0, 0.0, 0.0},
						  {0.0, 1.0, 0.0, 0.0},
						  {0.0, 0.0, 1.0, 0.0},
						  {0.0, 0.0, 0.0, 1.0}})
	{
	}
}