#include "LuaAnimationObject.h"
#include <Logger.h>
#include <AnimationCommunicator\BasicAnimationConfig.h>
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

	AnimationController::AnimationController(){}
	AnimationController::AnimationController(luabind::object const& table)
	{
		if(luabind::type(table) != LUA_TTABLE)
			Logger::LogError("Wrong paramter for AnimationController, please send in a table");

		std::string animationID;
		LuaNode::Node rootNode;
		double speed = 1.0;


		for(luabind::iterator it(table);
			it != luabind::iterator();
			++it)
		{
			std::string key = luabind::object_cast<std::string>(it.key());

				 if(key == Keys::AnimationController::BASICANIMATION)	{ animationID = luabind::object_cast<BasicAnimationObject>(*it).ID; }
			else if(key == Keys::AnimationController::ROOTNODE)			{ rootNode = luabind::object_cast<LuaNode::Node>(*it); }
			else if(key == Keys::AnimationController::SPEED)			{ speed = luabind::object_cast<double>(*it); }
		}

		if(animationID.empty())
			Logger::LogError(Keys::AnimationController::BASICANIMATION + " is a mandatory field in AnimationController::ChangeAnimation");
		if(!rootNode.node)
			Logger::LogError(Keys::AnimationController::BASICANIMATION + " is a mandatory field in AnimationController::ROOTNODE");

		this->ID = AnimationControllerConfig::Create(animationID, rootNode.node, speed);
	}
	void AnimationController::ChangeAnimation(luabind::object const& table)
	{
		if(luabind::type(table) != LUA_TTABLE)
			Logger::LogError("Wrong paramter for AnimationController::ChangeAnimation, please send in a table");

		std::string animationID;
		int transitionType = 0;
		double transitionLength = 0;
		bool startonNextPhase = false;


		for(luabind::iterator it(table);
			it != luabind::iterator();
			++it)
		{
			std::string key = luabind::object_cast<std::string>(it.key());

				 if(key == Keys::AnimationController::BASICANIMATION)	{ animationID = luabind::object_cast<BasicAnimationObject>(*it).ID; }
			else if(key == Keys::AnimationController::TRANSITIONTYPE)	{ transitionType = luabind::object_cast<int>(*it); }
			else if(key == Keys::AnimationController::TRANSITIONLENGTH)	{ transitionLength = luabind::object_cast<double>(*it); }
			else if(key == Keys::AnimationController::STARTONNEXTPHASE)	{ startonNextPhase = luabind::object_cast<bool>(*it); }
		}

		if(animationID.empty())
			Logger::LogError(Keys::AnimationController::BASICANIMATION + " is a mandatory field in AnimationController::ChangeAnimation");

		AnimationControllerConfig::TransitionType t = static_cast<AnimationControllerConfig::TransitionType>(transitionType);
		AnimationControllerConfig::ChangeAnimation(this->ID, animationID, t, transitionLength, startonNextPhase);
	}
	void AnimationController::ChangeSpeed(double speed)
	{
		AnimationControllerConfig::ChangeSpeed(this->ID, speed);
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
				.def(luabind::constructor<luabind::object const&>())
				.def("ChangeAnimation", &AnimationController::ChangeAnimation)
				.def("ChangeSpeed", &AnimationController::ChangeSpeed)
				.def("Release", &AnimationController::Release)
				.def_readonly("ID", &AnimationController::ID)
		];


		luabind::object TransitionType = luabind::newtable(lua);
		TransitionType["None"] = 0;
		TransitionType["CrossFade"] = 1;
		TransitionType["SnapShot"] = 2;
		TransitionType["TimeSync"] = 3;
		luabind::globals(lua)["TransitionType"] = TransitionType;
	}

	void RegisterAllLuaFunction(lua_State *lua)
	{
		BasicAnimationObject::Register(lua);
		AnimationController::Register(lua);
	}
}
