#ifndef __Nodes__
#define __Nodes__

#include "Linker.h"
#include <Vector.h>
#include <string>
#include <vector>
#include <memory>
#include <Matrix.h>

namespace CHL
{
	class CaesarModelLibraryDLL_API Node
	{
	public:
		std::string Name;
		CML::Matrix4x4 Transformation;
		std::shared_ptr<Node> Parent;
		std::vector<std::shared_ptr<Node>> Childern;
		std::vector<int> meshes;
		Node();
	};
}

#endif //__Nodes__