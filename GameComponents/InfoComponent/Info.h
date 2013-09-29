#ifndef __Info__
#define __Info__

#include "Linker.h"

#include <Queryable.h>
#include <string>
#include <Object.h>

class Info
{
public:	
	CHL::MapQ<std::string, std::shared_ptr<Object>> info;

	Info();
	Info(const CHL::MapQ<std::string, std::shared_ptr<Object>>& input);

	void Store(std::string key, std::shared_ptr<Object> value);

	bool Retrieve(std::string key, std::shared_ptr<Object>& value) const;

	bool Exist(std::string key) const;

	std::string ID();

	virtual ~Info(){}
};

#endif //__Info__