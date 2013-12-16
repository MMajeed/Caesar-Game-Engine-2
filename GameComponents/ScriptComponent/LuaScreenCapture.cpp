#include "LuaScreenCapture.h"
#include <luabind\luabind.hpp>
#include <GraphicCommunicator\DepthScreenCaptureConfig.h>
#include <GraphicCommunicator\CubeScreenCaptureConfig.h>
#include <GraphicCommunicator\BasicScreenCaptureConfig.h>
#include <Keys.h>
#include "LuaMath.h"
#include <3DMath.h>

LuaScreenCapture::BasicScreenCapture::BasicScreenCapture(luabind::object const& table)
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

				 if(key == Keys::ScreenShot::WIDTH)				{ width = luabind::object_cast<int>(*it); }
			else if(key == Keys::ScreenShot::HEIGHT)			{ height = luabind::object_cast<int>(*it); }
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
		double nearZ = 0.01;
		double farZ = 5000.0;
		prespective = CHL::PerspectiveFovLHCalculation(FovAngleY, width / height, nearZ, farZ);
	}

	BasicScreenCaptureConfig::Create(width, height, camera, prespective, this->ID, this->TextureID);
}

void LuaScreenCapture::BasicScreenCapture::SetCameraMatrix(LuaMath::Matrix4x4 mat)
{
	BasicScreenCaptureConfig::SetCamera(this->ID, mat);
}
void LuaScreenCapture::BasicScreenCapture::SetPrespectiveMatrix(LuaMath::Matrix4x4 mat)
{
	BasicScreenCaptureConfig::SetPrespective(this->ID, mat);
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
			.def("SetCamera", &LuaScreenCapture::BasicScreenCapture::SetCameraMatrix)
			.def("SetPrespective", &LuaScreenCapture::BasicScreenCapture::SetPrespectiveMatrix)
			.def("GetTexture", &LuaScreenCapture::BasicScreenCapture::GetTexture)
			.def("Release", &LuaScreenCapture::BasicScreenCapture::Release)
	];
}

//*******************************************************************//
LuaScreenCapture::DepthScreenCapture::DepthScreenCapture(luabind::object const& table)
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

			if(key == Keys::ScreenShot::WIDTH)					{ width = luabind::object_cast<int>(*it); }
			else if(key == Keys::ScreenShot::HEIGHT)			{ height = luabind::object_cast<int>(*it); }
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
		double nearZ = 0.01;
		double farZ = 5000.0;
		prespective = CHL::PerspectiveFovLHCalculation(FovAngleY, width / height, nearZ, farZ);
	}

	DepthScreenCaptureConfig::Create(width, height, camera, prespective, this->ID, this->TextureID);
}

void LuaScreenCapture::DepthScreenCapture::SetCameraMatrix(LuaMath::Matrix4x4 mat)
{
	DepthScreenCaptureConfig::SetCamera(this->ID, mat);
}
void LuaScreenCapture::DepthScreenCapture::SetPrespectiveMatrix(LuaMath::Matrix4x4 mat)
{
	DepthScreenCaptureConfig::SetPrespective(this->ID, mat);
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
			.def("SetCamera", &LuaScreenCapture::DepthScreenCapture::SetCameraMatrix)
			.def("SetPrespective", &LuaScreenCapture::DepthScreenCapture::SetPrespectiveMatrix)
			.def("GetTexture", &LuaScreenCapture::DepthScreenCapture::GetTexture)
			.def("Release", &LuaScreenCapture::DepthScreenCapture::Release)
	];
}

//*******************************************************************//
LuaScreenCapture::CubeScreenCapture::CubeScreenCapture(luabind::object const& table)
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

			if(key == Keys::ScreenShot::WIDTH)		{ width = luabind::object_cast<int>(*it); }
			else if(key == Keys::ScreenShot::HEIGHT){ height = luabind::object_cast<int>(*it); }
			else if(key == Keys::ScreenShot::EYE)	{ eye = luabind::object_cast<LuaMath::Vector4>(*it); }
		}
	}

	CubeScreenCaptureConfig::Create(width, height, eye, this->ID, this->TextureID);
}

void LuaScreenCapture::CubeScreenCapture::SetEye(LuaMath::Vector4 mat)
{
	CubeScreenCaptureConfig::SetEye(this->ID, mat);
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
			.def("SetEye", &LuaScreenCapture::CubeScreenCapture::SetEye)
			.def("GetTexture", &LuaScreenCapture::CubeScreenCapture::GetTexture)
			.def("Release", &LuaScreenCapture::CubeScreenCapture::Release)
	];
}