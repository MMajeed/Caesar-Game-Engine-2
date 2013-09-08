#ifndef __LuaGraphic__
#define __LuaGraphic__

class LuaGraphic
{
public:
	class ClearScreen
	{
	public:
		static int Action(lua_State *lua);
		static void Register();
	};

	static inline void RegisterAllLuaFunction()
	{
		LuaGraphic::ClearScreen::Register();
	}
};

#endif //__LuaGraphic__