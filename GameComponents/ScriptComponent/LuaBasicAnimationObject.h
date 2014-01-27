#ifndef __LuaBasicAnimationObject__
#define __LuaBasicAnimationObject__

#include <lua.hpp>
#include <luabind\luabind.hpp>
#include <string>
#include "LuaAnimation.h"
#include "LuaNode.h"

namespace LuaBasicAnimationObject
{
	class BasicAnimationObject
	{
	public:
		BasicAnimationObject();
		BasicAnimationObject(LuaAnimation::Animation anim, LuaNode::Node rootNode);
		void Release();
		std::string ID;

		static void Register(lua_State *lua);
	};

	void RegisterAllLuaFunction(lua_State *lua);
}

#endif //__LuaBasicAnimationObject__
