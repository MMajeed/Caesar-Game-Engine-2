#include "LuaBasicAnimationObject.h"

#include <AnimationCommunicator\BasicAnimationConfig.h>

namespace LuaBasicAnimationObject
{
	
	BasicAnimationObject::BasicAnimationObject(){}
	BasicAnimationObject::BasicAnimationObject(LuaAnimation::Animation anim, LuaNode::Node rootNode)
	{
		this->ID = BasicAnimationConfig::Create(anim, rootNode);
	}
	void BasicAnimationObject::Release()
	{
		BasicAnimationConfig::Release(this->ID);
		this->ID = "";
	}

	void BasicAnimationObject::Register(lua_State *lua)
	{
		luabind::module(lua)[
			luabind::class_<BasicAnimationObject>("BasicAnimation")
				.def(luabind::constructor<LuaAnimation::Animation, LuaNode::Node>())
				.def("Release", &BasicAnimationObject::Release)
				.def_readonly("ID", &BasicAnimationObject::ID)
		];
	}

	void RegisterAllLuaFunction(lua_State *lua)
	{
		BasicAnimationObject::Register(lua);
	}
}
