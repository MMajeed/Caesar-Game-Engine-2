#ifndef __EntityConfig__
#define __EntityConfig__

#include "Linker.h"
#include <INFO.h>
#include <hash_map>

namespace EntityConfig
{
	void SetEntity(SP_INFO info);
	SP_INFO GetEntity(std::string ID);
	std::shared_ptr<Object> GetEntity(std::string ID, std::string keyID);
	void SetEntity(std::string ID, std::string keyID, std::shared_ptr<Object> obj);
	std::hash_map<std::string, SP_INFO> GetAllEntity();
};

#endif //__EntityConfig__
