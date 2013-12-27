#ifndef __BasicScreenCaptureConfig__
#define __BasicScreenCaptureConfig__

#include "Linker.h"

#include <Message.h>
#include <string>
#include <Matrix.h>
#include <Vector.h>

namespace BasicScreenCaptureConfig
{
	void Create(unsigned int width,
				unsigned int height,
				const std::string& cameraID,
				std::string& ID,
				std::string& textureID);
	void SetCameraID(const std::string& id, const std::string& cameraid);
	void Release(std::string ID);
};

#endif //__BasicScreenCaptureConfig__
