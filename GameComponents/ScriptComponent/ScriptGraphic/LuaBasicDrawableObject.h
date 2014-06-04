#ifndef __LuaBasicDrawableObject__
#define __LuaBasicDrawableObject__

#include "Linker.h"

#include <lua.hpp>
#include <luabind\luabind.hpp>
#include <string>
#include "ScriptCommon\LuaModel.h"

namespace LuaBasicDrawableObject
{
	class ScriptGraphicDLL_API BasicDrawableObject
	{
	public:
		BasicDrawableObject(){}
		BasicDrawableObject(luabind::object const& table);
		void ChangeModel(LuaModel::Model model);
		void ChangeRastersizerState(int cullMode, int fillMode);
		void ChangeVS(std::string fileName);
		void ChangeGS(std::string fileName);
		void ChangePS(std::string fileName);
		void Release();
		std::string ID;

		static void Register(lua_State *lua);
	};

	void RegisterAllLuaFunction(lua_State *lua);
}

#endif //__LuaBasicDrawableObject__
