#ifndef __LuaComponentManager__
#define __LuaComponentManager__

#include <Lua.hpp>
#include <luabind\luabind.hpp>

#include <string>

namespace LuaComponentManager
{
	void WaitToProcessGraphic(luabind::object const& function);
	void WaitToProcessInput(luabind::object const& function);
	void WaitToProcessScript(luabind::object const& function);
	void WaitToProcessAnimation(luabind::object const& function);

	void LogInformation(std::string message);
	void LogError(std::string message);
	void Quit();

	double GetTimeSinceStart();
	double GetGraphicFrame();
	double GetInputFrame();
	double GetScriptFrame();
	double GetAnimationFrame();

	void RegisterAllLuaFunction(lua_State *lua);
};

#endif //__LuaComponentManager__
