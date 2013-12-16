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
				const CHL::Vec4& eye,
				std::string& ID,
				std::string& textureID);
	void SetEye(const std::string& id, const CHL::Vec4& eye);
	void Release(std::string ID);
};

#endif //__CubeScreenCaptureConfig__
