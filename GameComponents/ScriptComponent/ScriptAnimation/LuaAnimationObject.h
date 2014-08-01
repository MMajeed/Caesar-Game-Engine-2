#ifndef __LuaAnimationObject__
#define __LuaAnimationObject__

#include "Linker.h"

#include <lua.hpp>
#include <luabind\luabind.hpp>
#include <GenericLuaObject.h>
#include <LuaAnimation.h>
#include <LuaNode.h>

namespace LuaAnimationObject
{
	class ScriptAnimationDLL_API BasicAnimationObject : public GenericLuaObject
	{
	public:
		BasicAnimationObject();
		BasicAnimationObject(const GenericLuaObject& v);
		BasicAnimationObject(LuaAnimation::Animation anim);
		void Release();

		static void Register(lua_State *lua);
	};

	class ScriptAnimationDLL_API AnimationController : public GenericLuaObject
	{
	public:
		AnimationController();
		AnimationController(const GenericLuaObject& v);
		AnimationController(luabind::object const& table);
		void ChangeAnimation(luabind::object const& table);
		void ChangeSpeed(double speed);
		std::string AddMinorAnimation(luabind::object const& table);
		void RemoveMinorAnimation(std::string MinorAnimationID);
		void Release();

		static void Register(lua_State *lua);
	};

	void RegisterAllLuaFunction(lua_State *lua);
}

#endif //__LuaAnimationObject__
