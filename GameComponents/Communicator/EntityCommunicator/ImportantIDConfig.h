#ifndef __ImportantIDConfig__
#define __ImportantIDConfig__

#include "Linker.h"
#include <Message.h>
#include <string>

namespace ImportantIDConfig
{
	namespace CameraID
	{
		EntityCommunicatorDLL_API void Set(std::string newID);
		EntityCommunicatorDLL_API std::string Get();
	}
}


#endif //__ImportantIDConfig__