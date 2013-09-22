#include "ObjectManagerOutput.h"

#include "ObjectManager.h"

CHL::VectorQueryable<CHL::MapQueryable<std::string, std::string>> ObjectManagerOutput::GetAllObjects()
{
	boost::mutex::scoped_lock lock(ObjectManager::GetInstance().mutex);

	auto allObjects = ObjectManager::GetInstance().AllObjects();

	CHL::VectorQueryable<CHL::MapQueryable<std::string, std::string>> convertedVec;

	convertedVec.reserve(allObjects.size());

	for(auto iter = allObjects.begin();
		iter != allObjects.end();
		++iter)
	{
		convertedVec.push_back(**iter);
	}

	return convertedVec;
}