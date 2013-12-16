#ifndef __EntityConfig__
#define __EntityConfig__

#include "Linker.h"
#include <INFO.h>
#include <hash_map>

namespace EntityConfig
{
	void SetEntity(SP_INFO info);
	void SetEntity(std::string ID, std::string keyID, std::shared_ptr<Object> obj);
	SP_INFO GetEntity(std::string ID);
	std::shared_ptr<Object> GetEntity(std::string ID, std::string keyID);
	std::hash_map<std::string, SP_INFO> GetAllEntity();
	void DeleteEntity(std::string ID);
};

#endif //__EntityConfig__
