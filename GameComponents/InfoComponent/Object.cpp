#include "Object.h"

#include <Keys.h>

#include <Converter.h>
#include <boost/uuid/uuid_generators.hpp> // generators
#include <boost/uuid/uuid_io.hpp>         // streaming operators etc.
#include <boost/numeric/ublas/io.hpp>
#include <sstream>

Object::Object()
{
	this->Store(Keys::ID, CHL::ToString(boost::uuids::random_generator()()));
}
Object::Object(const CHL::MapQ<std::string, std::string>& input)
{
	this->info = input;
	this->Store(Keys::ID, CHL::ToString(boost::uuids::random_generator()()));
}

void Object::Store(std::string key, const std::string& value)
{
	this->info[key] = value;
}

bool Object::Retrieve(std::string key, std::string& value) const
{
	auto valueIterator = this->info.find(key);

	if(valueIterator != this->info.cend())
	{
		value = valueIterator->second;
		return true;
	}
	return false;
}

bool Object::Exist(std::string key) const
{
	auto valueIterator = this->info.find(key);

	return (valueIterator != this->info.cend());
}

std::string Object::ID()
{
	std::string id;
	this->Retrieve(Keys::ID, id);
	return id;
}

Object::operator CHL::MapQ<std::string, std::string>()
{
	return this->info;
}