#include "GetObjectINFO.h"
#include <thread>

#include <InfoManager.h>
#include <Keys.h>

std::hash_map<std::string, SP_INFO> GetObjectINFO::GetAllObjects()
{
	std::hash_map<std::string, SP_INFO> returnValue;

	std::lock_guard<std::mutex> lock(InfoManager::GetInstance().mutex);
	
	for(auto iter = InfoManager::GetInstance().objects.begin();
		iter != InfoManager::GetInstance().objects.end();
		++iter)
	{
		returnValue[iter->first] = iter->second->Clone();
	}

	return returnValue;
}
SP_INFO GetObjectINFO::GetObject(std::string id)
{
	SP_INFO returnValue;

	std::lock_guard<std::mutex> lock(InfoManager::GetInstance().mutex);

	auto iter = InfoManager::GetInstance().objects.find(id);
	if(iter != InfoManager::GetInstance().objects.end())
	{
		returnValue = iter->second->Clone();
	}

	return returnValue;
}