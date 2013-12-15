#ifndef __CubeScreenCaptureConfig__
#define __CubeScreenCaptureConfig__

#include "Linker.h"

#include <Message.h>
#include <string>
#include <Matrix.h>
#include <Vector.h>

namespace CubeScreenCaptureConfig
{
	class AddCubeScreenCapture : public Message
	{
	public:
		AddCubeScreenCapture(unsigned int width, unsigned int height, const CHL::Vec4& eye);

		Message::Status Work();

		CHL::Vec4 eye;
		std::string newTextureID;
		std::string ID;
		unsigned int width;
		unsigned int height;
	};

	class ChangeEye : public Message
	{
	public:
		ChangeEye(const std::string& id, const CHL::Vec4& eye);

		Message::Status Work();
		std::string ID;
		CHL::Vec4 eye;
	};
};

#endif //__CubeScreenCaptureConfig__
