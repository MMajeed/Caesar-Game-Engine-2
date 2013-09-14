#ifndef __LuaGraphic__
#define __LuaGraphic__

extern "C" {
#include <lua-5.1.0\lua.h>
#include <lua-5.1.0\\lualib.h>
#include <lua-5.1.0\\lauxlib.h>
}

class LuaGraphic
{
public:
	class ClearScreen
	{
	public:
		static void Action(double x, double y, double z);
		static void Register();
	};

	static inline void RegisterAllLuaFunction()
	{
		LuaGraphic::ClearScreen::Register();
	}
};

#endif //__LuaGraphic__