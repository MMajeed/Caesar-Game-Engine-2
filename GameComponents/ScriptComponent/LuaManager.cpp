#include "LuaManager.h"

#include <exception>
#include <sstream>
#include <boost/filesystem.hpp>
#include <algorithm>

#include "LuaGraphic.h"
#include "LuaModel.h"
#include "LuaObject.h"
#include "LuaUblas.h"
#include "LuaKeysID.h"
#include "LuaKeyActionSetup.h"
#include "LuaCamera.h"
#include "LuaLoopCallSetup.h"
#include "LuaBasicDrawableObject.h"
#include "LuaBasicTexture.h"

LuaManager::LuaManager()
{
	this->lua = 0;
	this->FileRun = false;
}


void LuaManager::Init()
{
	this->lua = lua_open();

	lua_pushcfunction(this->lua,luaopen_base);
	lua_call(this->lua,0,0);
	lua_pushcfunction(this->lua,luaopen_table);
	lua_call(this->lua,0,0);
	lua_pushcfunction(this->lua,luaopen_io);
	lua_call(this->lua,0,0);
	lua_pushcfunction(this->lua,luaopen_os);
	lua_call(this->lua,0,0);
	lua_pushcfunction(this->lua,luaopen_string);
	lua_call(this->lua,0,0);
	lua_pushcfunction(this->lua,luaopen_math);
	lua_call(this->lua,0,0);
	lua_pushcfunction(this->lua,luaopen_debug);
	lua_call(this->lua,0,0);
	lua_pushcfunction(this->lua,luaopen_package);
	lua_call(this->lua,0,0);

	luabind::open(this->lua);    

	std::string packagePath = "package.path = \"";
	packagePath += boost::filesystem::current_path().string() + "/Assets/Lua/?.lua\"";
	std::replace(packagePath.begin(), packagePath.end(), '\\', '/');
	luaL_dostring(this->lua, packagePath.c_str());	

	LuaGraphic::RegisterAllLuaFunction(this->lua);
	LuaModel::RegisterAllLuaFunction(this->lua);
	LuaUblas::RegisterAllLuaFunction(this->lua);
	LuaObject::RegisterAllLuaFunction(this->lua);
	LuaKeysID::RegisterAllLuaFunction(this->lua);
	LuaKeyActionSetup::RegisterAllLuaFunction(this->lua);
	LuaCamera::RegisterAllLuaFunction(this->lua);
	LuaLoopCallSetup::RegisterAllLuaFunction(this->lua);
	LuaBasicDrawableObject::RegisterAllLuaFunction(this->lua);
	LuaBasicTexture::RegisterAllLuaFunction(this->lua);
}

void LuaManager::Update(double realTime, double deltaTime)
{
	for(auto iterProcesses = this->allProcesses.begin();
		iterProcesses != this->allProcesses.end();
		++iterProcesses)
	{
		(*iterProcesses)->Update(realTime, deltaTime);
	}
}

static const char mainLua[] = "Assets/Lua/main.lua";

void LuaManager::Work()
{
	if(this->FileRun == false)
	{
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

		lua_call(this->lua,0,0);
		this->FileRun = true;
	}

	for(auto iterProccessers = this->allProcesses.begin();
		iterProccessers !=  this->allProcesses.end();
		++iterProccessers)
	{
		(*iterProccessers)->Action();
	}
}

void LuaManager::Shutdown()
{

}

void LuaManager::SubmitProcesses(std::shared_ptr<LuaProcesses> process)
{
	this->allProcesses.push_back(process);
}