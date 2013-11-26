#ifndef __EntityManager__
#define __EntityManager__

#include "Linker.h"
#include <Interface.h>
#include <Singleton.h>
#include <INFO.h>
#include <hash_map>
#include <mutex>

class EntityManager : public CHL::Singleton<EntityManager>
{
protected:
	EntityManager();
public:
	std::hash_map<std::string, SP_INFO> entities;

	struct
	{
		std::string CameraID;
		std::string PrespectiveID;
		std::string WindowINFOID;
	}ImportantKeys;

	std::mutex infoMutex;

	friend CHL::Singleton<EntityManager>;
};

#endif //__EntityManager__