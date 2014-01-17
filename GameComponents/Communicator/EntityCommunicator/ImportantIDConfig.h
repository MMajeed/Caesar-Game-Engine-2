#ifndef __ImportantIDConfig__
#define __ImportantIDConfig__

#include "Linker.h"
#include <Message.h>
#include <string>

namespace ImportantIDConfig
{
	namespace CameraID
	{
		void Set(std::string newID);
		std::string Get();
	}
}


#endif //__ImportantIDConfig__