#ifndef __LuaModel__
#define __LuaModel__

#include <Lua.hpp>
#include <luabind\luabind.hpp>
#include <memory>
#include <Model.h>
#include <vector>

namespace LuaModel
{
	class Model
	{
	public:
		Model();
		Model(std::shared_ptr<CHL::Model> model);
		operator std::shared_ptr<CHL::Model>();
		
		std::shared_ptr<CHL::Model> model;

		static void Register(lua_State *lua);
	};

	LuaModel::Model GetFirstModel(std::string fileName);
	luabind::object GetScene(std::string fileName);

	void RegisterAllLuaFunction(lua_State *lua);
};

#endif //__LuaModel__