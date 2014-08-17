#ifndef __CBWeakVariables__
#define __CBWeakVariables__

#include "Linker.h"
#include "GraphicCameraEntity.h"
#include "GraphicObjectEntity.h"
#include "CBSetup.h"
#include <unordered_map>
#include <functional>
#include <vector>
#include <string>
#include <memory>

class GraphicComponentDLL_API CBWeakVariables : public CBVariables
{
protected:
	CBWeakVariables(std::vector<char>& bytes, 
						  const unsigned int StartOffset, 
						  const unsigned int sizeOfValue, 
						  const std::string Name);
public:
	virtual void Update(std::shared_ptr<GraphicCameraEntity> camera, std::shared_ptr<GraphicObjectEntity> object);
	static std::shared_ptr<CBWeakVariables> Spawn(std::vector<char>& bytes,
														const unsigned int StartOffset,
														const unsigned int sizeOfValue,
														const std::string Name);

	const std::string Name;
	const unsigned int sizeOfValue;
};

#endif //__CBWeakVariables__
