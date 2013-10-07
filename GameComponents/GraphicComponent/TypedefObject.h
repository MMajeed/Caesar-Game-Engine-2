#ifndef __ObjectName__
#define __ObjectName__

#include <Queryable.h>
#include <Object.h>
#include <memory>

namespace TypedefObject
{
	typedef CHL::MapQ<std::string, std::shared_ptr<Object>> ObjectInfo;
	typedef CHL::VectorQ<ObjectInfo> ObjectVector;
};

#endif //__ObjectName__