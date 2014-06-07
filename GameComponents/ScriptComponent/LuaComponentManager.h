#ifndef __LuaComponentManager__
#define __LuaComponentManager__

#include "Linker.h"

#include <Lua.hpp>
#include <luabind\luabind.hpp>

#include <string>

namespace LuaComponentManager
{
	ScriptComponentDLL_API void WaitToProcessGraphic(luabind::object const& function);
	ScriptComponentDLL_API void WaitToProcessInput(luabind::object const& function);
	ScriptComponentDLL_API void WaitToProcessScript(luabind::object const& function);
	ScriptComponentDLL_API void WaitToProcessAnimation(luabind::object const& function);
	ScriptComponentDLL_API void WaitToProcessPhysics(luabind::object const& function);

	ScriptComponentDLL_API void LogInformation(std::string message);
	ScriptComponentDLL_API void LogError(std::string message);
	ScriptComponentDLL_API void Quit();

	ScriptComponentDLL_API double GetTimeSinceStart();
	ScriptComponentDLL_API double GetGraphicFrame();
	ScriptComponentDLL_API double GetInputFrame();
	ScriptComponentDLL_API double GetScriptFrame();
	ScriptComponentDLL_API double GetAnimationFrame();
	ScriptComponentDLL_API double GetPhysicsFrame();

	ScriptComponentDLL_API void RegisterAllLuaFunction(lua_State *lua);
};

#endif //__LuaComponentManager__
