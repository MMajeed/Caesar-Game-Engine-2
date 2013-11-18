#include "INFO.h"
#include "Keys.h"
#include <GenerateGUID.h>

INFO::INFO()
{
	this->ID = CHL::GenerateGUID();
}

std::shared_ptr<Object> INFO::Get(const std::string& ID)
{
	std::shared_ptr<Object> returnValue;

	if(ID == Keys::ID){ returnValue = GenericObj<std::string>::CreateNew(this->ID); }

	return returnValue;
}
void INFO::Set(const std::string& ID, std::shared_ptr<Object> obj)
{

}