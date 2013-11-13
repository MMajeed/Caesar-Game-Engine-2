#ifndef __AddBasicScreenCaptureMessage__
#define __AddBasicScreenCaptureMessage__

#include "Linker.h"

#include <Message.h>
#include <string>

namespace BasicScreenCaptureConfig
{
	class AddBasicScreenCaptureMessage : public Message
	{
	public:
		AddBasicScreenCaptureMessage(unsigned int widthInput, unsigned int heightInput);

		virtual Message::Status BasicScreenCaptureConfig::AddBasicScreenCaptureMessage::Work();

		std::string ID;
		unsigned int width;
		unsigned int height;
	};

	class SnapPictureMessage : public Message
	{
	public:
		SnapPictureMessage(std::string ID, std::string cameraID, std::string prespectiveID);

		Message::Status SnapPictureMessage::Work();

		std::string ID;
		std::string cameraID;
		std::string prespectiveID;
		std::string newTextureID;
	};
};


#endif //__AddBasicScreenCaptureMessage__