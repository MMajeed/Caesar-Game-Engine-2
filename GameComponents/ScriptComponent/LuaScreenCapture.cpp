#include "LuaScreenCapture.h"
#include <luabind\luabind.hpp>
#include <GraphicCommunicator\TakeScreenShot.h>
#include <GraphicCommunicator\GraphicCommunicator.h>
#include <Keys.h>
#include "LuaMath.h"
#include <3DMath.h>

LuaBasicTexture LuaScreenCapture::TakeScreenSnapShot(luabind::object const& table)
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

				 if(key == Keys::ScreenCapture::WIDTH)				{ width = luabind::object_cast<int>(*it); }
			else if(key == Keys::ScreenCapture::HEIGHT)				{ height = luabind::object_cast<int>(*it); }
			else if(key == Keys::ScreenCapture::CAMERAMATRIX)		{ camera = luabind::object_cast<LuaMath::Matrix4x4>(*it);  cameraSet = true;  }
			else if(key == Keys::ScreenCapture::PRESPECTIVEMATRIX)	{ prespective = luabind::object_cast<LuaMath::Matrix4x4>(*it);  prespectiveSet = true; }
		}
	}

	if(cameraSet == false)
	{
		CHL::Vec4 eye;	eye(0) = 0.0; eye(1) = 0.0; eye(2) = 0.0; eye(3) = 0.0;
		CHL::Vec4 TM;	TM(0) = 0.0; TM(1) = 0.0; TM(2) = 1.0; TM(3) = 0.0;
		CHL::Vec4 up;	up(0) = 0.0; up(1) = 1.0; up(2) = 0.0; up(3) = 0.0;
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

	std::shared_ptr<TakeBasicScreenShot> msg(
		new TakeBasicScreenShot(width, height, camera, prespective));

	GraphicCommunicator::SubmitMessage(msg);

	msg->WaitTillProcccesed();

	returnValue.ID = msg->newTextureID;

	return returnValue;
}

LuaBasicTexture LuaScreenCapture::TakeDepthSnapShot(luabind::object const& table)
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

			if(key == Keys::ScreenCapture::WIDTH)				{ width = luabind::object_cast<int>(*it); }
			else if(key == Keys::ScreenCapture::HEIGHT)				{ height = luabind::object_cast<int>(*it); }
			else if(key == Keys::ScreenCapture::CAMERAMATRIX)		{ camera = luabind::object_cast<LuaMath::Matrix4x4>(*it);  cameraSet = true; }
			else if(key == Keys::ScreenCapture::PRESPECTIVEMATRIX)	{ prespective = luabind::object_cast<LuaMath::Matrix4x4>(*it);  prespectiveSet = true; }
		}
	}

	if(cameraSet == false)
	{
		CHL::Vec4 eye;	eye(0) = 0.0; eye(1) = 0.0; eye(2) = 0.0; eye(3) = 0.0;
		CHL::Vec4 TM;	TM(0) = 0.0; TM(1) = 0.0; TM(2) = 1.0; TM(3) = 0.0;
		CHL::Vec4 up;	up(0) = 0.0; up(1) = 1.0; up(2) = 0.0; up(3) = 0.0;
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

	std::shared_ptr<TakeDepthScreenShot> msg(
		new TakeDepthScreenShot(width, height, camera, prespective));

	GraphicCommunicator::SubmitMessage(msg);

	msg->WaitTillProcccesed();

	returnValue.ID = msg->newTextureID;

	return returnValue;
}

LuaBasicTexture LuaScreenCapture::TakeCubeSnapShot(luabind::object const& table)
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

			if(key == Keys::ScreenCapture::WIDTH)		{ width = luabind::object_cast<int>(*it); }
			else if(key == Keys::ScreenCapture::HEIGHT)	{ height = luabind::object_cast<int>(*it); }
			else if(key == Keys::ScreenCapture::EYE)	{ eye = luabind::object_cast<LuaMath::Vector4>(*it);}
		}
	}

	std::shared_ptr<TakeCubeScreenShot> msg(new TakeCubeScreenShot(width, height, eye));

	GraphicCommunicator::SubmitMessage(msg);

	msg->WaitTillProcccesed();

	returnValue.ID = msg->newTextureID;

	return returnValue;
}

void LuaScreenCapture::Register(lua_State *lua)
{
	luabind::module(lua)[
		luabind::def("TakeScreenShot", LuaScreenCapture::TakeScreenSnapShot)
		,luabind::def("TakeDepthScreenShot", LuaScreenCapture::TakeDepthSnapShot)
		, luabind::def("TakeCubeScreenShot", LuaScreenCapture::TakeCubeSnapShot)
	];
}