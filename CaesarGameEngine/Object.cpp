#include "Object.h"

#include <Converter.h>
#include <boost/uuid/uuid_generators.hpp> // generators
#include <boost/uuid/uuid_io.hpp>         // streaming operators etc.
#include <boost/numeric/ublas/io.hpp>
#include <sstream>

Object::Object()
{
	this->Store(Object::Keys::ID, CHL::ToString(boost::uuids::random_generator()()));
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

bool Object::Retrieve(std::string key, std::string& value)
{
	std::hash_map<std::string, std::string>::iterator valueIterator;

	valueIterator = this->info.find(key);

	if(valueIterator != this->info.end())
	{
		value = valueIterator->second;
		return true;
	}
	return false;
}
bool Object::Retrieve(std::string key, int& value)
{
	std::hash_map<std::string, std::string>::iterator valueIterator;

	valueIterator = this->info.find(key);

	if(valueIterator != this->info.end())
	{
		value = CHL::ToInt(valueIterator->second);
		return true;
	}
	return false;
}
bool Object::Retrieve(std::string key, double& value)
{
	std::hash_map<std::string, std::string>::iterator valueIterator;

	valueIterator = this->info.find(key);

	if(valueIterator != this->info.end())
	{
		value = CHL::ToDouble(valueIterator->second);
		return true;
	}
	return false;
}
bool Object::Retrieve(std::string key, boost::numeric::ublas::vector<double>& value)
{
	std::hash_map<std::string, std::string>::iterator valueIterator;

	valueIterator = this->info.find(key);

	if(valueIterator != this->info.end())
	{
		std::stringstream ss;
		ss << valueIterator->second;
		ss >> value;

		return true;
	}
	return false;
}

const std::string Object::Keys::ID = "__ID";