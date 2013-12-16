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
				const CHL::Matrix4x4& cameraMatrix,
				const CHL::Matrix4x4& prespectiveMatrix,
				std::string& ID,
				std::string& textureID);
	void SetCamera(const std::string& id, const CHL::Matrix4x4& camera);
	void SetPrespective(const std::string& id, const CHL::Matrix4x4& prespective);
	void Release(std::string ID);
};

#endif //__BasicScreenCaptureConfig__
