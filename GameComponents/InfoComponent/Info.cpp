#include "Info.h"

#include <Keys.h>

#include <Converter.h>
#include <boost/uuid/uuid_generators.hpp> // generators
#include <boost/uuid/uuid_io.hpp>         // streaming operators etc.

Info::Info()
{
	std::shared_ptr<GenericObject<std::string>> obj(new GenericObject<std::string>(CHL::ToString(boost::uuids::random_generator()())));
	this->Store(Keys::ID, obj);
}
Info::Info(const CHL::MapQ<std::string, std::shared_ptr<Object>>& input)
	: info(input)
{
	std::shared_ptr<GenericObject<std::string>> obj(new GenericObject<std::string>(CHL::ToString(boost::uuids::random_generator()())));
	this->Store(Keys::ID, obj);
}

void Info::Store(std::string key, std::shared_ptr<Object> value)
{
	this->info[key] = value;
}

bool Info::Retrieve(std::string key, std::shared_ptr<Object>& value) const
{
	auto valueIterator = this->info.find(key);

	if(valueIterator != this->info.cend())
	{
		value = valueIterator->second->Clone();
		return true;
	}
	return false;
}

bool Info::Exist(std::string key) const
{
	auto valueIterator = this->info.find(key);

	return (valueIterator != this->info.cend());
}

std::string Info::ID() const
{
	std::shared_ptr<Object> idObj;
	this->Retrieve(Keys::ID, idObj);
	return GenericObject<std::string>::GetValue(idObj);
}