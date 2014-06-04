#ifndef __LuaNode__
#define __LuaNode__

#include <Lua.hpp>
#include <luabind\luabind.hpp>
#include <memory>
#include <vector>
#include <Node.h>
#include "LuaMath.h"

namespace LuaNode
{
	class ScriptCommonDLL_API Node
	{
	public:
		Node();
		Node(std::shared_ptr<CHL::Node> anim);
		operator std::shared_ptr<CHL::Node>();
		
		std::string GetName();
		void SetName(std::string v);

		luabind::object GetParent();
		void SetParent(const luabind::object& v);

		luabind::object GetChildern();
		void SetChildern(const luabind::object& v);

		luabind::object GetMeshes();
		void SetMeshes(const luabind::object& v);

		LuaMath::Matrix4x4 GetTransformation();
		void SetTransformation(LuaMath::Matrix4x4 v);

		std::shared_ptr<CHL::Node> node;

		static void Register(lua_State *lua);
	};

	void RegisterAllLuaFunction(lua_State *lua);
}

#endif //__LuaNode__