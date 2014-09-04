#ifndef __BasicScreenCaptureConfig__
#define __BasicScreenCaptureConfig__

#include "Linker.h"

#include <Message.h>
#include <string>
#include <vector>

namespace BasicScreenCaptureConfig
{
	GraphicCommunicatorDLL_API 
		void Create(unsigned int width,
					unsigned int height,
					unsigned int priority,
					const std::string& cameraID,
					unsigned int numberOfTargets,
					std::string& ID,
					std::vector<std::string>& textureID);
	GraphicCommunicatorDLL_API void SetCameraID(const std::string& id, const std::string& cameraid);
	GraphicCommunicatorDLL_API void SetPriority(const std::string& id, int p);
	GraphicCommunicatorDLL_API void Release(std::string ID);
};

#endif //__BasicScreenCaptureConfig__
