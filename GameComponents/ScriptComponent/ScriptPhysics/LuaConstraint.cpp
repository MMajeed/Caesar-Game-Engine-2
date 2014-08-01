#include "LuaConstraint.h"
#include <PhysicsCommunicator\ConstraintConfig.h>
#include <Keys.h>
#include <Logger.h>

namespace LuaConstraint
{
	// ----------------------------------- Start BallSocket ---------------------------
	BallSocket::BallSocket(luabind::object const& table)
	{
		std::string RigidBodyIDA;
		CML::Vec4 PivotPointA;
		std::string RigidBodyIDB;
		CML::Vec4 PivotPointB;
		double breakingThreshold = 1000000.0;

		if(luabind::type(table) != LUA_TTABLE)
			Logger::LogError("Wrong paramter for BallSocket, please send in a table");

		for(luabind::iterator it(table);
			it != luabind::iterator();
			++it)
		{
			std::string key = luabind::object_cast<std::string>(it.key());

				 if(key == Keys::Constraint::RIGIDBODYA)		{ RigidBodyIDA = luabind::object_cast<LuaRigidBody::RididBody>(*it).GetID(); }
			else if(key == Keys::Constraint::PIVOTPOINTA)		{ PivotPointA = luabind::object_cast<LuaMath::Vector4>(*it); }
			else if(key == Keys::Constraint::RIGIDBODYB)		{ RigidBodyIDB = luabind::object_cast<LuaRigidBody::RididBody>(*it).GetID(); }
			else if(key == Keys::Constraint::PIVOTPOINTB)		{ PivotPointB = luabind::object_cast<LuaMath::Vector4>(*it); }
			else if(key == Keys::Constraint::BREAKINGTHRESHOLD)	{ breakingThreshold = luabind::object_cast<double>(*it); }
		}
		
		if(RigidBodyIDA.empty())	Logger::LogError(Keys::Constraint::RIGIDBODYA + " is mandetory paramter in BallSocket");
		
		if(RigidBodyIDB.empty())
		{
			this->ID = ConstraintConfig::CreateBallSocket(RigidBodyIDA, PivotPointA, breakingThreshold);
		}
		else
		{
			this->ID = ConstraintConfig::CreateBallSocket(RigidBodyIDA, PivotPointA, RigidBodyIDB, PivotPointB, breakingThreshold);
		}
	}
	void BallSocket::Release()
	{
		ConstraintConfig::Release(this->ID);
	}
	void BallSocket::Register(lua_State *lua)
	{
		luabind::module(lua)[
			luabind::class_<LuaConstraint::BallSocket, GenericLuaObject>("BallSocket")
				.def(luabind::constructor<luabind::object const&>())
				.def("Release", &LuaConstraint::BallSocket::Release)
		];
	}
	// ----------------------------------- End BallSocket ---------------------------

	// ----------------------------------- Start Hinge ---------------------------
	Hinge::Hinge(luabind::object const& table)
	{
		std::string RigidBodyIDA; CML::Vec3 PivotPointA; CML::Vec3 AxesA;
		std::string RigidBodyIDB; CML::Vec3 PivotPointB; CML::Vec3 AxesB;
		double BreakingThreshold = 1000000.0;
		double Low = 1; double High = -1;
		double Softness = 0.9;
		double BiasFactor = 0.3f; double RelaxationFactor = 1.0f;
		double MaxMotorImpulse = 0.0f;

		if(luabind::type(table) != LUA_TTABLE)
			Logger::LogError("Wrong paramter for Hinge, please send in a table");

		for(luabind::iterator it(table);
			it != luabind::iterator();
			++it)
		{
			std::string key = luabind::object_cast<std::string>(it.key());

				 if(key == Keys::Constraint::RIGIDBODYA)		{ RigidBodyIDA = luabind::object_cast<LuaRigidBody::RididBody>(*it).GetID(); }
			else if(key == Keys::Constraint::PIVOTPOINTA)		{ PivotPointA = luabind::object_cast<LuaMath::Vector4>(*it).vector; }
			else if(key == Keys::Constraint::AXESA)				{ AxesA = luabind::object_cast<LuaMath::Vector4>(*it).vector; }
			else if(key == Keys::Constraint::RIGIDBODYB)		{ RigidBodyIDB = luabind::object_cast<LuaRigidBody::RididBody>(*it).GetID(); }
			else if(key == Keys::Constraint::PIVOTPOINTB)		{ PivotPointB = luabind::object_cast<LuaMath::Vector4>(*it).vector; }
			else if(key == Keys::Constraint::AXESB)				{ AxesB = luabind::object_cast<LuaMath::Vector4>(*it).vector; }
			else if(key == Keys::Constraint::BREAKINGTHRESHOLD)	{ BreakingThreshold = luabind::object_cast<double>(*it); }
			else if(key == Keys::Constraint::LOW)				{ Low = luabind::object_cast<double>(*it); }
			else if(key == Keys::Constraint::HIGH)				{ High = luabind::object_cast<double>(*it); }
			else if(key == Keys::Constraint::SOFTNESS)			{ Softness = luabind::object_cast<double>(*it); }
			else if(key == Keys::Constraint::BIASFACTOR)		{ BiasFactor = luabind::object_cast<double>(*it); }
			else if(key == Keys::Constraint::RELEXATIONFACTOR)	{ RelaxationFactor = luabind::object_cast<double>(*it); }
			else if(key == Keys::Constraint::MAXMOTORIMPULSE)	{ MaxMotorImpulse = luabind::object_cast<double>(*it); }
		}

		if(RigidBodyIDA.empty())	Logger::LogError(Keys::Constraint::RIGIDBODYA + " is mandetory paramter in Hinge");

		if(RigidBodyIDB.empty())
		{
			this->ID = ConstraintConfig::CreateHinge(RigidBodyIDA, PivotPointA, AxesA,
													 BreakingThreshold,
													 Low, High,
													 Softness,
													 BiasFactor, RelaxationFactor, 
													 MaxMotorImpulse);
		}
		else
		{
			this->ID = ConstraintConfig::CreateHinge(RigidBodyIDA, PivotPointA, AxesA, 
													 RigidBodyIDB, PivotPointB, AxesB, 
													 BreakingThreshold,
													 Low, High,
													 Softness,
													 BiasFactor, RelaxationFactor,
													 MaxMotorImpulse);
		}
	}
	void Hinge::Release()
	{
		ConstraintConfig::Release(this->ID);
	}
	void Hinge::Register(lua_State *lua)
	{
		luabind::module(lua)[
			luabind::class_<LuaConstraint::Hinge, GenericLuaObject>("Hinge")
				.def(luabind::constructor<luabind::object const&>())
				.def("Release", &LuaConstraint::Hinge::Release)
		];
	}
	// ----------------------------------- End Hinge ---------------------------

	void RegisterAllLuaFunction(lua_State *lua)
	{
		BallSocket::Register(lua);
		Hinge::Register(lua);
	}
}
