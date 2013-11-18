#include "PrespectiveINFO.h"
#include "Keys.h"

std::shared_ptr<Object> PrespectiveINFO::Get(const std::string& ID)
{
	std::shared_ptr<Object> returnValue;

	returnValue = INFO::Get(ID);

	return returnValue;
}


void PrespectiveINFO::Set(const std::string& ID, std::shared_ptr<Object> obj)
{
	INFO::Set(ID, obj);
}

std::shared_ptr<INFO> PrespectiveINFO::Clone()
{
	return std::make_shared<PrespectiveINFO>(*this);
}