#ifndef __iScreenShotFactory__
#define __iScreenShotFactory__

#include "Linker.h"
#include <Model.h>
#include <memory>
#include <string>

class CommonDLL_API iScreenShotFactory
{
public:
	virtual std::vector<std::string> Basic(unsigned int width,
										   unsigned int height,
										   unsigned int numberOfTargets,
										   const std::string& cameraID,
										   const std::string& drawSettingsID) = 0;
	virtual std::string Depth(unsigned int width,
							  unsigned int height,
							  const std::string& cameraID,
							  const std::string& drawSettingsID) = 0;
	virtual std::string Cube(unsigned int width,
							 unsigned int height,
							 const std::string& cameraID,
							 const std::string& drawSettingsID) = 0;
};

#endif //__iScreenShotFactory__