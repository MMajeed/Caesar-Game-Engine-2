#include "LuaManager.h"

#include <exception>
#include <sstream>
#include <boost/filesystem.hpp>
#include <algorithm>
#include "LuaError.h"
#include "LuaRegisterAll.h"
#include <Logger.h>

LuaManager::LuaManager()
{
	this->lua = 0;
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

	this->ProccessMessages();
	this->Work(0.0, 0.0);

	static const char mainLua[] = "Assets/Lua/main.lua";

	int ErrorException = luaL_loadfile(this->lua, mainLua);
	if(ErrorException != 0) Logger::LogError(LuaError::GetLuaError(lua));

	ErrorException = lua_pcall(this->lua, 0, 0, 0);
	if(ErrorException != 0)	Logger::LogError(LuaError::GetLuaError(lua));
}

void LuaManager::Work(double realTime, double deltaTime)
{
	for(auto iterProcesses = this->allProcesses.begin();
		iterProcesses != this->allProcesses.end();
		++iterProcesses)
	{
		iterProcesses->second->Update(realTime, deltaTime);
	}

	std::stack<std::string> removeProcessesStack;
	for(auto iterProccessers = this->allProcesses.begin();
		iterProccessers !=  this->allProcesses.end();
		++iterProccessers)
	{
		iterProccessers->second->Action(this->lua);
		if(iterProccessers->second->IsInfiniteLoop() == false)
		{
			removeProcessesStack.push(iterProccessers->second->ID);
		}
	}

	while(removeProcessesStack.empty() == false)
	{
		this->RemoveProcesses(removeProcessesStack.top());
		removeProcessesStack.pop();
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