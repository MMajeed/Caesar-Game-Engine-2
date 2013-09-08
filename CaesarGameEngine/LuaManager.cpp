#include "LuaManager.h"

#include <exception>
#include <sstream>

#include "LuaGraphic.h"

LuaManager::LuaManager()
	: lua(0)
{

}

static const char mainLua[] = "Assets/Lua/main.lua";

void LuaManager::Init()
{
	lua = luaL_newstate();

    luaopen_base(lua);
    luaopen_table(lua);
    luaopen_string(lua);
    luaopen_math(lua);
    
	int error = luaL_loadfile(lua, mainLua);

	switch( error )
	{
		case LUA_ERRFILE:
		{
			std::stringstream ss;
			ss << "Cannot find/open lua script file: " << mainLua <<std::endl;
			throw std::exception( ss.str().c_str() );
		}
		case LUA_ERRSYNTAX:
		{
			std::stringstream ss;
			ss << "Fatal memory allocation error during processing of script file: " << mainLua << std::endl;
			throw std::exception( ss.str().c_str() );
		}
		case LUA_ERRMEM:
		{
			std::stringstream ss;
			ss << "Syntax error during pre-compilation of script file:  " << mainLua << std::endl;
			throw std::exception( ss.str().c_str() );
		}
	}

	LuaGraphic::RegisterAllLuaFunction();

	lua_call(lua,0,0);
}

void LuaManager::Update(double realTime, double deltaTime)
{

}

void LuaManager::Work()
{
	luaL_loadfile(lua, mainLua);
	lua_call(lua,0,0);
}

void LuaManager::Shutdown()
{

}