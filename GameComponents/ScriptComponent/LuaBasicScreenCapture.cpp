#include "LuaBasicScreenCapture.h"
#include <luabind\luabind.hpp>
#include <GraphicCommunicator\BasicScreenCaptureConfig.h>
#include <GraphicCommunicator\GraphicCommunicator.h>
#include <Keys.h>

LuaBasicScreenCapture::LuaBasicScreenCapture(luabind::object const& table)
{
	unsigned int width = 1024;
	unsigned int height = 1024;

	if (luabind::type(table) == LUA_TTABLE)
	{
		for (luabind::iterator it(table);
			it != luabind::iterator();
			++it)
		{
			std::string key = luabind::object_cast<std::string>(it.key());

			     if (key == Keys::BasicScreenCapture::WIDTH)	{ width = luabind::object_cast<int>(*it); }
			else if (key == Keys::BasicScreenCapture::HEIGHT)	{ height = luabind::object_cast<int>(*it); }
		}
	}

	std::shared_ptr<BasicScreenCaptureConfig::AddBasicScreenCaptureMessage> msg(
		new BasicScreenCaptureConfig::AddBasicScreenCaptureMessage(width, height));

	GraphicCommunicator::SubmitMessage(msg);

	this->ID = msg->ID;
}

LuaBasicTexture LuaBasicScreenCapture::TakeSnapShot(luabind::object const& table)
{
	LuaBasicTexture returnValue;

	std::string cameraID;
	std::string prespectiveID;
	
	if (luabind::type(table) != LUA_TTABLE)
	{
		for (luabind::iterator it(table);
			it != luabind::iterator();
			++it)
		{
			std::string key = luabind::object_cast<std::string>(it.key());

			     if (key == Keys::BasicScreenCapture::CAMERAOBJ)		{ cameraID = luabind::object_cast<std::string>(*it); }
			else if (key == Keys::BasicScreenCapture::PRESPECTIVEOBJ)	{ prespectiveID = luabind::object_cast<std::string>(*it); }
		}
	}

	std::shared_ptr<BasicScreenCaptureConfig::SnapPictureMessage> msg(
		new BasicScreenCaptureConfig::SnapPictureMessage(this->ID, cameraID, prespectiveID));

	GraphicCommunicator::SubmitMessage(msg);

	returnValue.ID = msg->newTextureID;

	return returnValue;
}

void LuaBasicScreenCapture::Register(lua_State *lua)
{
	luabind::module(lua)[
		luabind::class_<LuaBasicScreenCapture>("BasicScreenCapture")
			.def(luabind::constructor<luabind::object const&>())
			.def_readonly("ID", &LuaBasicScreenCapture::ID)
			.def("TakeSnapShot", &LuaBasicScreenCapture::TakeSnapShot)
	];
}