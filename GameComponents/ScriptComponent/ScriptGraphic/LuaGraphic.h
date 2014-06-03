#ifndef __LuaGraphic__
#define __LuaGraphic__

#include <Lua.hpp>
#include <luabind\luabind.hpp>

namespace LuaGraphic
{
	void ChangeWindowsTitle(std::string title);
	void MoveWindow(unsigned int x, unsigned int y);
	void ResizeWindow(unsigned int height, unsigned int width);
	void ResizeClient(unsigned int height, unsigned int width);
	void DiableResize();
	void EnableResize();
	void FullScreen();
	void LeaveFullScreen();
	bool IsFullScreen();
	luabind::object GetClientsSize();
	luabind::object GetWindowsSize();
	luabind::object GetWindowsLoc();

	void RegisterAllLuaFunction(lua_State *lua);
};

#endif //__LuaGraphic__