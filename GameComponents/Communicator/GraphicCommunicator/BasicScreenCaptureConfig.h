#ifndef __BasicScreenCaptureConfig__
#define __BasicScreenCaptureConfig__

#include "Linker.h"

#include <Message.h>
#include <string>
#include <Vector.h>
#include <Vector.h>

namespace BasicScreenCaptureConfig
{
	GraphicCommunicatorDLL_API 
		void Create(unsigned int width,
					unsigned int height,
					const std::string& cameraID,
					std::string& ID,
					std::string& textureID);
	GraphicCommunicatorDLL_API void SetCameraID(const std::string& id, const std::string& cameraid);
	GraphicCommunicatorDLL_API void Release(std::string ID);
};

#endif //__BasicScreenCaptureConfig__
