#include "ObjectManagerOutput.h"

#include <ObjectManager.h>

CHL::VectorQ<CHL::MapQ<std::string, std::string>> ObjectManagerOutput::GetAllObjects()
{
	boost::mutex::scoped_lock lock(ObjectManager::GetInstance().mutex);

	auto allObjects = ObjectManager::GetInstance().AllObjects();

	CHL::VectorQ<CHL::MapQ<std::string, std::string>> convertedVec;

	convertedVec.reserve(allObjects.size());

	for(auto iter = allObjects.begin();
		iter != allObjects.end();
		++iter)
	{
		convertedVec.push_back(*iter);
	}

	return convertedVec;
}

CHL::MapQ<std::string, std::string> ObjectManagerOutput::GetObject(std::string id)
{
	boost::mutex::scoped_lock lock(ObjectManager::GetInstance().mutex);

	return ObjectManager::GetInstance().GetObjectInfo(id).info;
}