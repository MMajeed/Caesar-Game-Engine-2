#ifndef __ScreenShotFactory__
#define __ScreenShotFactory__

#include "Linker.h"

#include <iScreenShotFactory.h>

class GraphicComponentDLL_API ScreenShotFactory : public iScreenShotFactory
{
public:
	virtual std::vector<std::string> Basic(unsigned int width,
										   unsigned int height,
										   unsigned int numberOfTargets,
										   const std::string& cameraID,
										   const std::string& drawSettingsID);
	virtual std::string Depth(unsigned int width,
							  unsigned int height,
							  const std::string& cameraID,
							  const std::string& drawSettingsID);
	virtual std::string Cube(unsigned int width,
							 unsigned int height,
							 const std::string& cameraID,
							 const std::string& drawSettingsID);
};

#endif //__ScreenShotFactory__