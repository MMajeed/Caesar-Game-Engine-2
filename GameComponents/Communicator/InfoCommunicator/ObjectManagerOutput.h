#ifndef __ObjectManagerOutput__
#define __ObjectManagerOutput__

#include "Linker.h"
#include <vector>
#include <hash_map>
#include <Object.h>

class ObjectManagerOutput
{
public:
	static std::vector<std::hash_map<std::string, std::shared_ptr<Object>>> GetAllObjects();
	static std::hash_map<std::string, std::shared_ptr<Object>> GetObject(std::string id);
};

#endif //__ObjectManagerOutput__