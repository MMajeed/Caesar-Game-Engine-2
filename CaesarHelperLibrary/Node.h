#ifndef __Nodes__
#define __Nodes__

#include "Linker.h"
#include "Vector.h"
#include "Matrix.h"
#include <string>
#include <vector>
#include <memory>

namespace CHL
{
	class Node
	{
	public:
		std::string Name;
		CHL::Matrix4x4 Transformation;
		std::shared_ptr<Node> Parent;
		std::vector<std::shared_ptr<Node>> Childern;
		std::vector<int> meshes;
		Node();
	};
}

#endif //__Nodes__