#ifndef __LuaModel__
#define __LuaModel__

extern "C" {
#include <lua-5.1.0\lua.h>
#include <lua-5.1.0\\lualib.h>
#include <lua-5.1.0\\lauxlib.h>
}

class LuaModel
{
public:
	class Model
	{
	public:
		static int NewModel(lua_State *lua);
		static void Register();
	};

	static inline void RegisterAllLuaFunction()
	{
		LuaModel::Model::Register();
	}
};

#endif //__LuaModel__