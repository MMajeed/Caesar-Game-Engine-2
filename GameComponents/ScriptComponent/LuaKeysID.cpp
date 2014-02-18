#include "LuaKeysID.h"

#include <luabind\luabind.hpp>

#include <Keys.h>

void LuaKeysID::Register(lua_State *lua)
{
	luabind::object luaKeyTable = luabind::newtable(lua);
	
	luaKeyTable[Keys::ID]    = Keys::ID;
	luaKeyTable[Keys::Class] = Keys::Class;

	luabind::object classTable = luabind::newtable(lua);
		classTable[Keys::ClassType::Object]      = Keys::ClassType::Object;
		classTable[Keys::ClassType::Camera]      = Keys::ClassType::Camera;
		classTable[Keys::ClassType::Prespective] = Keys::ClassType::Prespective;
		classTable[Keys::ClassType::WindowInfo]  = Keys::ClassType::WindowInfo;
		classTable[Keys::ClassType::Light]       = Keys::ClassType::Light;
	luaKeyTable["Class"] = classTable;

	luabind::object lightTable = luabind::newtable(lua);
		lightTable[Keys::Light::LIGHTTYPE] = Keys::Light::LIGHTTYPE;
		luabind::object lightTypeTable       = luabind::newtable(lua);
			lightTypeTable[Keys::Light::LightTypes::DIRECTIONAL] = Keys::Light::LightTypes::DIRECTIONAL;
			lightTypeTable[Keys::Light::LightTypes::POINT]       = Keys::Light::LightTypes::POINT;
			lightTypeTable[Keys::Light::LightTypes::SPOT]        = Keys::Light::LightTypes::SPOT;
		lightTable["Types"]                  = lightTypeTable;
		lightTable[Keys::Light::DIFFUSE]     = Keys::Light::DIFFUSE;
		lightTable[Keys::Light::AMBIENT]     = Keys::Light::AMBIENT;
		lightTable[Keys::Light::SPECULAR]    = Keys::Light::SPECULAR;
		lightTable[Keys::Light::DIRECTION]   = Keys::Light::DIRECTION;
		lightTable[Keys::Light::RANGE]       = Keys::Light::RANGE;
		lightTable[Keys::Light::ATTENUATION] = Keys::Light::ATTENUATION;
		lightTable[Keys::Light::SPOT]        = Keys::Light::SPOT;
		lightTable[Keys::Light::POSITION]    = Keys::Light::POSITION;
		lightTable[Keys::Light::HASHADOW]    = Keys::Light::HASHADOW;
	luaKeyTable["Light"] = lightTable;

	luabind::object windowTable = luabind::newtable(lua);
		windowTable[Keys::Window::WIDTH]  = Keys::Window::WIDTH;
		windowTable[Keys::Window::HEIGHT] = Keys::Window::HEIGHT;
		windowTable[Keys::Window::HWND]   = Keys::Window::HWND;
	luaKeyTable["Window"] = windowTable;

	luabind::object cameraTable = luabind::newtable(lua);
		cameraTable[Keys::Camera::EYE]               = Keys::Camera::EYE;
		cameraTable[Keys::Camera::TARGETMAGNITUDE]   = Keys::Camera::TARGETMAGNITUDE;
		cameraTable[Keys::Camera::UP]                = Keys::Camera::UP;
		cameraTable[Keys::Camera::RADIANROLL]        = Keys::Camera::RADIANROLL;
		cameraTable[Keys::Camera::RADIANPITCH]       = Keys::Camera::RADIANPITCH;
		cameraTable[Keys::Camera::RADIANYAW]         = Keys::Camera::RADIANYAW;
		cameraTable[Keys::Camera::FOVANGLE]          = Keys::Camera::FOVANGLE;
		cameraTable[Keys::Camera::NEARZ]             = Keys::Camera::NEARZ;
		cameraTable[Keys::Camera::FARZ]              = Keys::Camera::FARZ;
		cameraTable[Keys::Camera::CLEARCOLOR]        = Keys::Camera::CLEARCOLOR;
		cameraTable[Keys::Camera::PROCESS2D]	     = Keys::Camera::PROCESS2D;
		cameraTable[Keys::Camera::GLOBAL2DTEXTURE]   = Keys::Camera::GLOBAL2DTEXTURE;
		cameraTable[Keys::Camera::GLOBALCUBETEXTURE] = Keys::Camera::GLOBALCUBETEXTURE;
		cameraTable[Keys::Camera::GLOBALUSERDATA]    = Keys::Camera::GLOBALUSERDATA;
		cameraTable[Keys::Camera::INCLUSIONSTATE]    = Keys::Camera::INCLUSIONSTATE;
		cameraTable[Keys::Camera::OBJECTLIST]        = Keys::Camera::OBJECTLIST;
	luaKeyTable["Camera"] = cameraTable;

	luabind::object BasicDrawableTable = luabind::newtable(lua);
		BasicDrawableTable[Keys::BasicDrawable::DRAWABLEOBJ]            = Keys::BasicDrawable::DRAWABLEOBJ;
		BasicDrawableTable[Keys::BasicDrawable::MODEL]                  = Keys::BasicDrawable::MODEL;
		BasicDrawableTable[Keys::BasicDrawable::VERTEXSHADERFILE]       = Keys::BasicDrawable::VERTEXSHADERFILE;
		BasicDrawableTable[Keys::BasicDrawable::PIXELSHADERFILE]        = Keys::BasicDrawable::PIXELSHADERFILE;
		BasicDrawableTable[Keys::BasicDrawable::GEOMETRYSHADERFILE]     = Keys::BasicDrawable::GEOMETRYSHADERFILE;
		BasicDrawableTable[Keys::BasicDrawable::CULLMODE]               = Keys::BasicDrawable::CULLMODE;
		BasicDrawableTable[Keys::BasicDrawable::FILLMODE]               = Keys::BasicDrawable::FILLMODE;
		BasicDrawableTable[Keys::BasicDrawable::DIMENSION]		        = Keys::BasicDrawable::DIMENSION;
	luaKeyTable["BasicDrawable"] = BasicDrawableTable;

	luabind::object BasicTextureTable = luabind::newtable(lua);
		BasicTextureTable[Keys::BasicTexture::TEXTUREFILE] = Keys::BasicTexture::TEXTUREFILE;
		BasicTextureTable[Keys::BasicTexture::TEXTUREOBJ]  = Keys::BasicTexture::TEXTUREOBJ;
	luaKeyTable["BasicTexture"] = BasicTextureTable;

	luabind::object ObjectInfoTable = luabind::newtable(lua);
		ObjectInfoTable[Keys::ObjectInfo::LOCATION]       = Keys::ObjectInfo::LOCATION;
		ObjectInfoTable[Keys::ObjectInfo::ROTATION]       = Keys::ObjectInfo::ROTATION;
		ObjectInfoTable[Keys::ObjectInfo::SCALE]          = Keys::ObjectInfo::SCALE;
		ObjectInfoTable[Keys::ObjectInfo::DIFFUSE]        = Keys::ObjectInfo::DIFFUSE;
		ObjectInfoTable[Keys::ObjectInfo::AMBIENT]        = Keys::ObjectInfo::AMBIENT;
		ObjectInfoTable[Keys::ObjectInfo::SPECULAR]       = Keys::ObjectInfo::SPECULAR;
		ObjectInfoTable[Keys::ObjectInfo::DRAWABLEOBJ]    = Keys::ObjectInfo::DRAWABLEOBJ;
		ObjectInfoTable[Keys::ObjectInfo::TEXTURE2DOBJ]   = Keys::ObjectInfo::TEXTURE2DOBJ;
		ObjectInfoTable[Keys::ObjectInfo::TEXTURECUBEOBJ] = Keys::ObjectInfo::TEXTURECUBEOBJ;
		ObjectInfoTable[Keys::ObjectInfo::LIGHT]          = Keys::ObjectInfo::LIGHT;
		ObjectInfoTable[Keys::ObjectInfo::SHADOW]         = Keys::ObjectInfo::SHADOW;
		ObjectInfoTable[Keys::ObjectInfo::DEPTH]          = Keys::ObjectInfo::DEPTH;
		ObjectInfoTable[Keys::ObjectInfo::OBJUSERDATA]    = Keys::ObjectInfo::OBJUSERDATA;
		ObjectInfoTable[Keys::ObjectInfo::ANIMATIONJOINT] = Keys::ObjectInfo::ANIMATIONJOINT;
		ObjectInfoTable[Keys::ObjectInfo::RIGIDBODY]	  = Keys::ObjectInfo::RIGIDBODY;
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
		RigidBody[Keys::RigidBody::FRICTION]       = Keys::RigidBody::FRICTION;
	luaKeyTable["RigidBody"] = RigidBody;

	luabind::globals(lua)["Keys"] = luaKeyTable;
}