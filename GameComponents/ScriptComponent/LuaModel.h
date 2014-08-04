#ifndef __LuaModel__
#define __LuaModel__

#include <Lua.hpp>
#include <luabind\luabind.hpp>
#include <memory>
#include <vector>
#include <Model.h>
#include "LuaMath.h"

namespace LuaModel
{
	class ScriptComponentDLL_API  Model
	{
	public:
		Model();
		Model(std::shared_ptr<CHL::Model> model);
		operator std::shared_ptr<CHL::Model>();

		unsigned int GetNumberFaces();
		void SetNumberFaces(const luabind::object& v);

		void SetFaces(luabind::object const& table);
		luabind::object GetFaces();

		void SetVertices(luabind::object const& table);
		luabind::object GetVertices();

		void SetNormal(luabind::object const& table);
		luabind::object GetNormal();

		void SetTangents(luabind::object const& table);
		luabind::object GetTangents();

		void SetBitangents(luabind::object const& table);
		luabind::object GetBitangents();

		void SetColor(luabind::object const& table);
		luabind::object GetColor();

		void SetTexture(luabind::object const& table);
		luabind::object GetTexture();

		std::shared_ptr<CHL::Model> model;

		static void Register(lua_State *lua);
	};

	void RegisterAllLuaFunction(lua_State *lua);
}

#endif //__LuaModel__