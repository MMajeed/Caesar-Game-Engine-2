#include "LuaAnimationObject.h"
#include <Logger.h>
#include <Components.h>
#include <Keys.h>

namespace LuaAnimationObject
{
	
	BasicAnimationObject::BasicAnimationObject(){}
	BasicAnimationObject::BasicAnimationObject(const GenericLuaObject& v) : GenericLuaObject(v){}
	BasicAnimationObject::BasicAnimationObject(LuaAnimation::Animation anim)
	{
		this->ID = Components::Animation->BasicAnimationFactory()->Create(anim);
	}
	void BasicAnimationObject::Release()
	{
		Components::Animation->BasicAnimationFactory()->Release(this->ID);
		this->ID = "";
	}
	void BasicAnimationObject::Register(lua_State *lua)
	{
		luabind::module(lua)[
			luabind::class_<BasicAnimationObject, GenericLuaObject>("BasicAnimation")
				.def(luabind::constructor<const GenericLuaObject&>())
				.def(luabind::constructor<LuaAnimation::Animation>())
				.def("Release", &BasicAnimationObject::Release)
		];
	}

	AnimationController::AnimationController(){}
	AnimationController::AnimationController(const GenericLuaObject& v) : GenericLuaObject(v){}
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

				 if(key == Keys::AnimationController::BASICANIMATION)	{ animationID = luabind::object_cast<BasicAnimationObject>(*it).GetID(); }
			else if(key == Keys::AnimationController::ROOTNODE)			{ rootNode = luabind::object_cast<LuaNode::Node>(*it); }
			else if(key == Keys::AnimationController::SPEED)			{ speed = luabind::object_cast<double>(*it); }
		}

		if(animationID.empty())
			Logger::LogError(Keys::AnimationController::BASICANIMATION + " is a mandatory field in AnimationController");
		if(!rootNode.node)
			Logger::LogError(Keys::AnimationController::ROOTNODE + " is a mandatory field in AnimationController");

		this->ID = Components::Animation->AnimationControllerFactory()->Create(animationID, rootNode.node, speed);
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

			if(key == Keys::AnimationController::BASICANIMATION)	{ animationID = luabind::object_cast<BasicAnimationObject>(*it).GetID(); }
			else if(key == Keys::AnimationController::TRANSITIONTYPE)	{ transitionType = luabind::object_cast<int>(*it); }
			else if(key == Keys::AnimationController::TRANSITIONLENGTH)	{ transitionLength = luabind::object_cast<double>(*it); }
			else if(key == Keys::AnimationController::STARTONNEXTPHASE)	{ startonNextPhase = luabind::object_cast<bool>(*it); }
		}

		if(animationID.empty())
			Logger::LogError(Keys::AnimationController::BASICANIMATION + " is a mandatory field in AnimationController::ChangeAnimation");

		iAnimationControllerFactory::TransitionType t = static_cast<iAnimationControllerFactory::TransitionType>(transitionType);
		Components::Animation->AnimationControllerFactory()->ChangeAnimation(this->ID, animationID, t, transitionLength, startonNextPhase);
	}
	void AnimationController::ChangeSpeed(double speed)
	{
		Components::Animation->AnimationControllerFactory()->ChangeSpeed(this->ID, speed);
	}
	std::string AnimationController::AddMinorAnimation(luabind::object const& table)
	{
		if(luabind::type(table) != LUA_TTABLE)
			Logger::LogError("Wrong paramter for AnimationController, please send in a table");

		std::string animationID;
		std::string startNodeName;
		double startRatio = 1.0;
		double stepRatio = 0.0;


		for(luabind::iterator it(table);
			it != luabind::iterator();
			++it)
		{
			std::string key = luabind::object_cast<std::string>(it.key());

				 if(key == Keys::AnimationController::BASICANIMATION)	{ animationID = luabind::object_cast<BasicAnimationObject>(*it).GetID(); }
			else if(key == Keys::AnimationController::STARTNODENAME)	{ startNodeName = luabind::object_cast<std::string>(*it); }
			else if(key == Keys::AnimationController::STARTRATIO)		{ startRatio = luabind::object_cast<double>(*it); }
			else if(key == Keys::AnimationController::STEPRATIO)		{ stepRatio = luabind::object_cast<double>(*it); }
		}

		if(animationID.empty())
			Logger::LogError(Keys::AnimationController::BASICANIMATION + " is a mandatory field in AnimationController::AddMinorAnimation");
		if(startNodeName.empty())
			Logger::LogError(Keys::AnimationController::STARTNODENAME + " is a mandatory field in AnimationController::AddMinorAnimation");

		std::string newMinorID = Components::Animation->AnimationControllerFactory()->AddMinorAnimation(this->ID, animationID, startNodeName, startRatio, stepRatio);
		return newMinorID;
	}
	void AnimationController::RemoveMinorAnimation(std::string MinorAnimationID)
	{
		Components::Animation->AnimationControllerFactory()->RemoveMinorAnimation(this->ID, MinorAnimationID);
	}
	void AnimationController::Release()
	{
		Components::Animation->AnimationControllerFactory()->Release(this->ID);
		this->ID = "";
	}
	void AnimationController::Register(lua_State *lua)
	{
		luabind::module(lua)[
			luabind::class_<AnimationController, GenericLuaObject>("AnimationController")
				.def(luabind::constructor<const GenericLuaObject&>())
				.def(luabind::constructor<luabind::object const&>())
				.def("ChangeAnimation", &AnimationController::ChangeAnimation)
				.def("ChangeSpeed", &AnimationController::ChangeSpeed)
				.def("AddMinorAnimation", &AnimationController::AddMinorAnimation)
				.def("RemoveMinorAnimation", &AnimationController::RemoveMinorAnimation)
				.def("Release", &AnimationController::Release)
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
