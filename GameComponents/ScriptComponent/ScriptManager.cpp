#include "ScriptManager.h"

#include <exception>
#include <sstream>
#include <boost/filesystem.hpp>
#include <algorithm>
#include "LuaError.h"
#include <Logger.h>

#include "GenericLuaObject.h"
#include "LuaMath.h"
#include "LuaKeysID.h"
#include "LuaThreadSetup.h"
#include "LuaComponentManager.h"
#include "Lua3DFile.h"
#include "LuaModel.h"
#include "LuaAnimation.h"
#include "LuaNode.h"

ScriptManager::ScriptManager()
{
	this->lua = 0;
}


void ScriptManager::Init()
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
	
	this->ActivateLuaClassesNFunction();

	static const char mainLua[] = "Assets/Lua/main.lua";

	int ErrorException = luaL_loadfile(this->lua, mainLua);
	if(ErrorException != 0) Logger::LogError(LuaError::GetLuaError(lua));

	ErrorException = lua_pcall(this->lua, 0, 0, 0);
	if(ErrorException != 0)	Logger::LogError(LuaError::GetLuaError(lua));
}

void ScriptManager::Work(double realTime, double deltaTime)
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
		if(iterProccessers->second->DoDelete() == true)
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

void ScriptManager::Shutdown()
{

}

void ScriptManager::ActivateLuaClassesNFunction()
{
	GenericLuaObject::RegisterAllLuaFunction(this->lua);
	LuaMath::RegisterAllLuaFunction(this->lua);
	LuaKeysID::RegisterAllLuaFunction(this->lua);
	LuaThreadSetup::RegisterAllLuaFunction(this->lua);
	LuaComponentManager::RegisterAllLuaFunction(this->lua);
	Lua3DFile::RegisterAllLuaFunction(this->lua);
	LuaModel::RegisterAllLuaFunction(this->lua);
	LuaAnimation::RegisterAllLuaFunction(this->lua);
	LuaNode::RegisterAllLuaFunction(this->lua);

	this->ProccessMessages();
	this->Work(0.0, 0.0);
}

void ScriptManager::SubmitProcesses(std::string ID, std::shared_ptr<LuaProcesses> process)
{
	this->allProcesses[ID] = process;
}

void ScriptManager::RemoveProcesses(std::string ID)
{
	this->allProcesses.erase(ID);
}