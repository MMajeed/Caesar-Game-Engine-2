#ifndef __TakeScreenShot__
#define __TakeScreenShot__

#include "Linker.h"

#include <Message.h>
#include <string>
#include <vector>

namespace ScreenShotConfig
{
	GraphicCommunicatorDLL_API
		std::vector<std::string> Basic(unsigned int width,
									   unsigned int height,
									   unsigned int numberOfTargets,
									   const std::string& cameraID);
	GraphicCommunicatorDLL_API 
		std::string Depth(unsigned int width,
						  unsigned int height,
						  const std::string& cameraID);
	GraphicCommunicatorDLL_API 
		std::string Cube(unsigned int width,
						 unsigned int height,
						 const std::string& cameraID);
}


#endif //__TakeScreenShot__