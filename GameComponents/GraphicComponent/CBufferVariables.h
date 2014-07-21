#ifndef __CBufferVariables__
#define __CBufferVariables__

#include "Linker.h"
#include <ObjectEntity.h>
#include "SceneInfo.h"
#include <vector>

class GraphicComponentDLL_API CBufferVariables
{
protected:
	CBufferVariables(std::vector<char>& bytes, const unsigned int StartOffset);
public:
	virtual void Update(std::shared_ptr<ObjectEntity> object, const SceneInfo& si) = 0;

	std::vector<char>& bytes;
	const unsigned int StartOffset;

	virtual ~CBufferVariables(){}
};
#endif //__CBufferVariables__