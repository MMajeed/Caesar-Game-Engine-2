#ifndef __LuaAnimation__
#define __LuaAnimation__

#include <Lua.hpp>
#include <luabind\luabind.hpp>
#include <memory>
#include <vector>
#include <Animation.h>
#include "LuaMath.h"

namespace LuaAnimation
{
	class Animation
	{
	public:
		Animation();
		Animation(std::shared_ptr<CHL::Animation> anim);
		operator std::shared_ptr<CHL::Animation>();

		std::shared_ptr<CHL::Animation> anim;

		static void Register(lua_State *lua);
	};

	void RegisterAllLuaFunction(lua_State *lua);
}

#endif //__LuaAnimation__