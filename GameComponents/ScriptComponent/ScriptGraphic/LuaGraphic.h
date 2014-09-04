#ifndef __LuaGraphic__
#define __LuaGraphic__

#include "Linker.h"

#include <Lua.hpp>
#include <luabind\luabind.hpp>
#include <GenericLuaObject.h>

namespace LuaGraphic
{
	ScriptGraphicDLL_API void ChangeWindowsTitle(std::string title);
	ScriptGraphicDLL_API void MoveWindow(unsigned int x, unsigned int y);
	ScriptGraphicDLL_API void ResizeWindow(unsigned int height, unsigned int width);
	ScriptGraphicDLL_API void ResizeClient(unsigned int height, unsigned int width);
	ScriptGraphicDLL_API void DiableResize();
	ScriptGraphicDLL_API void EnableResize();
	ScriptGraphicDLL_API void FullScreen();
	ScriptGraphicDLL_API void LeaveFullScreen();
	ScriptGraphicDLL_API bool IsFullScreen();
	ScriptGraphicDLL_API luabind::object GetClientsSize();
	ScriptGraphicDLL_API luabind::object GetWindowsSize();
	ScriptGraphicDLL_API luabind::object GetWindowsLoc();
	ScriptGraphicDLL_API void SetMainCamera(const GenericLuaObject& tx);
	ScriptGraphicDLL_API void SetCameraUpdate(bool v);
	ScriptGraphicDLL_API void SetObjectUpdate(bool v);

	ScriptGraphicDLL_API void RegisterAllLuaFunction(lua_State *lua);
};

#endif //__LuaGraphic__