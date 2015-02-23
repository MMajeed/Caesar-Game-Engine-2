#ifndef __iDepthScreenCaptureFactory__
#define __iDepthScreenCaptureFactory__

#include "Linker.h"
#include <memory>
#include <string>
#include <vector>

class CommonDLL_API iDepthScreenCaptureFactory
{
public:
	virtual void Create(unsigned int width,
						unsigned int height,
						unsigned int priority,
						const std::string& cameraID,
						const std::string& drawSettingsID,
						std::string& ID,
						std::string& textureID) = 0;
	virtual void SetCameraID(const std::string& id, const std::string& cameraid) = 0;
	virtual void SetDrawSettingsID(const std::string& id, const std::string& dsID) = 0;
	virtual void SetPriority(const std::string& id, int p) = 0;
	virtual void Release(std::string ID) = 0;
};

#endif //__iDepthScreenCaptureFactory__