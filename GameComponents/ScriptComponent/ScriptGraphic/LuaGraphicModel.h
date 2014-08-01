#ifndef __GraphicModel__
#define __GraphicModel__

#include "Linker.h"

#include <lua.hpp>
#include <luabind\luabind.hpp>
#include <GenericLuaObject.h>
#include <LuaModel.h>

namespace LuaGraphicModel
{
	class ScriptGraphicDLL_API GraphicModel : public GenericLuaObject
	{
	public:
		GraphicModel(const LuaModel::Model& model);
		GraphicModel(const GenericLuaObject& v);
		void Release();

		static void Register(lua_State *lua);
	};

	void RegisterAllLuaFunction(lua_State *lua);
}

#endif //__GraphicModel__
