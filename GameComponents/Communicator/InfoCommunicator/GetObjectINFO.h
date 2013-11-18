#ifndef __GetObjectINFO__
#define __GetObjectINFO__

#include "Linker.h"
#include <INFO.h>
#include <hash_map>
#include <string>

class GetObjectINFO
{
public:
	static std::hash_map<std::string, SP_INFO> GetAllObjects();
	static SP_INFO GetObject(std::string id);
};

#endif //__GetObjectINFO__