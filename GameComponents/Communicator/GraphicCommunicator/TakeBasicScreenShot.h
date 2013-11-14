#ifndef __TakeBasicScreenShot__
#define __TakeBasicScreenShot__

#include "Linker.h"

#include <Message.h>
#include <string>

class TakeBasicScreenShot : public Message
{
public:
	TakeBasicScreenShot(unsigned int width, unsigned int height, std::string cameraID, std::string prespectiveID);

	Message::Status Work();

	std::string cameraID;
	std::string prespectiveID;
	std::string newTextureID;
	unsigned int width;
	unsigned int height;
};


#endif //__TakeBasicScreenShot__