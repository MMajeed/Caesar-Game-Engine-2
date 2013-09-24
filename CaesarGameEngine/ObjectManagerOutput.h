#ifndef __ObjectManagerOutput__
#define __ObjectManagerOutput__

#include <Queryable.h>

class ObjectManagerOutput
{
public:
	static CHL::VectorQ<CHL::MapQ<std::string, std::string>> GetAllObjects();
	static CHL::MapQ<std::string, std::string> GetObject(std::string id);
};

#endif //__ObjectManagerOutput__