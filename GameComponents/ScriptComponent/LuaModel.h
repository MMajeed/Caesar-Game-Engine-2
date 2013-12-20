#ifndef __LuaModel__
#define __LuaModel__

#include <Lua.hpp>
#include <luabind\luabind.hpp>
#include <memory>
#include <Model.h>
#include <vector>
#include "LuaMath.h"

namespace LuaModel
{
	class Vertices
	{
	public:
		Vertices();
		Vertices(luabind::object const& table);
		Vertices(CHL::Model::VerticesInfo vertices);
		operator CHL::Model::VerticesInfo();

		LuaMath::Vector4 Point;
		LuaMath::Vector4 Normal;
		LuaMath::Vector4 Texture;

		static void Register(lua_State *lua);
	};
	class Model
	{
	public:
		Model();
		Model(std::shared_ptr<CHL::Model> model);
		operator std::shared_ptr<CHL::Model>();
		
		void SetVertices(luabind::object const& table);
		luabind::object GetVertices();
		void SeFaces(luabind::object const& table);
		luabind::object GetFaces();

		std::shared_ptr<CHL::Model> model;

		static void Register(lua_State *lua);
	};

	LuaModel::Model GetFirstModel(std::string fileName);
	luabind::object GetScene(std::string fileName);

	void RegisterAllLuaFunction(lua_State *lua);
};

#endif //__LuaModel__