#ifndef __Info__
#define __Info__

#include "Linker.h"
#include <hash_map>
#include <string>
#include <Object.h>

class Info
{
public:	
	std::hash_map<std::string, std::shared_ptr<Object>> info;

	Info();
	Info(const std::hash_map<std::string, std::shared_ptr<Object>>& input);

	void Store(std::string key, std::shared_ptr<Object> value);

	bool Retrieve(std::string key, std::shared_ptr<Object>& value) const;

	void Erase(std::string key);

	bool Exist(std::string key) const;

	std::string ID() const;

	virtual ~Info(){}
};

#endif //__Info__