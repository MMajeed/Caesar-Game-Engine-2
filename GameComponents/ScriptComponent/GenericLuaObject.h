#ifndef __GenericLuaObject__
#define __GenericLuaObject__

#include "Linker.h"

#include <string>
#include <Lua.hpp>
#include <luabind\luabind.hpp>

class ScriptComponentDLL_API GenericLuaObject
{
protected:
	std::string ID;
public:
	GenericLuaObject() = default;
	GenericLuaObject(const std::string& ID);
	virtual operator std::string();
	virtual std::string GetID() const;

	virtual ~GenericLuaObject(){}
	static void RegisterAllLuaFunction(lua_State *lua);
};

#endif //__GenericLuaObject__
