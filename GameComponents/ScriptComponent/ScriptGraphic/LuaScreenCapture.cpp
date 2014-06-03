#include "LuaScreenCapture.h"
#include <luabind\luabind.hpp>
#include <GraphicCommunicator\DepthScreenCaptureConfig.h>
#include <GraphicCommunicator\CubeScreenCaptureConfig.h>
#include <GraphicCommunicator\BasicScreenCaptureConfig.h>
#include <Keys.h>
#include "LuaMath.h"
#include <ScriptEntity\LuaCamera.h>

LuaScreenCapture::BasicScreenCapture::BasicScreenCapture(luabind::object const& table)
{
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
			else if(key == Keys::ScreenShot::HEIGHT)	{ height = luabind::object_cast<int>(*it); }
			else if(key == Keys::ScreenShot::CAMERAID)	{ cameraID = luabind::object_cast<LuaCamera>(*it).ID; }
		}
	}
	
	BasicScreenCaptureConfig::Create(width, height, cameraID, this->ID, this->TextureID);
}

void LuaScreenCapture::BasicScreenCapture::SetCameraID(LuaCamera cameraID)
{
	BasicScreenCaptureConfig::SetCameraID(this->ID, cameraID.ID);
}
LuaBasicTexture LuaScreenCapture::BasicScreenCapture::GetTexture()
{
	LuaBasicTexture texture;
	texture.ID = this->TextureID;
	return texture;
}
void LuaScreenCapture::BasicScreenCapture::Release()
{
	BasicScreenCaptureConfig::Release(this->ID);	
	this->ID = "";
	this->TextureID = "";
}

void LuaScreenCapture::BasicScreenCapture::Register(lua_State *lua)
{
	luabind::module(lua)[
		luabind::class_<LuaScreenCapture::BasicScreenCapture>("BasicScreenCapture")
			.def(luabind::constructor<luabind::object const&>())
			.def("SetCamera", &LuaScreenCapture::BasicScreenCapture::SetCameraID)
			.def("GetTexture", &LuaScreenCapture::BasicScreenCapture::GetTexture)
			.def("Release", &LuaScreenCapture::BasicScreenCapture::Release)
	];
}

//*******************************************************************//
LuaScreenCapture::DepthScreenCapture::DepthScreenCapture(luabind::object const& table)
{
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
			else if(key == Keys::ScreenShot::HEIGHT)	{ height = luabind::object_cast<int>(*it); }
			else if(key == Keys::ScreenShot::CAMERAID)	{ cameraID = luabind::object_cast<LuaCamera>(*it).ID; }
		}
	}
	
	DepthScreenCaptureConfig::Create(width, height, cameraID, this->ID, this->TextureID);
}

void LuaScreenCapture::DepthScreenCapture::SetCameraID(LuaCamera cameraID)
{
	DepthScreenCaptureConfig::SetCameraID(this->ID, cameraID.ID);
}
LuaBasicTexture LuaScreenCapture::DepthScreenCapture::GetTexture()
{
	LuaBasicTexture texture;
	texture.ID = this->TextureID;
	return texture;
}
void LuaScreenCapture::DepthScreenCapture::Release()
{
	DepthScreenCaptureConfig::Release(this->ID);
	this->ID = "";
	this->TextureID = "";
}

void LuaScreenCapture::DepthScreenCapture::Register(lua_State *lua)
{
	luabind::module(lua)[
		luabind::class_<LuaScreenCapture::DepthScreenCapture>("DepthScreenCapture")
			.def(luabind::constructor<luabind::object const&>())
			.def("SetCamera", &LuaScreenCapture::DepthScreenCapture::SetCameraID)
			.def("GetTexture", &LuaScreenCapture::DepthScreenCapture::GetTexture)
			.def("Release", &LuaScreenCapture::DepthScreenCapture::Release)
	];
}

//*******************************************************************//
LuaScreenCapture::CubeScreenCapture::CubeScreenCapture(luabind::object const& table)
{
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

	CubeScreenCaptureConfig::Create(width, height, cameraID, this->ID, this->TextureID);
}

void LuaScreenCapture::CubeScreenCapture::SetCameraID(LuaCamera cameraID)
{
	CubeScreenCaptureConfig::SetCameraID(this->ID, cameraID.ID);
}
LuaBasicTexture LuaScreenCapture::CubeScreenCapture::GetTexture()
{
	LuaBasicTexture texture;
	texture.ID = this->TextureID;
	return texture;
}
void LuaScreenCapture::CubeScreenCapture::Release()
{
	CubeScreenCaptureConfig::Release(this->ID);
	this->ID = "";
	this->TextureID = "";
}

void LuaScreenCapture::CubeScreenCapture::Register(lua_State *lua)
{
	luabind::module(lua)[
		luabind::class_<LuaScreenCapture::CubeScreenCapture>("CubeScreenCapture")
			.def(luabind::constructor<luabind::object const&>())
			.def("SetCamera", &LuaScreenCapture::CubeScreenCapture::SetCameraID)
			.def("GetTexture", &LuaScreenCapture::CubeScreenCapture::GetTexture)
			.def("Release", &LuaScreenCapture::CubeScreenCapture::Release)
	];
}