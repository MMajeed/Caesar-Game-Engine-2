#ifndef __Object__
#define __Object__

#include "Linker.h"

#include <Queryable.h>
#include <string>
#include <boost/numeric/ublas/vector.hpp>

class Object
{
public:
	Object();
	Object(const CHL::MapQ<std::string, std::string>& input);

	CHL::MapQ<std::string, std::string> info;

	void Store(std::string key, const std::string& value);

	bool Retrieve(std::string key, std::string& value) const;

	bool Exist(std::string key) const;

	std::string ID();

	operator CHL::MapQ<std::string, std::string>();

	virtual ~Object(){}
};

#endif //__Object__