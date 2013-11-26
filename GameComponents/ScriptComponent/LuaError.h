#ifndef __LuaError__
#define __LuaError__

#include <lua.hpp>
#include <stdexcept>
#include <memory>

class LuaError : public std::exception
{
private:
	lua_State * m_L;
	// resource for error object on Lua stack (is to be popped
	// when no longer used)
	std::shared_ptr<lua_State> m_lua_resource;
	LuaError & operator=(const LuaError & other); // prevent
public:
	// Construct using top-most element on Lua stack as error.
	LuaError(lua_State * L);
	LuaError(const LuaError & other);
	~LuaError();
	virtual const char * what() const throw();
};

#endif //__LuaError__
