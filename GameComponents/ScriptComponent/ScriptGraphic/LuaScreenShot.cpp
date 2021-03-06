#include "LuaScreenShot.h"
#include <luabind\luabind.hpp>
#include <Components.h>
#include <Keys.h>
#include <LuaMath.h>
#include <GenericLuaObject.h>
#include <ScriptManager.h>
#include <Resource.h>

luabind::object LuaScreenShot::TakeScreenSnapShot(luabind::object const& table)
{
	unsigned int width = 1028;
	unsigned int height = 1028;
	std::string cameraID;
	std::string drawSettingsID;
	unsigned int numOfTagrets = 1;

	if (luabind::type(table) == LUA_TTABLE)
	{
		for (luabind::iterator it(table);
			it != luabind::iterator();
			++it)
		{
			std::string key = luabind::object_cast<std::string>(it.key());

				 if(key == Keys::ScreenShot::WIDTH)				{	 width = luabind::object_cast<int>(*it); }
				 else if(key == Keys::ScreenShot::HEIGHT)			{ height = luabind::object_cast<int>(*it); }
				 else if(key == Keys::ScreenShot::CAMERAID)			{ cameraID = luabind::object_cast<GenericLuaObject>(*it).GetID(); }
				 else if(key == Keys::ScreenShot::DRAWSETTINGSID)	{ drawSettingsID = luabind::object_cast<GenericLuaObject>(*it).GetID(); }
				 else if(key == Keys::ScreenShot::NUMOFTARGETS)		{ numOfTagrets = luabind::object_cast<int>(*it); }
		}
	}

	std::vector<std::string> textureID = Components::Graphic->ScreenShotFactory()->Basic(width, height, numOfTagrets, cameraID, drawSettingsID);

	lua_State* lua = Resource::lua;

	luabind::object returnValue;

	if(textureID.size() == 1)
	{
		GenericLuaObject g(textureID[0]);
		LuaBasicTexture texture(g);
		returnValue = luabind::object(lua, texture);
	}
	else
	{
		returnValue = luabind::newtable(lua);

		for(unsigned int i = 0; i < textureID.size(); ++i)
		{
			GenericLuaObject g(textureID[i]);
			LuaBasicTexture texture(g);
			returnValue[i + 1] = texture;
		}
	}

	return returnValue;
}

LuaBasicTexture LuaScreenShot::TakeDepthSnapShot(luabind::object const& table)
{
	LuaBasicTexture returnValue;

	unsigned int width = 1028;
	unsigned int height = 1028;
	std::string cameraID;
	std::string drawSettingsID;

	if(luabind::type(table) == LUA_TTABLE)
	{
		for(luabind::iterator it(table);
			it != luabind::iterator();
			++it)
		{
			std::string key = luabind::object_cast<std::string>(it.key());

			if(key == Keys::ScreenShot::WIDTH)				{ width = luabind::object_cast<int>(*it); }
			else if(key == Keys::ScreenShot::HEIGHT)		{ height = luabind::object_cast<int>(*it); }
			else if(key == Keys::ScreenShot::CAMERAID)		{ cameraID = luabind::object_cast<GenericLuaObject*>(*it)->GetID(); }
			else if(key == Keys::ScreenShot::DRAWSETTINGSID){ drawSettingsID = luabind::object_cast<GenericLuaObject>(*it).GetID(); }

		}
	}

	std::string textureID = Components::Graphic->ScreenShotFactory()->Depth(width, height, cameraID, drawSettingsID);
	GenericLuaObject g(textureID);
	LuaBasicTexture texture(g);
	return texture;
}

LuaBasicTexture LuaScreenShot::TakeCubeSnapShot(luabind::object const& table)
{
	LuaBasicTexture returnValue;

	unsigned int width = 1028;
	unsigned int height = 1028;
	std::string cameraID;
	std::string drawSettingsID;

	if(luabind::type(table) == LUA_TTABLE)
	{
		for(luabind::iterator it(table);
			it != luabind::iterator();
			++it)
		{
			std::string key = luabind::object_cast<std::string>(it.key());

			if(key == Keys::ScreenShot::WIDTH)				{ width = luabind::object_cast<int>(*it); }
			else if(key == Keys::ScreenShot::HEIGHT)		{ height = luabind::object_cast<int>(*it); }
			else if(key == Keys::ScreenShot::CAMERAID)		{ cameraID = luabind::object_cast<GenericLuaObject>(*it).GetID(); }
			else if(key == Keys::ScreenShot::DRAWSETTINGSID){ drawSettingsID = luabind::object_cast<GenericLuaObject>(*it).GetID(); }
		}
	}

	std::string textureID = Components::Graphic->ScreenShotFactory()->Cube(width, height, cameraID, drawSettingsID);
	GenericLuaObject g(textureID);
	LuaBasicTexture texture(g);
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