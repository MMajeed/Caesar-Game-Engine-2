#include "EntityList.h"

#include <mutex>

namespace ObjectEntities
{
	std::unordered_map<std::string, std::shared_ptr<ObjectEntity>> objectEntitiesList;
	std::mutex objectEntitiesMutex;

	std::unordered_map<std::string, std::weak_ptr<ObjectEntity>> GetAll()
	{
		std::lock_guard<std::mutex> lock(objectEntitiesMutex);

		std::unordered_map<std::string, std::weak_ptr<ObjectEntity>> returnValue;
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
	bool Find(const std::string& ID, std::shared_ptr<ObjectEntity>& returnObj)
	{
		std::lock_guard<std::mutex> lock(objectEntitiesMutex);
		auto objEntitiesIter = objectEntitiesList.find(ID);
		if(objEntitiesIter == objectEntitiesList.end())	{ return false; }
		returnObj = objEntitiesIter->second;
		return true;
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
	std::unordered_map<std::string, std::shared_ptr<CameraEntity>> cameraEntitiesList;
	std::mutex cameraEntitiesMutex;

	std::unordered_map<std::string, std::weak_ptr<CameraEntity>> GetAll()
	{
		std::lock_guard<std::mutex> lock(cameraEntitiesMutex);

		std::unordered_map<std::string, std::weak_ptr<CameraEntity>> returnValue;
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

namespace DrawSettingsEntities
{
	std::unordered_map<std::string, std::shared_ptr<DrawSettingsEntity>> DrawSettingsEntitiesList;
	std::mutex DrawSettingsEntitiesMutex;

	std::unordered_map<std::string, std::weak_ptr<DrawSettingsEntity>> GetAll()
	{
		std::lock_guard<std::mutex> lock(DrawSettingsEntitiesMutex);

		std::unordered_map<std::string, std::weak_ptr<DrawSettingsEntity>> returnValue;
		returnValue.reserve(DrawSettingsEntitiesList.size());

		for(auto objEntitiesIter = DrawSettingsEntitiesList.cbegin();
			objEntitiesIter != DrawSettingsEntitiesList.cend();
			++objEntitiesIter)
		{
			returnValue[objEntitiesIter->first] = objEntitiesIter->second;
		}

		return returnValue;
	}
	void Add(std::shared_ptr<DrawSettingsEntity> objEntity)
	{
		std::lock_guard<std::mutex> lock(DrawSettingsEntitiesMutex);
		DrawSettingsEntitiesList[objEntity->GetID()] = objEntity;
	}
	bool Find(const std::string& ID, std::weak_ptr<DrawSettingsEntity>& returnObj)
	{
		std::lock_guard<std::mutex> lock(DrawSettingsEntitiesMutex);

		auto objEntitiesIter = DrawSettingsEntitiesList.find(ID);
		if(objEntitiesIter == DrawSettingsEntitiesList.end())
		{
			return false;
		}
		returnObj = objEntitiesIter->second;
		return true;
	}
	void Remove(const std::string& ID)
	{
		std::lock_guard<std::mutex> lock(DrawSettingsEntitiesMutex);

		DrawSettingsEntitiesList.erase(ID);
	}
}