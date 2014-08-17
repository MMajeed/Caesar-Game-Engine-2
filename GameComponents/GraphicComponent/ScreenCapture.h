#ifndef __ScreenCapture__
#define __ScreenCapture__

#include "Linker.h"
#include "GraphicObjectEntity.h"
#include <string>
#include <unordered_map>
#include <vector>
#include <memory>

class GraphicComponentDLL_API ScreenCapture
{
public:
	ScreenCapture() : Priority(0){}
	virtual void Init() = 0;
	virtual void Snap(const std::unordered_map<std::string, std::shared_ptr<GraphicObjectEntity>>& list) = 0;
	virtual std::shared_ptr<ScreenCapture> clone() const = 0;
	virtual ~ScreenCapture(){}

	unsigned int Priority;
	std::vector<std::string> TextureID;
};


#endif //__ScreenCapture__
