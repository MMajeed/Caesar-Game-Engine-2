#ifndef __LuaBasicDrawableObject__
#define __LuaBasicDrawableObject__

#include <lua.hpp>
#include <luabind\luabind.hpp>
#include <string>
#include "LuaModel.h"

namespace LuaBasicDrawableObject
{
	class BasicDrawableObject
	{
	public:
		BasicDrawableObject(){}
		BasicDrawableObject(luabind::object const& table);
		void ChangeModel(LuaModel::Model model);
		void ChangeRastersizerState(int cullMode, int fillMode);
		void Release();
		std::string ID;

		static void Register(lua_State *lua);
	};

	void RegisterAllLuaFunction(lua_State *lua);
}

#endif //__LuaBasicDrawableObject__
