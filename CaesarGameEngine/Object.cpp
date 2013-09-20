#include "Object.h"

#include "Keys.h"

#include <Converter.h>
#include <boost/uuid/uuid_generators.hpp> // generators
#include <boost/uuid/uuid_io.hpp>         // streaming operators etc.
#include <boost/numeric/ublas/io.hpp>
#include <sstream>

Object::Object()
{
	this->Store(Keys::ID, CHL::ToString(boost::uuids::random_generator()()));
}
Object::Object(CHL::MapQueryable<std::string, std::string> input)
{
	this->Store(Keys::ID, CHL::ToString(boost::uuids::random_generator()()));
	this->info = input;
}

void Object::Store(std::string key, const std::string& value)
{
	this->info[key] = value;
}
void Object::Store(std::string key, const int value)
{
   this->info[key] = CHL::ToString(value);
}
void Object::Store(std::string key, const double value)
{
	this->info[key] = CHL::ToString(value);
}
void Object::Store(std::string key, const boost::numeric::ublas::vector<double>& value )
{
	this->info[key] = CHL::ToString(value);
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
bool Object::Retrieve(std::string key, int& value) const
{
	auto valueIterator = this->info.find(key);

	if(valueIterator != this->info.cend())
	{
		value = CHL::ToInt(valueIterator->second);
		return true;
	}
	return false;
}
bool Object::Retrieve(std::string key, double& value) const
{
	auto valueIterator = this->info.find(key);

	if(valueIterator != this->info.cend())
	{
		value = CHL::ToDouble(valueIterator->second);
		return true;
	}
	return false;
}
bool Object::Retrieve(std::string key, boost::numeric::ublas::vector<double>& value) const
{
	auto valueIterator = this->info.find(key);

	if(valueIterator != this->info.cend())
	{
		std::stringstream ss;
		ss << valueIterator->second;
		ss >> value;

		return true;
	}
	return false;
}

bool Object::Exist(std::string key) const
{
	auto valueIterator = this->info.find(key);

	return (valueIterator != this->info.cend());
}

Object::operator CHL::MapQueryable<std::string, std::string>()
{
	return this->info;
}