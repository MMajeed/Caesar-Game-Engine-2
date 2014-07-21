#ifndef __CBWeakVariables__
#define __CBWeakVariables__

#include "Linker.h"
#include <ObjectEntity.h>
#include "CBufferSetup.h"
#include "SceneInfo.h"
#include <hash_map>
#include <functional>
#include <vector>
#include <string>
#include <memory>

class GraphicComponentDLL_API CBWeakVariables : public CBufferVariables
{
protected:
	CBWeakVariables(std::vector<char>& bytes, const unsigned int StartOffset);
public:
	virtual void Update(std::shared_ptr<ObjectEntity> object, const SceneInfo& si);
	
	virtual ~CBWeakVariables(){}
};



#endif //__CBWeakVariables__