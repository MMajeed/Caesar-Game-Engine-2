#include "LuaContinuousScreenCapture.h"
#include <luabind\luabind.hpp>
#include <GraphicCommunicator\ContinuousDepthScreenShotConfig.h>
#include <GraphicCommunicator\ContinuousCubeScreenShotConfig.h>
#include <GraphicCommunicator\ContinuousBasicScreenShotConfig.h>
#include <GraphicCommunicator\GraphicCommunicator.h>
#include <Keys.h>
#include "LuaMath.h"
#include <3DMath.h>

LuaContinuousScreenCapture::ContinuousBasicScreenCapture::ContinuousBasicScreenCapture(luabind::object const& table)
{
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

	std::shared_ptr<ContinuousBasicScreenShotConfig::AddContinuousBasicScreenShot> msg(
		new ContinuousBasicScreenShotConfig::AddContinuousBasicScreenShot(width, height, camera, prespective));

	GraphicCommunicator::SubmitMessage(msg);

	this->ID = msg->ID;
	this->TextureID = msg->newTextureID;
}

void LuaContinuousScreenCapture::ContinuousBasicScreenCapture::SetCameraMatrix(LuaMath::Matrix4x4 mat)
{
	std::shared_ptr<ContinuousBasicScreenShotConfig::ChangeCameraMatrix> msg(
		new ContinuousBasicScreenShotConfig::ChangeCameraMatrix(this->ID, mat));
	GraphicCommunicator::SubmitMessage(msg);
}
void LuaContinuousScreenCapture::ContinuousBasicScreenCapture::SetPrespectiveMatrix(LuaMath::Matrix4x4 mat)
{
	std::shared_ptr<ContinuousBasicScreenShotConfig::ChangePrespectiveMatrix> msg(
		new ContinuousBasicScreenShotConfig::ChangePrespectiveMatrix(this->ID, mat));
	GraphicCommunicator::SubmitMessage(msg);
}
LuaBasicTexture LuaContinuousScreenCapture::ContinuousBasicScreenCapture::GetTexture()
{
	LuaBasicTexture texture;
	texture.ID = this->TextureID;
	return texture;
}

void LuaContinuousScreenCapture::ContinuousBasicScreenCapture::Register(lua_State *lua)
{
	luabind::module(lua)[
		luabind::class_<LuaContinuousScreenCapture::ContinuousBasicScreenCapture>("BasicScreenCapture")
			.def(luabind::constructor<luabind::object const&>())
			.def("SetCamera", &LuaContinuousScreenCapture::ContinuousBasicScreenCapture::SetCameraMatrix)
			.def("SetPrespective", &LuaContinuousScreenCapture::ContinuousBasicScreenCapture::SetPrespectiveMatrix)
			.def("GetTexture", &LuaContinuousScreenCapture::ContinuousBasicScreenCapture::GetTexture)
	];
}

//*******************************************************************//
LuaContinuousScreenCapture::ContinuousDepthScreenCapture::ContinuousDepthScreenCapture(luabind::object const& table)
{
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

	std::shared_ptr<ContinuousDepthScreenShotConfig::AddContinuousDepthScreenShot> msg(
		new ContinuousDepthScreenShotConfig::AddContinuousDepthScreenShot(width, height, camera, prespective));

	GraphicCommunicator::SubmitMessage(msg);

	this->ID = msg->ID;
	this->TextureID = msg->newTextureID;
}

void LuaContinuousScreenCapture::ContinuousDepthScreenCapture::SetCameraMatrix(LuaMath::Matrix4x4 mat)
{
	std::shared_ptr<ContinuousDepthScreenShotConfig::ChangeCameraMatrix> msg(
		new ContinuousDepthScreenShotConfig::ChangeCameraMatrix(this->ID, mat));
	GraphicCommunicator::SubmitMessage(msg);
}
void LuaContinuousScreenCapture::ContinuousDepthScreenCapture::SetPrespectiveMatrix(LuaMath::Matrix4x4 mat)
{
	std::shared_ptr<ContinuousDepthScreenShotConfig::ChangePrespectiveMatrix> msg(
		new ContinuousDepthScreenShotConfig::ChangePrespectiveMatrix(this->ID, mat));
	GraphicCommunicator::SubmitMessage(msg);
}
LuaBasicTexture LuaContinuousScreenCapture::ContinuousDepthScreenCapture::GetTexture()
{
	LuaBasicTexture texture;
	texture.ID = this->TextureID;
	return texture;
}

void LuaContinuousScreenCapture::ContinuousDepthScreenCapture::Register(lua_State *lua)
{
	luabind::module(lua)[
		luabind::class_<LuaContinuousScreenCapture::ContinuousDepthScreenCapture>("DepthScreenCapture")
			.def(luabind::constructor<luabind::object const&>())
			.def("SetCamera", &LuaContinuousScreenCapture::ContinuousDepthScreenCapture::SetCameraMatrix)
			.def("SetPrespective", &LuaContinuousScreenCapture::ContinuousDepthScreenCapture::SetPrespectiveMatrix)
			.def("GetTexture", &LuaContinuousScreenCapture::ContinuousDepthScreenCapture::GetTexture)
	];
}

//*******************************************************************//
LuaContinuousScreenCapture::ContinuousCubeScreenCapture::ContinuousCubeScreenCapture(luabind::object const& table)
{
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

			if(key == Keys::ScreenCapture::WIDTH)				{ width = luabind::object_cast<int>(*it); }
			else if(key == Keys::ScreenCapture::HEIGHT)				{ height = luabind::object_cast<int>(*it); }
			else if(key == Keys::ScreenCapture::EYE)		{ eye = luabind::object_cast<LuaMath::Vector4>(*it); }
		}
	}

	std::shared_ptr<ContinuousCubeScreenShotConfig::AddContinuousCubeScreenShot> msg(
		new ContinuousCubeScreenShotConfig::AddContinuousCubeScreenShot(width, height, eye));

	GraphicCommunicator::SubmitMessage(msg);

	this->ID = msg->ID;
	this->TextureID = msg->newTextureID;
}

void LuaContinuousScreenCapture::ContinuousCubeScreenCapture::SetEye(LuaMath::Vector4 mat)
{
	std::shared_ptr<ContinuousCubeScreenShotConfig::ChangeEye> msg(
		new ContinuousCubeScreenShotConfig::ChangeEye(this->ID, mat));
	GraphicCommunicator::SubmitMessage(msg);
}
LuaBasicTexture LuaContinuousScreenCapture::ContinuousCubeScreenCapture::GetTexture()
{
	LuaBasicTexture texture;
	texture.ID = this->TextureID;
	return texture;
}

void LuaContinuousScreenCapture::ContinuousCubeScreenCapture::Register(lua_State *lua)
{
	luabind::module(lua)[
		luabind::class_<LuaContinuousScreenCapture::ContinuousCubeScreenCapture>("CubeScreenCapture")
			.def(luabind::constructor<luabind::object const&>())
			.def("SetEye", &LuaContinuousScreenCapture::ContinuousCubeScreenCapture::SetEye)
			.def("GetTexture", &LuaContinuousScreenCapture::ContinuousCubeScreenCapture::GetTexture)
	];
}