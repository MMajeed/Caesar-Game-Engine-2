#include "EntityConfig.h"
#include <EntityManager.h>
#include <iostream>

namespace EntityConfig
{
	void SetEntity(SP_INFO info)
	{
		std::lock_guard<std::mutex> lock(EntityManager::GetInstance().infoMutex);
		EntityManager::GetInstance().entities[info->ID] = info;
	}
	SP_INFO GetEntity(std::string ID)
	{
		std::lock_guard<std::mutex> lock(EntityManager::GetInstance().infoMutex);

		SP_INFO returnValue;
		auto iter = EntityManager::GetInstance().entities.find(ID);
		if(iter != EntityManager::GetInstance().entities.end())
		{
			returnValue = iter->second->Clone();
		}
		return returnValue;
	}
	std::shared_ptr<Object> GetEntity(std::string ID, std::string keyID)
	{
		std::lock_guard<std::mutex> lock(EntityManager::GetInstance().infoMutex);
		std::shared_ptr<Object> returnValue;
		auto iter = EntityManager::GetInstance().entities.find(ID);
		if(iter != EntityManager::GetInstance().entities.end())
		{
			returnValue = iter->second->Get(keyID);
		}
		return returnValue;
	}
	void SetEntity(std::string ID, std::string keyID, std::shared_ptr<Object> obj)
	{
		std::lock_guard<std::mutex> lock(EntityManager::GetInstance().infoMutex);
		auto iter = EntityManager::GetInstance().entities.find(ID);
		if(iter != EntityManager::GetInstance().entities.end())
		{
			iter->second->Set(keyID, obj);
		}
	}
	std::hash_map<std::string, SP_INFO> GetAllEntity()
	{
		std::lock_guard<std::mutex> lock(EntityManager::GetInstance().infoMutex);

		std::hash_map<std::string, SP_INFO> returnValue;

		for(auto iter = EntityManager::GetInstance().entities.begin();
			iter != EntityManager::GetInstance().entities.end();
			++iter)
		{
			returnValue[iter->first] = iter->second->Clone();
		}

		return returnValue;
	}
};