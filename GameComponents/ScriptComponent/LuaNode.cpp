#include "LuaNode.h"

#include "LuaManager.h"
#include <Model.h>
#include <3DLoader.h>
#include <string>
#include <Logger.h>

namespace LuaNode
{
	//-----------------------------Start Node-------------------------------------//
	Node::Node()
	{
		this->node = std::shared_ptr<CHL::Node>(new CHL::Node());
	}
	Node::Node(std::shared_ptr<CHL::Node> node)
	{
		this->node = node;
	}
	Node::operator std::shared_ptr<CHL::Node>()
	{
		return this->node;
	}
	void Node::Register(lua_State *lua)
	{
		luabind::module(lua)[
			luabind::class_<LuaNode::Node>("Node")
				.def(luabind::constructor<>())
		];
	}
	//----------------------------End Node--------------------------------------//


	void RegisterAllLuaFunction(lua_State *lua)
	{
		LuaNode::Node::Register(lua);
	}
}