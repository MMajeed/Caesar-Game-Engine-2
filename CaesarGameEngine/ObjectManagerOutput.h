#ifndef __ObjectManagerOutput__
#define __ObjectManagerOutput__

#include <MapQueryable.h>
#include <VectorQueryable.h>

class ObjectManagerOutput
{
public:
	static CHL::VectorQueryable<CHL::MapQueryable<std::string, std::string>> GetAllObjects();
};

#endif //__ObjectManagerOutput__