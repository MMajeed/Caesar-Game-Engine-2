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

	std::string Node::GetName()
	{
		return this->node->Name;
	}
	void Node::SetName(std::string v)
	{
		this->node->Name = v;
	}

	luabind::object Node::GetParent()
	{
		luabind::object returnValue;
		if(this->node)
		{
			returnValue(LuaNode::Node(this->node->Parent));
		}
		return returnValue;
	}
	void Node::SetParent(const luabind::object& v)
	{
		this->node->Parent = luabind::object_cast<LuaNode::Node>(v);
	}

	luabind::object Node::GetChildern()
	{
		lua_State *lua = LuaManager::GetInstance().lua;
		luabind::object outChildren = luabind::newtable(lua);

		unsigned int counter = 1;
		for(auto iter = this->node->Childern.begin();
			iter != this->node->Childern.end();
			++iter)
		{
			outChildren[counter] = LuaNode::Node(*iter);
			++counter;
		}
		return outChildren;
	}
	void Node::SetChildern(const luabind::object& v)
	{
		if(luabind::type(v) != LUA_TTABLE)
			Logger::LogError("Wrong paramter for Model::SetVertices, please send in a table");

		for(luabind::iterator it(v);
			it != luabind::iterator();
			++it)
		{
			std::shared_ptr<CHL::Node> ver = luabind::object_cast<LuaNode::Node>(*it);
			this->node->Childern.push_back(ver);
		}
	}

	luabind::object Node::GetMeshes()
	{
		lua_State *lua = LuaManager::GetInstance().lua;
		luabind::object outChildren = luabind::newtable(lua);

		unsigned int counter = 1;
		for(auto iter = this->node->meshes.begin();
			iter != this->node->meshes.end();
			++iter)
		{
			outChildren[counter] = (*iter) + 1;
		}
		return outChildren;
	}
	void Node::SetMeshes(const luabind::object& v)
	{
		if(luabind::type(v) != LUA_TTABLE)
			Logger::LogError("Wrong paramter for Model::SetVertices, please send in a table");

		for(luabind::iterator it(v);
			it != luabind::iterator();
			++it)
		{
			int ver = luabind::object_cast<int>(*it);
			this->node->meshes.push_back(ver - 1);
		}
	}

	LuaMath::Matrix4x4 Node::GetTransformation()
	{
		return this->node->Transformation;
	}
	void Node::SetTransformation(LuaMath::Matrix4x4 v)
	{
		this->node->Transformation = v;
	}

	void Node::Register(lua_State *lua)
	{
		luabind::module(lua)[
			luabind::class_<LuaNode::Node>("Node")
				.def(luabind::constructor<>())
				.property("Name", &Node::GetName, &Node::SetName)
				.property("Parent", &Node::GetParent, &Node::SetParent)
				.property("Childern", &Node::GetChildern, &Node::SetChildern)
				.property("Meshes", &Node::GetMeshes, &Node::SetMeshes)
				.property("Transformation", &Node::GetTransformation, &Node::SetTransformation)
		];
	}
	//----------------------------End Node--------------------------------------//


	void RegisterAllLuaFunction(lua_State *lua)
	{
		LuaNode::Node::Register(lua);
	}
}