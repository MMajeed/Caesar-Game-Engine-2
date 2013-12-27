#ifndef __CubeScreenCaptureConfig__
#define __CubeScreenCaptureConfig__

#include "Linker.h"

#include <Message.h>
#include <string>
#include <Matrix.h>
#include <Vector.h>

namespace CubeScreenCaptureConfig
{
	void Create(unsigned int width,
				unsigned int height,
				const std::string& cameraID,
				std::string& ID,
				std::string& textureID);
	void SetCameraID(const std::string& id, const std::string& cameraID);
	void Release(std::string ID);
};

#endif //__CubeScreenCaptureConfig__
