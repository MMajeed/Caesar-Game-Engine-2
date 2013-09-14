#include "ObjectManagerOutput.h"

#include "ObjectManager.h"

CHL::VectorQueryable<CHL::MapQueryable<std::string, std::string>> ObjectManagerOutput::GetAllObjects()
{
	auto allObjects = ObjectManager().GetInstance().AllObjects();

	CHL::VectorQueryable<CHL::MapQueryable<std::string, std::string>> convertedVec;
	

	return convertedVec;
}