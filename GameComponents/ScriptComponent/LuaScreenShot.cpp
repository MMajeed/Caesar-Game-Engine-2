#include "LuaScreenShot.h"
#include <luabind\luabind.hpp>
#include <GraphicCommunicator\ScreenShotConfig.h>
#include <Keys.h>
#include "LuaMath.h"
#include "LuaCamera.h"

LuaBasicTexture LuaScreenShot::TakeScreenSnapShot(luabind::object const& table)
{
	LuaBasicTexture returnValue;

	unsigned int width = 1028;
	unsigned int height = 1028;
	std::string cameraID;

	if (luabind::type(table) == LUA_TTABLE)
	{
		for (luabind::iterator it(table);
			it != luabind::iterator();
			++it)
		{
			std::string key = luabind::object_cast<std::string>(it.key());

				 if(key == Keys::ScreenShot::WIDTH)			{ width = luabind::object_cast<int>(*it); }
				 else if(key == Keys::ScreenShot::HEIGHT)	{ height = luabind::object_cast<int>(*it); }
				 else if(key == Keys::ScreenShot::CAMERAID)	{ cameraID = luabind::object_cast<LuaCamera>(*it).ID; }
		}
	}

	std::string textureID = ScreenShotConfig::Basic(width, height, cameraID);
	LuaBasicTexture texture;
	texture.ID = textureID;
	return texture;
}

LuaBasicTexture LuaScreenShot::TakeDepthSnapShot(luabind::object const& table)
{
	LuaBasicTexture returnValue;

	unsigned int width = 1028;
	unsigned int height = 1028;
	std::string cameraID;

	if(luabind::type(table) == LUA_TTABLE)
	{
		for(luabind::iterator it(table);
			it != luabind::iterator();
			++it)
		{
			std::string key = luabind::object_cast<std::string>(it.key());

			if(key == Keys::ScreenShot::WIDTH)				{ width = luabind::object_cast<int>(*it); }
			else if(key == Keys::ScreenShot::HEIGHT)				{ height = luabind::object_cast<int>(*it); }
			else if(key == Keys::ScreenShot::CAMERAID)	{ cameraID = luabind::object_cast<LuaCamera>(*it).ID; }
		}
	}

	std::string textureID = ScreenShotConfig::Depth(width, height, cameraID);
	LuaBasicTexture texture;
	texture.ID = textureID;
	return texture;
}

LuaBasicTexture LuaScreenShot::TakeCubeSnapShot(luabind::object const& table)
{
	LuaBasicTexture returnValue;

	unsigned int width = 1028;
	unsigned int height = 1028;
	std::string cameraID;

	if(luabind::type(table) == LUA_TTABLE)
	{
		for(luabind::iterator it(table);
			it != luabind::iterator();
			++it)
		{
			std::string key = luabind::object_cast<std::string>(it.key());

			if(key == Keys::ScreenShot::WIDTH)		{ width = luabind::object_cast<int>(*it); }
			else if(key == Keys::ScreenShot::HEIGHT){ height = luabind::object_cast<int>(*it); }
			else if(key == Keys::ScreenShot::CAMERAID)	{ cameraID = luabind::object_cast<LuaCamera>(*it).ID; }
		}
	}

	std::string textureID = ScreenShotConfig::Cube(width, height, cameraID);
	LuaBasicTexture texture;
	texture.ID = textureID;
	return texture;
}

void LuaScreenShot::Register(lua_State *lua)
{
	luabind::module(lua)[
		luabind::def("TakeScreenShot", LuaScreenShot::TakeScreenSnapShot)
		,luabind::def("TakeDepthScreenShot", LuaScreenShot::TakeDepthSnapShot)
		,luabind::def("TakeCubeScreenShot", LuaScreenShot::TakeCubeSnapShot)
	];
}