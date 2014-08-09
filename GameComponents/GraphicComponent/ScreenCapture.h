#ifndef __ScreenCapture__
#define __ScreenCapture__

#include "Linker.h"
#include "GraphicObjectEntity.h"
#include <string>
#include <Entity.h>
#include <hash_map>
#include <memory>

class GraphicComponentDLL_API ScreenCapture
{
public:
	virtual void Init()                                                 = 0;
	
	virtual void Snap(const std::hash_map<std::string, std::shared_ptr<GraphicObjectEntity>>& list)     = 0;
	virtual std::shared_ptr<ScreenCapture> clone() const                = 0;
	virtual ~ScreenCapture(){}

	std::string TextureID;
};


#endif //__ScreenCapture__
