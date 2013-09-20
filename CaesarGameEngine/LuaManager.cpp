#include "LuaManager.h"

#include <exception>
#include <sstream>

#include "LuaGraphic.h"
#include "LuaModel.h"
#include "LuaObject.h"
#include "LuaUblas.h"
#include "LuaKeys.h"

LuaManager::LuaManager()
	: Interface("Lua")
	, lua(0)
{
	this->FileRun = false;
}

static const char mainLua[] = "Assets/Lua/main.lua";

void LuaManager::Init()
{
	this->lua = luaL_newstate();

	luabind::open(this->lua);

	luaopen_base(this->lua);
	luaopen_table(this->lua);
	luaopen_string(this->lua);
	luaopen_math(this->lua);
	luaopen_debug(this->lua);

	int error = luaL_loadfile(this->lua, mainLua);

	switch( error )
	{
	case LUA_ERRFILE:
		{
			std::stringstream ss;
			ss << "Cannot find/open lua script file: " << mainLua << std::endl;
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

	LuaGraphic::RegisterAllLuaFunction(this->lua);
	LuaModel::RegisterAllLuaFunction(this->lua);
	LuaUblas::RegisterAllLuaFunction(this->lua);
	LuaObject::RegisterAllLuaFunction(this->lua);
	LuaKeys::RegisterAllLuaFunction(this->lua);
}

void LuaManager::Update(double realTime, double deltaTime)
{

}

void LuaManager::Work()
{
	if(this->FileRun == false)
	{
		lua_call(this->lua,0,0);
		this->FileRun = true;
	}
}

void LuaManager::Shutdown()
{

}