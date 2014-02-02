#include "LuaAnimationObject.h"
#include <Logger.h>
#include <AnimationCommunicator\BasicAnimationConfig.h>
#include <AnimationCommunicator\AnimationPlayerConfig.h>
#include <AnimationCommunicator\AnimationControllerConfig.h>
#include <Keys.h>

namespace LuaAnimationObject
{
	
	BasicAnimationObject::BasicAnimationObject(){}
	BasicAnimationObject::BasicAnimationObject(LuaAnimation::Animation anim)
	{
		this->ID = BasicAnimationConfig::Create(anim);
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
				.def(luabind::constructor<LuaAnimation::Animation>())
				.def("Release", &BasicAnimationObject::Release)
				.def_readonly("ID", &BasicAnimationObject::ID)
		];
	}

	AnimationPlayer::AnimationPlayer(){}
	AnimationPlayer::AnimationPlayer(luabind::object const& table)
	{
		if(luabind::type(table) != LUA_TTABLE)
			Logger::LogError("Wrong paramter for AnimationPlayer, please send in a table");
		
		std::string basicAnimationID;
		double phase = 0.0;
		double speed = 1.0;

		for(luabind::iterator it(table);
			it != luabind::iterator();
			++it)
		{
			std::string key = luabind::object_cast<std::string>(it.key());

				 if(key == Keys::AnimationPlayer::BASICANIMATION)	{ basicAnimationID = luabind::object_cast<BasicAnimationObject>(*it).ID; }
			else if(key == Keys::AnimationPlayer::PHASE)			{ phase = luabind::object_cast<double>(*it); }
			else if(key == Keys::AnimationPlayer::SPEED)			{ speed = luabind::object_cast<double>(*it); }
		}
		if(basicAnimationID.empty())
			Logger::LogError(Keys::AnimationPlayer::BASICANIMATION + " is a manditory paramter in AnimationPlayer" );
		this->ID = AnimationPlayerConfig::Create(basicAnimationID, phase, speed);
	}
	void AnimationPlayer::SetPhase(double v)
	{
		AnimationPlayerConfig::SetPhase(this->ID, v);
	}
	void AnimationPlayer::SetSpeed(double v)
	{
		AnimationPlayerConfig::SetSpeed(this->ID, v);
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
				.def(luabind::constructor<luabind::object>())
				.def("SetSpeed", &AnimationPlayer::SetSpeed)
				.def("SetPhase", &AnimationPlayer::SetPhase)
				.def("Release", &AnimationPlayer::Release)
				.def_readonly("ID", &AnimationPlayer::ID)
		];
	}

	AnimationController::AnimationController(){}
	AnimationController::AnimationController(AnimationPlayer v, LuaNode::Node rootNode)
	{
		this->ID = AnimationControllerConfig::Create(v.ID, rootNode);
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
				.def(luabind::constructor<LuaAnimationObject::AnimationPlayer, LuaNode::Node>())
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
