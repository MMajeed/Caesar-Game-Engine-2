#ifndef __TakeScreenShot__
#define __TakeScreenShot__

#include "Linker.h"

#include <Message.h>
#include <string>
#include <Vector.h>
#include <Vector.h>

namespace ScreenShotConfig
{
	std::string Basic(unsigned int width,
					  unsigned int height,
					  const std::string& cameraID);
	std::string Depth(unsigned int width,
					  unsigned int height,
					  const std::string& cameraID);
	std::string Cube(unsigned int width, 
					 unsigned int height,
					 const std::string& cameraID);
}


#endif //__TakeScreenShot__