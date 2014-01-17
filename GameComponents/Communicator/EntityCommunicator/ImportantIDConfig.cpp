#include "ImportantIDConfig.h"
#include <EntityManager.h>

namespace ImportantIDConfig
{
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
}