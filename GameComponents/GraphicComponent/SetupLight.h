#ifndef __SetupLight__
#define __SetupLight__

#include <hash_map>
#include <string>
#include <INFO.h>

namespace Light
{
	void SetupLight(std::hash_map<std::string, SP_INFO>& objects);
}

#endif //__SetupLight__