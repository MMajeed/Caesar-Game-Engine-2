#ifndef __ObjectManagerOutput__
#define __ObjectManagerOutput__

#include "Linker.h"
#include <Queryable.h>
#include <Object.h>

class ObjectManagerOutput
{
public:
	static CHL::VectorQ<CHL::MapQ<std::string, std::shared_ptr<Object>>> GetAllObjects();
	static CHL::MapQ<std::string, std::shared_ptr<Object>> GetObject(std::string id);
};

#endif //__ObjectManagerOutput__