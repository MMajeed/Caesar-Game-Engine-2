#ifndef __BasicScreenCaptureFactory__
#define __BasicScreenCaptureFactory__

#include "Linker.h"
#include <iBasicScreenCaptureFactory.h>

class GraphicComponentDLL_API BasicScreenCaptureFactory : public iBasicScreenCaptureFactory
{
public:
	virtual void Create(unsigned int width,
						unsigned int height,
						unsigned int priority,
						const std::string& cameraID,
						const std::string& drawSettingsID,
						unsigned int numberOfTargets,
						std::string& ID,
						std::vector<std::string>& textureID);
	virtual void SetCameraID(const std::string& id, const std::string& cameraid);
	virtual void SetDrawSettingsID(const std::string& id, const std::string& dsID);
	virtual void SetPriority(const std::string& id, int p);
	virtual void Release(std::string ID);
};

#endif //__BasicScreenCaptureFactory__