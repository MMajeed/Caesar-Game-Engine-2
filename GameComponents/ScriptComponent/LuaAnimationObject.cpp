#include "LuaAnimationObject.h"

#include <AnimationCommunicator\BasicAnimationConfig.h>
#include <AnimationCommunicator\AnimationPlayerConfig.h>
#include <AnimationCommunicator\AnimationControllerConfig.h>

namespace LuaAnimationObject
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

	AnimationPlayer::AnimationPlayer(){}
	AnimationPlayer::AnimationPlayer(BasicAnimationObject v)
	{
		this->ID = AnimationPlayerConfig::Create(v.ID, 0.0, 1.0);
	}
	void AnimationPlayer::Release()
	{
		AnimationPlayerConfig::Release(this->ID);
		this->ID = "";
	}
	void AnimationPlayer::Register(lua_State *lua)
	{
		luabind::module(lua)[
			luabind::class_<AnimationPlayer>("AnimationPlayer")
				.def(luabind::constructor<LuaAnimationObject::BasicAnimationObject>())
				.def("Release", &AnimationPlayer::Release)
				.def_readonly("ID", &AnimationPlayer::ID)
		];
	}

	AnimationController::AnimationController(){}
	AnimationController::AnimationController(AnimationPlayer v)
	{
		this->ID = AnimationControllerConfig::Create(v.ID);
	}
	void AnimationController::Release()
	{
		AnimationControllerConfig::Release(this->ID);
		this->ID = "";
	}
	void AnimationController::Register(lua_State *lua)
	{
		luabind::module(lua)[
			luabind::class_<AnimationController>("AnimationController")
				.def(luabind::constructor<LuaAnimationObject::AnimationPlayer>())
				.def("Release", &AnimationController::Release)
				.def_readonly("ID", &AnimationController::ID)
		];
	}

	void RegisterAllLuaFunction(lua_State *lua)
	{
		BasicAnimationObject::Register(lua);
		AnimationPlayer::Register(lua);
		AnimationController::Register(lua);
	}
}
