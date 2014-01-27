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
	class Node
	{
	public:
		Node();
		Node(std::shared_ptr<CHL::Node> anim);
		operator std::shared_ptr<CHL::Node>();

		std::shared_ptr<CHL::Node> node;

		static void Register(lua_State *lua);
	};

	void RegisterAllLuaFunction(lua_State *lua);
}

#endif //__LuaNode__