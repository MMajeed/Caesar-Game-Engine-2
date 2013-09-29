#include "ObjectManagerOutput.h"

#include <InfoManager.h>

CHL::VectorQ<CHL::MapQ<std::string, std::shared_ptr<Object>>> ObjectManagerOutput::GetAllObjects()
{
	boost::mutex::scoped_lock lock(InfoManager::GetInstance().mutex);

	auto allObjects = InfoManager::GetInstance().AllObjects();

	CHL::VectorQ<CHL::MapQ<std::string, std::shared_ptr<Object>>> convertedVec;

	convertedVec.reserve(allObjects.size());

	for(auto objIter = allObjects.begin();
		objIter != allObjects.end();
		++objIter)
	{
		CHL::MapQ<std::string, std::shared_ptr<Object>> newInfo;
		newInfo.reserve( objIter->second.info.size());
		for(auto infoIter = objIter->second.info.begin();
			infoIter != objIter->second.info.end();
			++infoIter)
		{
			newInfo[infoIter->first] = infoIter->second->Clone();
		}
		convertedVec.push_back(newInfo);
	}

	return convertedVec;
}

CHL::MapQ<std::string, std::shared_ptr<Object>> ObjectManagerOutput::GetObject(std::string id)
{
	boost::mutex::scoped_lock lock(InfoManager::GetInstance().mutex);

	CHL::MapQ<std::string, std::shared_ptr<Object>> returnValue;

	auto objIter = InfoManager::GetInstance().GetObjectInfo(id);
	returnValue.reserve( objIter.info.size() );

	for(auto infoIter = objIter.info.begin();
		infoIter != objIter.info.end();
		++infoIter)
	{
		returnValue[infoIter->first] = infoIter->second->Clone();
	}

	return returnValue;
}