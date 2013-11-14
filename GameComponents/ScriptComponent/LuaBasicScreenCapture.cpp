#include "LuaBasicScreenCapture.h"
#include <luabind\luabind.hpp>
#include <GraphicCommunicator\TakeBasicScreenShot.h>
#include <GraphicCommunicator\GraphicCommunicator.h>
#include <Keys.h>


LuaBasicTexture LuaBasicScreenCapture::TakeSnapShot(luabind::object const& table)
{
	LuaBasicTexture returnValue;

	std::string cameraID;
	std::string prespectiveID;
	unsigned int width = 1028;
	unsigned int height = 1028;

	if (luabind::type(table) == LUA_TTABLE)
	{
		for (luabind::iterator it(table);
			it != luabind::iterator();
			++it)
		{
			std::string key = luabind::object_cast<std::string>(it.key());

			     if (key == Keys::BasicScreenCapture::CAMERAOBJ)		{ cameraID = luabind::object_cast<std::string>(*it); }
			else if (key == Keys::BasicScreenCapture::PRESPECTIVEOBJ)	{ prespectiveID = luabind::object_cast<std::string>(*it); }
			else if(key == Keys::BasicScreenCapture::WIDTH)				{ width = luabind::object_cast<int>(*it); }
			else if(key == Keys::BasicScreenCapture::HEIGHT)			{ height = luabind::object_cast<int>(*it); }
		}
	}

	std::shared_ptr<TakeBasicScreenShot> msg(
		new TakeBasicScreenShot(width, height, cameraID, prespectiveID));

	GraphicCommunicator::SubmitMessage(msg);

	msg->WaitTillProcccesed();

	returnValue.ID = msg->newTextureID;

	return returnValue;
}

void LuaBasicScreenCapture::Register(lua_State *lua)
{
	luabind::module(lua)[
		luabind::def("TakeScreenShot", LuaBasicScreenCapture::TakeSnapShot)
	];
}