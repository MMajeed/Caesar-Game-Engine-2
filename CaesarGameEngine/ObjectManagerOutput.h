#ifndef __ObjectManagerOutput__
#define __ObjectManagerOutput__

#include <Queryable.h>

class ObjectManagerOutput
{
public:
	static CHL::VectorQueryable<CHL::MapQueryable<std::string, std::string>> GetAllObjects();
};

#endif //__ObjectManagerOutput__