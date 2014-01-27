#ifndef __3DLoader__
#define __3DLoader__

#include "Linker.h"
#include "Animation.h"
#include "Model.h"
#include "Node.h"
#include <memory>

namespace CHL
{
	void Load3DFile(std::string fileName, 
					std::vector<std::shared_ptr<CHL::Model>>& modelVec, 
					std::vector<std::shared_ptr<CHL::Animation>>& animVec,
					std::shared_ptr<CHL::Node>& rootNode);
};

#endif //__3DLoader__