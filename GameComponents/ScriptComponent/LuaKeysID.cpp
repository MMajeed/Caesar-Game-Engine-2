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
		cameraTable[Keys::Camera::EYE]             = Keys::Camera::EYE;
		cameraTable[Keys::Camera::TARGETMAGNITUDE] = Keys::Camera::TARGETMAGNITUDE;
		cameraTable[Keys::Camera::UP]              = Keys::Camera::UP;
		cameraTable[Keys::Camera::RADIANROLL]      = Keys::Camera::RADIANROLL;
		cameraTable[Keys::Camera::RADIANPITCH]     = Keys::Camera::RADIANPITCH;
		cameraTable[Keys::Camera::RADIANYAW]       = Keys::Camera::RADIANYAW;
	luaKeyTable["Camera"] = cameraTable;

	luabind::object prespectiveTable = luabind::newtable(lua);
		prespectiveTable[Keys::Prespective::FOVANGLE]     = Keys::Prespective::FOVANGLE;
		prespectiveTable[Keys::Prespective::SCREENWIDTH]  = Keys::Prespective::SCREENWIDTH;
		prespectiveTable[Keys::Prespective::SCREENHEIGHT] = Keys::Prespective::SCREENHEIGHT;
		prespectiveTable[Keys::Prespective::MINVIEWABLE]  = Keys::Prespective::MINVIEWABLE;
		prespectiveTable[Keys::Prespective::MAXVIEWABLE]  = Keys::Prespective::MAXVIEWABLE;
	luaKeyTable["Prespective"] = prespectiveTable;

	luabind::object BasicDrawableTable = luabind::newtable(lua);
	BasicDrawableTable[Keys::BasicDrawable::DRAWABLEOBJ] = Keys::BasicDrawable::DRAWABLEOBJ;
		BasicDrawableTable[Keys::BasicDrawable::MODELFILE]         = Keys::BasicDrawable::MODELFILE;
		BasicDrawableTable[Keys::BasicDrawable::VERTEXSHADERFILE]  = Keys::BasicDrawable::VERTEXSHADERFILE;
		BasicDrawableTable[Keys::BasicDrawable::PIXELSHADERFILE]   = Keys::BasicDrawable::PIXELSHADERFILE;
		BasicDrawableTable[Keys::BasicDrawable::CULLMODE]          = Keys::BasicDrawable::CULLMODE;
		BasicDrawableTable[Keys::BasicDrawable::FILLMODE]          = Keys::BasicDrawable::FILLMODE;
		BasicDrawableTable[Keys::BasicDrawable::ANTIALIASEDLINE]   = Keys::BasicDrawable::ANTIALIASEDLINE;
		BasicDrawableTable[Keys::BasicDrawable::MULTISAMPLEENABLE] = Keys::BasicDrawable::MULTISAMPLEENABLE;
	luaKeyTable["BasicDrawable"] = BasicDrawableTable;

	luabind::object BasicTextureTable = luabind::newtable(lua);
		BasicTextureTable[Keys::BasicTexture::TEXTUREFILE] = Keys::BasicTexture::TEXTUREFILE;
		BasicTextureTable[Keys::BasicTexture::TEXTUREOBJ]  = Keys::BasicTexture::TEXTUREOBJ;
	luaKeyTable["BasicTexture"] = BasicTextureTable;

	luabind::object ObjectInfoTable = luabind::newtable(lua);
		ObjectInfoTable[Keys::ObjectInfo::LOCATION]    = Keys::ObjectInfo::LOCATION;
		ObjectInfoTable[Keys::ObjectInfo::ROTATION]    = Keys::ObjectInfo::ROTATION;
		ObjectInfoTable[Keys::ObjectInfo::SCALE]       = Keys::ObjectInfo::SCALE;
		ObjectInfoTable[Keys::ObjectInfo::DIFFUSE]     = Keys::ObjectInfo::DIFFUSE;
		ObjectInfoTable[Keys::ObjectInfo::AMBIENT]     = Keys::ObjectInfo::AMBIENT;
		ObjectInfoTable[Keys::ObjectInfo::SPECULAR]    = Keys::ObjectInfo::SPECULAR;
		ObjectInfoTable[Keys::ObjectInfo::DRAWABLEOBJ] = Keys::ObjectInfo::DRAWABLEOBJ;
		ObjectInfoTable[Keys::ObjectInfo::TEXTURE2DOBJ] = Keys::ObjectInfo::TEXTURE2DOBJ;
		ObjectInfoTable[Keys::ObjectInfo::TEXTURECUBEOBJ] = Keys::ObjectInfo::TEXTURECUBEOBJ;
		ObjectInfoTable[Keys::ObjectInfo::LIGHT] = Keys::ObjectInfo::LIGHT;
	luaKeyTable["ObjectInfo"] = ObjectInfoTable;

	luabind::object BasicScreenCapture = luabind::newtable(lua);
		BasicScreenCapture[Keys::ScreenCapture::SCREENCAPTUREOBJ]      = Keys::ScreenCapture::SCREENCAPTUREOBJ;
		BasicScreenCapture[Keys::ScreenCapture::WIDTH] = Keys::ScreenCapture::WIDTH;
		BasicScreenCapture[Keys::ScreenCapture::HEIGHT] = Keys::ScreenCapture::HEIGHT;
		BasicScreenCapture[Keys::ScreenCapture::CAMERAMATRIX] = Keys::ScreenCapture::CAMERAMATRIX;
		BasicScreenCapture[Keys::ScreenCapture::PRESPECTIVEMATRIX] = Keys::ScreenCapture::PRESPECTIVEMATRIX;
		BasicScreenCapture[Keys::ScreenCapture::EYE] = Keys::ScreenCapture::EYE;
	luaKeyTable["ScreenCapture"] = BasicScreenCapture;

	luabind::globals(lua)["Keys"] = luaKeyTable;
}