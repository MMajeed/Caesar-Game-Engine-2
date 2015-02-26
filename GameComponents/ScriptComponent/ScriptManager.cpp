#include "ScriptManager.h"

#include <exception>
#include <sstream>
#include <boost/filesystem.hpp>
#include <algorithm>
#include "LuaError.h"
#include <Logger.h>

#include "Resource.h"
#include "GenericLuaObject.h"
#include "LuaMath.h"
#include "LuaKeysID.h"
#include "LuaThreadSetup.h"
#include "LuaComponentManager.h"
#include "Lua3DFile.h"
#include "LuaModel.h"
#include "LuaAnimation.h"
#include "LuaNode.h"
#include "ProcessMessage.h"

ScriptManager::ScriptManager()
{
}

void ScriptManager::Init()
{
	Resource::lua = lua_open();

	lua_pushcfunction(Resource::lua,luaopen_base);
	lua_call(Resource::lua,0,0);
	lua_pushcfunction(Resource::lua,luaopen_table);
	lua_call(Resource::lua,0,0);
	lua_pushcfunction(Resource::lua,luaopen_io);
	lua_call(Resource::lua,0,0);
	lua_pushcfunction(Resource::lua,luaopen_os);
	lua_call(Resource::lua,0,0);
	lua_pushcfunction(Resource::lua,luaopen_string);
	lua_call(Resource::lua,0,0);
	lua_pushcfunction(Resource::lua,luaopen_math);
	lua_call(Resource::lua,0,0);
	lua_pushcfunction(Resource::lua,luaopen_debug);
	lua_call(Resource::lua,0,0);
	lua_pushcfunction(Resource::lua,luaopen_package);
	lua_call(Resource::lua,0,0);

	luabind::open(Resource::lua);    

	this->ActivateLuaClassesNFunction();

	class RunMain : public LuaProcesses
	{
	public:
		void Update(double realTime, double deltaTime){}
		void Action(lua_State *lua)
		{
			std::string packagePath = "package.path = \"";
			packagePath += boost::filesystem::current_path().string() + "/Assets/Lua/?.lua\"";
			std::replace(packagePath.begin(), packagePath.end(), '\\', '/');
			luaL_dostring(Resource::lua, packagePath.c_str());

			static const char mainLua[] = "Assets/Lua/main.lua";
			
			int ErrorException = luaL_loadfile(Resource::lua, mainLua);
			if(ErrorException != 0) Logger::LogError(LuaError::GetLuaError(Resource::lua));

			ErrorException = lua_pcall(Resource::lua, 0, 0, 0);
			if(ErrorException != 0)	Logger::LogError(LuaError::GetLuaError(Resource::lua));

			this->Delete = true;
		}
	};

	std::shared_ptr<RunMain> rm(new RunMain);
	ProcessMessage::Add(rm);
}

void ScriptManager::Work(double realTime, double deltaTime)
{
	for(auto iterProcesses = Resource::allProcesses.begin();
		iterProcesses != Resource::allProcesses.end();
		++iterProcesses)
	{
		iterProcesses->second->Update(realTime, deltaTime);
	}

	std::stack<std::string> removeProcessesStack;
	for(auto iterProccessers = Resource::allProcesses.begin();
		iterProccessers !=  Resource::allProcesses.end();
		++iterProccessers)
	{
		iterProccessers->second->Action(Resource::lua);
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
	GenericLuaObject::RegisterAllLuaFunction(Resource::lua);
	LuaMath::RegisterAllLuaFunction(Resource::lua);
	LuaKeysID::RegisterAllLuaFunction(Resource::lua);
	LuaThreadSetup::RegisterAllLuaFunction(Resource::lua);
	LuaComponentManager::RegisterAllLuaFunction(Resource::lua);
	Lua3DFile::RegisterAllLuaFunction(Resource::lua);
	LuaModel::RegisterAllLuaFunction(Resource::lua);
	LuaAnimation::RegisterAllLuaFunction(Resource::lua);
	LuaNode::RegisterAllLuaFunction(Resource::lua);

	this->ProccessMessages();
	this->Work(0.0, 0.0);
}

void ScriptManager::SubmitProcesses(std::string ID, std::shared_ptr<LuaProcesses> process)
{
	Resource::allProcesses[ID] = process;
}

void ScriptManager::RemoveProcesses(std::string ID)
{
	Resource::allProcesses.erase(ID);
}