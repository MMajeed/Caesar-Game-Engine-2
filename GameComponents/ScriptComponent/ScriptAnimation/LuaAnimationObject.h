#ifndef __LuaAnimationObject__
#define __LuaAnimationObject__

#include <lua.hpp>
#include <luabind\luabind.hpp>
#include <string>
#include <ScriptCommon\LuaAnimation.h>
#include <ScriptCommon\LuaNode.h>

namespace LuaAnimationObject
{
	class BasicAnimationObject
	{
	public:
		BasicAnimationObject();
		BasicAnimationObject(LuaAnimation::Animation anim);
		void Release();
		std::string ID;

		static void Register(lua_State *lua);
	};

	class AnimationController
	{
	public:
		AnimationController();
		AnimationController(luabind::object const& table);
		void ChangeAnimation(luabind::object const& table);
		void ChangeSpeed(double speed);
		std::string AddMinorAnimation(luabind::object const& table);
		void RemoveMinorAnimation(std::string MinorAnimationID);
		void Release();
		std::string ID;

		static void Register(lua_State *lua);
	};

	void RegisterAllLuaFunction(lua_State *lua);
}

#endif //__LuaAnimationObject__
