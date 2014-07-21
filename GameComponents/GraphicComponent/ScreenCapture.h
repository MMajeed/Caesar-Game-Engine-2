#ifndef __ScreenCapture__
#define __ScreenCapture__

#include "Linker.h"
#include <string>
#include <Entity.h>
#include <hash_map>
#include <memory>

class GraphicComponentDLL_API ScreenCapture
{
public:
	virtual void Init()                                                 = 0;
	virtual void Destory()                                              = 0;
	virtual void Update(double realTime, double deltaTime)              = 0;
	virtual void Snap(std::hash_map<std::string, SP_INFO>& objects)     = 0;
	virtual std::shared_ptr<ScreenCapture> clone() const                = 0;
	virtual ~ScreenCapture(){}

	std::string TextureID;
};


#endif //__ScreenCapture__
