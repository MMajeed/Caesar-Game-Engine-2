#ifndef __TakeScreenShot__
#define __TakeScreenShot__

#include "Linker.h"

#include <Message.h>
#include <string>
#include <Matrix.h>
#include <Vector.h>

namespace ScreenShotConfig
{
	std::string Basic(unsigned int width,
					  unsigned int height,
					  const CHL::Matrix4x4& cameraMatrix,
					  const CHL::Matrix4x4& prespectiveMatrix);
	std::string Depth(unsigned int width,
					  unsigned int height,
					  const CHL::Matrix4x4& cameraMatrix,
					  const CHL::Matrix4x4& prespectiveMatrix); 
	std::string Cube(unsigned int width, 
					 unsigned int height, 
					 const CHL::Vec4& eye);
}


#endif //__TakeScreenShot__