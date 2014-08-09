#include "LuaKeysID.h"

#include <luabind\luabind.hpp>

#include <Keys.h>

namespace LuaKeysID
{
	void Register(lua_State *lua)
	{
		luabind::object luaKeyTable = luabind::newtable(lua);
	
		luabind::object cameraTable = luabind::newtable(lua);
			cameraTable[Keys::Camera::EYE]               = Keys::Camera::EYE;
			cameraTable[Keys::Camera::TARGETMAGNITUDE]   = Keys::Camera::TARGETMAGNITUDE;
			cameraTable[Keys::Camera::UP]                = Keys::Camera::UP;
			cameraTable[Keys::Camera::ROLL]              = Keys::Camera::ROLL;
			cameraTable[Keys::Camera::PITCH]             = Keys::Camera::PITCH;
			cameraTable[Keys::Camera::YAW]               = Keys::Camera::YAW;
			cameraTable[Keys::Camera::FOVANGLE]          = Keys::Camera::FOVANGLE;
			cameraTable[Keys::Camera::NEARZ]             = Keys::Camera::NEARZ;
			cameraTable[Keys::Camera::FARZ]              = Keys::Camera::FARZ;
			cameraTable[Keys::Camera::CLEARCOLOR]        = Keys::Camera::CLEARCOLOR;
			cameraTable[Keys::Camera::GLOBAL2DTEXTURE]   = Keys::Camera::GLOBAL2DTEXTURE;
			cameraTable[Keys::Camera::GLOBALCUBETEXTURE] = Keys::Camera::GLOBALCUBETEXTURE;
			cameraTable[Keys::Camera::GLOBALUSERDATA]    = Keys::Camera::GLOBALUSERDATA;
			cameraTable[Keys::Camera::INCLUSIONSTATE]    = Keys::Camera::INCLUSIONSTATE;
			cameraTable[Keys::Camera::INCLUSIONLIST]     = Keys::Camera::INCLUSIONLIST;
		luaKeyTable["Camera"] = cameraTable;
		
		luabind::object BasicTextureTable = luabind::newtable(lua);
			BasicTextureTable[Keys::BasicTexture::TEXTUREFILE] = Keys::BasicTexture::TEXTUREFILE;
			BasicTextureTable[Keys::BasicTexture::TEXTUREOBJ]  = Keys::BasicTexture::TEXTUREOBJ;
		luaKeyTable["BasicTexture"] = BasicTextureTable;

		luabind::object ObjectInfoTable = luabind::newtable(lua);
			ObjectInfoTable[Keys::ObjectInfo::LOCATION]       = Keys::ObjectInfo::LOCATION;
			ObjectInfoTable[Keys::ObjectInfo::ROTATION]       = Keys::ObjectInfo::ROTATION;
			ObjectInfoTable[Keys::ObjectInfo::SCALE]          = Keys::ObjectInfo::SCALE;
			ObjectInfoTable[Keys::ObjectInfo::DEPTH]          = Keys::ObjectInfo::DEPTH;
			ObjectInfoTable[Keys::ObjectInfo::PRIORITY]       = Keys::ObjectInfo::PRIORITY;
			ObjectInfoTable[Keys::ObjectInfo::GRAPHICMODEL]   = Keys::ObjectInfo::GRAPHICMODEL;
			ObjectInfoTable[Keys::ObjectInfo::VERTEXSHADER]   = Keys::ObjectInfo::VERTEXSHADER;
			ObjectInfoTable[Keys::ObjectInfo::GEOMETRYSHADER] = Keys::ObjectInfo::GEOMETRYSHADER;
			ObjectInfoTable[Keys::ObjectInfo::PIXELSHADER]    = Keys::ObjectInfo::PIXELSHADER;
			ObjectInfoTable[Keys::ObjectInfo::ANIMATIONOBJ]   = Keys::ObjectInfo::ANIMATIONOBJ;
			ObjectInfoTable[Keys::ObjectInfo::ANIMATIONJOINT] = Keys::ObjectInfo::ANIMATIONJOINT;
			ObjectInfoTable[Keys::ObjectInfo::RIGIDBODY]      = Keys::ObjectInfo::RIGIDBODY;
			ObjectInfoTable[Keys::ObjectInfo::TEXTURE]        = Keys::ObjectInfo::TEXTURE;
			ObjectInfoTable[Keys::ObjectInfo::GROUP]          = Keys::ObjectInfo::GROUP;
			ObjectInfoTable[Keys::ObjectInfo::USERDATA]       = Keys::ObjectInfo::USERDATA;
			ObjectInfoTable[Keys::ObjectInfo::FILLMODE]       = Keys::ObjectInfo::FILLMODE;
			ObjectInfoTable[Keys::ObjectInfo::CULLMODE]       = Keys::ObjectInfo::CULLMODE;
		luaKeyTable["ObjectInfo"] = ObjectInfoTable;

		luabind::object BasicScreenShot = luabind::newtable(lua);
			BasicScreenShot[Keys::ScreenShot::ScreenShotOBJ] = Keys::ScreenShot::ScreenShotOBJ;
			BasicScreenShot[Keys::ScreenShot::WIDTH]         = Keys::ScreenShot::WIDTH;
			BasicScreenShot[Keys::ScreenShot::HEIGHT]        = Keys::ScreenShot::HEIGHT;
			BasicScreenShot[Keys::ScreenShot::CAMERAID]		 = Keys::ScreenShot::CAMERAID;
		luaKeyTable["ScreenShot"] = BasicScreenShot;

		luabind::object AnimationController = luabind::newtable(lua);
			AnimationController[Keys::AnimationController::BASICANIMATION]   = Keys::AnimationController::BASICANIMATION;
			AnimationController[Keys::AnimationController::ROOTNODE]		 = Keys::AnimationController::ROOTNODE;
			AnimationController[Keys::AnimationController::SPEED]            = Keys::AnimationController::SPEED;
			AnimationController[Keys::AnimationController::TRANSITIONTYPE]   = Keys::AnimationController::TRANSITIONTYPE;
			AnimationController[Keys::AnimationController::TRANSITIONLENGTH] = Keys::AnimationController::TRANSITIONLENGTH;
			AnimationController[Keys::AnimationController::STARTONNEXTPHASE] = Keys::AnimationController::STARTONNEXTPHASE;
			AnimationController[Keys::AnimationController::STARTNODENAME]    = Keys::AnimationController::STARTNODENAME;
			AnimationController[Keys::AnimationController::STARTRATIO]       = Keys::AnimationController::STARTRATIO;
			AnimationController[Keys::AnimationController::STEPRATIO]        = Keys::AnimationController::STEPRATIO;
		luaKeyTable["AnimationController"] = AnimationController;

		luabind::object RigidBody = luabind::newtable(lua);
			RigidBody[Keys::RigidBody::POSITION]       = Keys::RigidBody::POSITION;
			RigidBody[Keys::RigidBody::ROTATION]       = Keys::RigidBody::ROTATION;
			RigidBody[Keys::RigidBody::INERTIA]        = Keys::RigidBody::INERTIA;
			RigidBody[Keys::RigidBody::MASS]           = Keys::RigidBody::MASS;
			RigidBody[Keys::RigidBody::COLLISIONSHAPE] = Keys::RigidBody::COLLISIONSHAPE;
		luaKeyTable["RigidBody"] = RigidBody;

		luabind::object Constraint = luabind::newtable(lua);
			Constraint[Keys::Constraint::RIGIDBODYA]        = Keys::Constraint::RIGIDBODYA;
			Constraint[Keys::Constraint::PIVOTPOINTA]       = Keys::Constraint::PIVOTPOINTA;
			Constraint[Keys::Constraint::AXESA]             = Keys::Constraint::AXESA;
			Constraint[Keys::Constraint::RIGIDBODYB]        = Keys::Constraint::RIGIDBODYB;
			Constraint[Keys::Constraint::PIVOTPOINTB]       = Keys::Constraint::PIVOTPOINTB;
			Constraint[Keys::Constraint::AXESB]             = Keys::Constraint::AXESB;
			Constraint[Keys::Constraint::BREAKINGTHRESHOLD] = Keys::Constraint::BREAKINGTHRESHOLD;
			Constraint[Keys::Constraint::LOW]               = Keys::Constraint::LOW;
			Constraint[Keys::Constraint::HIGH]              = Keys::Constraint::HIGH;
			Constraint[Keys::Constraint::SOFTNESS]          = Keys::Constraint::SOFTNESS;
			Constraint[Keys::Constraint::BIASFACTOR]        = Keys::Constraint::BIASFACTOR;
			Constraint[Keys::Constraint::RELEXATIONFACTOR]  = Keys::Constraint::RELEXATIONFACTOR;
			Constraint[Keys::Constraint::MAXMOTORIMPULSE]   = Keys::Constraint::MAXMOTORIMPULSE;
		luaKeyTable["Constraint"] = Constraint;

		luabind::globals(lua)["Keys"] = luaKeyTable;
	}

	void RegisterAllLuaFunction(lua_State *lua)
	{
		LuaKeysID::Register(lua);
	}
}