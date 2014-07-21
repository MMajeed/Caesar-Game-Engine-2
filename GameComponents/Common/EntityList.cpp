#include "EntityList.h"

#include <mutex>

namespace ObjectEntities
{
	std::hash_map<std::string, std::shared_ptr<ObjectEntity>> objectEntitiesList;
	std::mutex objectEntitiesMutex;

	std::hash_map<std::string, std::weak_ptr<ObjectEntity>> GetAll()
	{
		std::lock_guard<std::mutex> lock(objectEntitiesMutex);

		std::hash_map<std::string, std::weak_ptr<ObjectEntity>> returnValue;
		returnValue.reserve(objectEntitiesList.size());

		for(auto objEntitiesIter = objectEntitiesList.cbegin();
			objEntitiesIter != objectEntitiesList.cend();
			++objEntitiesIter)
		{
			returnValue[objEntitiesIter->first] = objEntitiesIter->second;
		}

		return returnValue;
	}
	void Add(std::shared_ptr<ObjectEntity> objEntity)
	{
		std::lock_guard<std::mutex> lock(objectEntitiesMutex);
		objectEntitiesList[objEntity->GetID()] = objEntity;
	}
	bool Find(const std::string& ID, std::weak_ptr<ObjectEntity>& returnObj)
	{
		std::lock_guard<std::mutex> lock(objectEntitiesMutex);
		auto objEntitiesIter = objectEntitiesList.find(ID);
		if(objEntitiesIter == objectEntitiesList.end())
		{
			return false;
		}
		returnObj = objEntitiesIter->second;
		return true;
	}
	void Remove(const std::string& ID)
	{
		std::lock_guard<std::mutex> lock(objectEntitiesMutex);
		objectEntitiesList.erase(ID);
	}
}

namespace CameraEntities
{
	std::hash_map<std::string, std::shared_ptr<CameraEntity>> cameraEntitiesList;
	std::mutex cameraEntitiesMutex;

	std::hash_map<std::string, std::weak_ptr<CameraEntity>> GetAll()
	{
		std::lock_guard<std::mutex> lock(cameraEntitiesMutex);

		std::hash_map<std::string, std::weak_ptr<CameraEntity>> returnValue;
		returnValue.reserve(cameraEntitiesList.size());

		for(auto objEntitiesIter = cameraEntitiesList.cbegin();
			objEntitiesIter != cameraEntitiesList.cend();
			++objEntitiesIter)
		{
			returnValue[objEntitiesIter->first] = objEntitiesIter->second;
		}

		return returnValue;
	}
	void Add(std::shared_ptr<CameraEntity> objEntity)
	{
		std::lock_guard<std::mutex> lock(cameraEntitiesMutex);
		cameraEntitiesList[objEntity->GetID()] = objEntity;
	}
	bool Find(const std::string& ID, std::weak_ptr<CameraEntity>& returnObj)
	{
		std::lock_guard<std::mutex> lock(cameraEntitiesMutex);

		auto objEntitiesIter = cameraEntitiesList.find(ID);
		if(objEntitiesIter == cameraEntitiesList.end())
		{
			return false;
		}
		returnObj = objEntitiesIter->second;
		return true;
	}
	void Remove(const std::string& ID)
	{
		std::lock_guard<std::mutex> lock(cameraEntitiesMutex);

		cameraEntitiesList.erase(ID);
	}
}