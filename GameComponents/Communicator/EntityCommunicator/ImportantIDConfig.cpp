#include "ImportantIDConfig.h"
#include <EntityManager.h>

namespace CameraID
{
	void Set(std::string newID)
	{
		std::lock_guard<std::mutex> lock(EntityManager::GetInstance().infoMutex);
		EntityManager::GetInstance().ImportantKeys.CameraID = newID;
	}
	std::string Get()
	{
		std::lock_guard<std::mutex> lock(EntityManager::GetInstance().infoMutex);
		return EntityManager::GetInstance().ImportantKeys.CameraID;
	}
}

namespace PrespectiveID
{
	void Set(std::string newID)
	{
		std::lock_guard<std::mutex> lock(EntityManager::GetInstance().infoMutex);
		EntityManager::GetInstance().ImportantKeys.PrespectiveID = newID;
	}
	std::string Get()
	{
		std::lock_guard<std::mutex> lock(EntityManager::GetInstance().infoMutex);
		return EntityManager::GetInstance().ImportantKeys.PrespectiveID;
	}
}

namespace WindowINFOID
{
	void Set(std::string newID)
	{
		std::lock_guard<std::mutex> lock(EntityManager::GetInstance().infoMutex);
		EntityManager::GetInstance().ImportantKeys.WindowINFOID = newID;
	}
	std::string Get()
	{
		std::lock_guard<std::mutex> lock(EntityManager::GetInstance().infoMutex);
		return EntityManager::GetInstance().ImportantKeys.WindowINFOID;
	}
}
