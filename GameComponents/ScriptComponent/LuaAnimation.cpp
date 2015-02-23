#include "LuaAnimation.h"

#include "ScriptManager.h"
#include "Resource.h"
#include <Model.h>
#include <3DLoader.h>
#include <string>
#include <Logger.h>


namespace LuaAnimation
{
	//-----------------------------Start Animation-------------------------------------//
	Animation::Animation()
	{
		this->anim = std::shared_ptr<CHL::Animation>(new CHL::Animation());
	}
	Animation::Animation(std::shared_ptr<CHL::Animation> anim)
	{
		this->anim = anim;
	}
	Animation::operator std::shared_ptr<CHL::Animation>()
	{
		return this->anim;
	}
	void Animation::Register(lua_State *lua)
	{
		luabind::module(lua)[
			luabind::class_<LuaAnimation::Animation>("Animation")
				.def(luabind::constructor<>())
		];
	}
	//----------------------------End Animation--------------------------------------//

	void RegisterAllLuaFunction(lua_State *lua)
	{
		LuaAnimation::Animation::Register(lua);
	}
}