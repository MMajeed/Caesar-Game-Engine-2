#ifndef __ObjectName__
#define __ObjectName__

#include <vector>
#include <hash_map>
#include <Object.h>
#include <memory>

namespace TypedefObject
{
	typedef std::hash_map<std::string, std::shared_ptr<Object>> ObjectInfo;
	typedef std::vector<ObjectInfo> ObjectVector;
};

#endif //__ObjectName__