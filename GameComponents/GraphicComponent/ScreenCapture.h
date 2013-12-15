#ifndef __ScreenCapture__
#define __ScreenCapture__

#include <string>
#include <INFO.h>
#include <hash_map>
#include <memory>

class ScreenCapture
{
public:
	ScreenCapture(const std::string& inputID) : ID(inputID){}

	virtual void Init()                                         = 0;
	virtual void Destory()                                      = 0;
	virtual void Update(double realTime, double deltaTime)      = 0;
	virtual void Snap(std::hash_map<std::string, SP_INFO>& objects)     = 0;
	virtual std::shared_ptr<ScreenCapture> clone() const = 0;
	virtual ~ScreenCapture(){}

	const std::string ID;
	std::string TextureID;
};


#endif //__ScreenCapture__
