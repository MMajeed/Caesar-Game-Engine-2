#ifndef __EntityConfig__
#define __EntityConfig__

#include "Linker.h"
#include <INFO.h>
#include <hash_map>

namespace EntityConfig
{
	EntityCommunicatorDLL_API void SetEntity(SP_INFO info);
	EntityCommunicatorDLL_API void SetEntity(std::string ID, std::string keyID, std::shared_ptr<Object> obj);
	EntityCommunicatorDLL_API SP_INFO GetEntity(std::string ID);
	EntityCommunicatorDLL_API std::shared_ptr<Object> GetEntity(std::string ID, std::string keyID);
	EntityCommunicatorDLL_API std::hash_map<std::string, SP_INFO> GetAllEntity();
	EntityCommunicatorDLL_API void DeleteEntity(std::string ID);
};

#endif //__EntityConfig__
