#ifndef __LuaProcesses__
#define __LuaProcesses__

#include <string>

#include <boost/uuid/uuid_generators.hpp> // generators
#include <boost/uuid/uuid_io.hpp>         // streaming operators etc.
#include <Converter.h>
#include <Lua.hpp>

class LuaProcesses
{
public:
	LuaProcesses(){this->ID = CHL::ToString(boost::uuids::random_generator()()); }

	virtual void Update(double realTime, double deltaTime) = 0;

	virtual void Action(lua_State *lua) = 0;

	std::string ID;
};


#endif //__LuaProcesses__