#include "LuaScreenShot.h"
#include <luabind\luabind.hpp>
#include <GraphicCommunicator\ScreenShotConfig.h>
#include <Keys.h>
#include "LuaMath.h"
#include <3DMath.h>

LuaBasicTexture LuaScreenShot::TakeScreenSnapShot(luabind::object const& table)
{
	LuaBasicTexture returnValue;

	unsigned int width = 1028;
	unsigned int height = 1028;
	CHL::Matrix4x4 camera;
	bool cameraSet = false;
	CHL::Matrix4x4 prespective;
	bool prespectiveSet = false;

	if (luabind::type(table) == LUA_TTABLE)
	{
		for (luabind::iterator it(table);
			it != luabind::iterator();
			++it)
		{
			std::string key = luabind::object_cast<std::string>(it.key());

				 if(key == Keys::ScreenShot::WIDTH)				{ width = luabind::object_cast<int>(*it); }
			else if(key == Keys::ScreenShot::HEIGHT)			{ height = luabind::object_cast<int>(*it); }
			else if(key == Keys::ScreenShot::CAMERAMATRIX)		{ camera = luabind::object_cast<LuaMath::Matrix4x4>(*it);  cameraSet = true;  }
			else if(key == Keys::ScreenShot::PRESPECTIVEMATRIX)	{ prespective = luabind::object_cast<LuaMath::Matrix4x4>(*it);  prespectiveSet = true; }
		}
	}

	if(cameraSet == false)
	{
		CHL::Vec4 eye{0.0, 0.0, 0.0, 0.0};
		CHL::Vec4 TM{0.0, 0.0, 1.0, 0.0};
		CHL::Vec4 up{0.0, 1.0, 0.0, 0.0};
		double roll = 0.0;	double pitch = 0.0;		double yaw = 0.0;

		camera = CHL::ViewCalculation(eye, TM, up, pitch, yaw, roll);
	}
	if(prespectiveSet == false)
	{
		double FovAngleY = 0.785398163;
		double nearZ = 0.01;
		double farZ = 5000.0;
		prespective = CHL::PerspectiveFovLHCalculation(FovAngleY, width / height, nearZ, farZ);
	}

	std::string textureID = ScreenShotConfig::Basic(width, height, camera, prespective);
	LuaBasicTexture texture;
	texture.ID = textureID;
	return texture;
}

LuaBasicTexture LuaScreenShot::TakeDepthSnapShot(luabind::object const& table)
{
	LuaBasicTexture returnValue;

	unsigned int width = 1028;
	unsigned int height = 1028;
	CHL::Matrix4x4 camera;
	bool cameraSet = false;
	CHL::Matrix4x4 prespective;
	bool prespectiveSet = false;

	if(luabind::type(table) == LUA_TTABLE)
	{
		for(luabind::iterator it(table);
			it != luabind::iterator();
			++it)
		{
			std::string key = luabind::object_cast<std::string>(it.key());

			if(key == Keys::ScreenShot::WIDTH)				{ width = luabind::object_cast<int>(*it); }
			else if(key == Keys::ScreenShot::HEIGHT)				{ height = luabind::object_cast<int>(*it); }
			else if(key == Keys::ScreenShot::CAMERAMATRIX)		{ camera = luabind::object_cast<LuaMath::Matrix4x4>(*it);  cameraSet = true; }
			else if(key == Keys::ScreenShot::PRESPECTIVEMATRIX)	{ prespective = luabind::object_cast<LuaMath::Matrix4x4>(*it);  prespectiveSet = true; }
		}
	}

	if(cameraSet == false)
	{
		CHL::Vec4 eye{0.0, 0.0, 0.0, 0.0};
		CHL::Vec4 TM{0.0, 0.0, 1.0, 0.0};
		CHL::Vec4 up{0.0, 1.0, 0.0, 0.0};
		double roll = 0.0;	double pitch = 0.0;		double yaw = 0.0;

		camera = CHL::ViewCalculation(eye, TM, up, pitch, yaw, roll);
	}
	if(prespectiveSet == false)
	{
		double FovAngleY = 0.785398163;
		double nearZ = 1.0;
		double farZ = 50.0;
		prespective = CHL::PerspectiveFovLHCalculation(FovAngleY, width / height, nearZ, farZ);
	}

	std::string textureID = ScreenShotConfig::Depth(width, height, camera, prespective);
	LuaBasicTexture texture;
	texture.ID = textureID;
	return texture;
}

LuaBasicTexture LuaScreenShot::TakeCubeSnapShot(luabind::object const& table)
{
	LuaBasicTexture returnValue;

	unsigned int width = 1028;
	unsigned int height = 1028;
	CHL::Vec4 eye;

	if(luabind::type(table) == LUA_TTABLE)
	{
		for(luabind::iterator it(table);
			it != luabind::iterator();
			++it)
		{
			std::string key = luabind::object_cast<std::string>(it.key());

			if(key == Keys::ScreenShot::WIDTH)		{ width = luabind::object_cast<int>(*it); }
			else if(key == Keys::ScreenShot::HEIGHT)	{ height = luabind::object_cast<int>(*it); }
			else if(key == Keys::ScreenShot::EYE)	{ eye = luabind::object_cast<LuaMath::Vector4>(*it);}
		}
	}

	std::string textureID = ScreenShotConfig::Cube(width, height, eye);
	LuaBasicTexture texture;
	texture.ID = textureID;
	return texture;
}

void LuaScreenShot::Register(lua_State *lua)
{
	luabind::module(lua)[
		luabind::def("TakeScreenShot", LuaScreenShot::TakeScreenSnapShot)
		,luabind::def("TakeDepthScreenShot", LuaScreenShot::TakeDepthSnapShot)
		, luabind::def("TakeCubeScreenShot", LuaScreenShot::TakeCubeSnapShot)
	];
}