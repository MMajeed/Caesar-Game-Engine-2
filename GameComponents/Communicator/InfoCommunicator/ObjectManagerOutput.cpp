#include "ObjectManagerOutput.h"
#include <thread>

#include <InfoManager.h>
#include <Keys.h>

void FuncInsert(CHL::MapQ<std::string, Info>::const_iterator startIter,
				CHL::MapQ<std::string, Info>::const_iterator endIter,
					   std::size_t start,
					   CHL::VectorQ<CHL::MapQ<std::string, std::shared_ptr<Object>>>* convertedVec)
{
	int i = start;
	for(auto objIter = startIter;
		objIter != endIter;
		++objIter)
	{
		CHL::MapQ<std::string, std::shared_ptr<Object>> newInfo;
		newInfo.reserve( objIter->second.info.size());
		for(auto infoIter = objIter->second.info.cbegin();
			infoIter != objIter->second.info.cend();
			++infoIter)
		{
			newInfo[infoIter->first] = infoIter->second->Clone();
		}
		(*convertedVec)[i] = newInfo;
		++i;
	}
}

CHL::VectorQ<CHL::MapQ<std::string, std::shared_ptr<Object>>> ObjectManagerOutput::GetAllObjects()
{
	std::lock_guard<std::mutex> lock(InfoManager::GetInstance().mutex);
	
	const CHL::MapQ<std::string, Info>&  allObjects = InfoManager::GetInstance().AllObjects();

	CHL::VectorQ<CHL::MapQ<std::string, std::shared_ptr<Object>>> convertedVec;

	convertedVec.resize(allObjects.size());
		
	std::vector<std::shared_ptr<std::thread>> vThreads;

	static const int threadsPer = 2000;

	int numberOfThreads = ( (convertedVec.size() - 1) / threadsPer) + 1;
	std::vector<std::shared_ptr<std::thread>> threads;
	threads.reserve(numberOfThreads);

	CHL::MapQ<std::string, Info>::const_iterator startIter = allObjects.cbegin();
	CHL::MapQ<std::string, Info>::const_iterator endIter = allObjects.cbegin();
	std::size_t currentEndLoc = 0;

	for(int i = 0; i < numberOfThreads; ++i)
	{
		std::size_t start = 0;
		std::size_t end = 0;

		start = i * threadsPer;
		startIter = endIter;
				
		end = (i + 1) * threadsPer;
		if(end > convertedVec.size())
			end = convertedVec.size();
		std::size_t moveForward = end - currentEndLoc;
		std::advance(endIter, moveForward);
		currentEndLoc = end;

		std::shared_ptr<std::thread> thread = 
			std::shared_ptr<std::thread>(new std::thread(std::bind(&FuncInsert, startIter, endIter, start, &convertedVec)));
		
		threads.push_back(thread);
	}

	for(auto threadIter = threads.begin();
		threadIter != threads.end();
		++threadIter)
	{
		(*threadIter)->join();
	}

	/*int i = 0;
	for (auto iter = allObjects.begin();
		iter != allObjects.end();
		++iter, ++i)
	{
		std::string id1 = iter->first;
		std::string id2 = GenericObject<std::string>::GetValue(convertedVec[i][Keys::ID]);

		if (id1 != id2)
		{
			throw i;
		}
	}*/

	return convertedVec;
}

CHL::MapQ<std::string, std::shared_ptr<Object>> ObjectManagerOutput::GetObject(std::string id)
{
	std::lock_guard<std::mutex> lock(InfoManager::GetInstance().mutex);

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