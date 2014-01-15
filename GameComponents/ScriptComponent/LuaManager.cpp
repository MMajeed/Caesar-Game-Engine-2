#include "LuaManager.h"

#include <exception>
#include <sstream>
#include <boost/filesystem.hpp>
#include <algorithm>
#include "LuaError.h"
#include "LuaRegisterAll.h"

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

	LuaRegisterAll(this->lua);
}

void LuaManager::Update(double realTime, double deltaTime)
{
	for(auto iterProcesses = this->allProcesses.begin();
		iterProcesses != this->allProcesses.end();
		++iterProcesses)
	{
		iterProcesses->second->Update(realTime, deltaTime);
	}
}

void LuaManager::Work()
{
	if(this->FileRun == false)
	{
		static const char mainLua[] = "Assets/Lua/main.lua";

		int error = luaL_loadfile(this->lua, mainLua);
		if (error != 0)	throw LuaError(this->lua);

		error = lua_pcall(this->lua, 0, 0, 0);
		if (error != 0)	throw LuaError(this->lua);

		this->FileRun = true;
	}

	for(auto iterProccessers = this->allProcesses.begin();
		iterProccessers !=  this->allProcesses.end();
		++iterProccessers)
	{
		iterProccessers->second->Action(this->lua);
	}
}

void LuaManager::Shutdown()
{

}

void LuaManager::SubmitProcesses(std::string ID, std::shared_ptr<LuaProcesses> process)
{
	this->allProcesses[ID] = process;
}

void LuaManager::RemoveProcesses(std::string ID)
{
	this->allProcesses.erase(ID);
}