#include "LuaScreenCapture.h"
#include <luabind\luabind.hpp>
#include <Components.h>
#include <Keys.h>
#include <LuaMath.h>
#include <GenericLuaObject.h>
#include <ScriptManager.h>
#include <Resource.h>
#include <Logger.h>

namespace LuaScreenCapture
{
	BasicScreenCapture::BasicScreenCapture(luabind::object const& table)
	{
		unsigned int width = 1028;
		unsigned int height = 1028;
		unsigned int priority = 1000;
		std::string cameraID;
		std::string drawSettingsID;
		unsigned int numOfTagrets = 1;

		if(luabind::type(table) == LUA_TTABLE)
		{
			for(luabind::iterator it(table);
				it != luabind::iterator();
				++it)
			{
				std::string key = luabind::object_cast<std::string>(it.key());

					 if(key == Keys::ScreenShot::WIDTH)			{ width = this->GetWidth(*it); }
				else if(key == Keys::ScreenShot::HEIGHT)		{ height = this->GetHeight(*it); }
				else if(key == Keys::ScreenShot::CAMERAID)		{ cameraID = this->GetDrawSettingsID(*it); }
				else if(key == Keys::ScreenShot::DRAWSETTINGSID){ drawSettingsID = this->GetCameraID(*it); }
				else if(key == Keys::ScreenShot::NUMOFTARGETS)	{ numOfTagrets = this->GetNumOfTargets(*it); }
				else if(key == Keys::ScreenShot::PRIORITY)		{ priority = this->GetPriority(*it); }
			}
		}

		Components::Graphic->BasicScreenCaptureFactory()->Create(width, height, priority, cameraID, drawSettingsID, numOfTagrets, this->ID, this->TextureID);
	}

	void BasicScreenCapture::SetCameraID(GenericLuaObject cameraID)
	{
		Components::Graphic->BasicScreenCaptureFactory()->SetCameraID(this->ID, cameraID.GetID());
	}
	void BasicScreenCapture::SetDrawSettingsID(GenericLuaObject dsID)
	{
		Components::Graphic->BasicScreenCaptureFactory()->SetDrawSettingsID(this->ID, dsID.GetID());
	}
	void BasicScreenCapture::SetPriority(const luabind::object& v)
	{
		int p = this->GetPriority(v);
		Components::Graphic->BasicScreenCaptureFactory()->SetPriority(this->ID, p);
	}
	luabind::object BasicScreenCapture::GetTexture()
	{
		lua_State* lua = Resource::lua;

		luabind::object returnValue;

		if(this->TextureID.size() == 1)
		{
			GenericLuaObject g(this->TextureID[0]);
			LuaBasicTexture texture(g);
			returnValue = luabind::object(lua, texture);
		}
		else
		{
			returnValue = luabind::newtable(lua);

			for(unsigned int i = 0; i < this->TextureID.size(); ++i)
			{
				GenericLuaObject g(this->TextureID[i]);
				LuaBasicTexture texture(g);
				returnValue[i + 1] = texture;
			}
		}

		return returnValue;
	}
	void BasicScreenCapture::Release()
	{
		Components::Graphic->BasicScreenCaptureFactory()->Release(this->ID);
		this->ID = "";
		this->TextureID.clear();
	}

	void BasicScreenCapture::Register(lua_State *lua)
	{
		luabind::module(lua)[
			luabind::class_<LuaScreenCapture::BasicScreenCapture>("BasicScreenCapture")
				.def(luabind::constructor<luabind::object const&>())
				.def("SetCamera", &LuaScreenCapture::BasicScreenCapture::SetCameraID)
				.def("SetDrawSettingsID", &LuaScreenCapture::BasicScreenCapture::SetDrawSettingsID)
				.def("SetPriority", &LuaScreenCapture::BasicScreenCapture::SetPriority)
				.def("GetTexture", &LuaScreenCapture::BasicScreenCapture::GetTexture)
				.def("Release", &LuaScreenCapture::BasicScreenCapture::Release)
		];
	}

	unsigned int BasicScreenCapture::GetWidth(const luabind::object& v) const
	{
		unsigned int returnValue;
		if(boost::optional<int> value = luabind::object_cast_nothrow<int>(v))
			returnValue = *value;
		else
			Logger::LogError("Wrong paramter type");
		return returnValue;
	}
	unsigned int BasicScreenCapture::GetHeight(const luabind::object& v) const
	{
		unsigned int returnValue;
		if(boost::optional<int> value = luabind::object_cast_nothrow<int>(v))
			returnValue = *value;
		else
			Logger::LogError("Wrong paramter type");
		return returnValue;
	}
	unsigned int BasicScreenCapture::GetPriority(const luabind::object& v) const
	{
		unsigned int returnValue;
		if(boost::optional<int> value = luabind::object_cast_nothrow<int>(v))
			returnValue = *value;
		else
			Logger::LogError("Wrong paramter type");
		return returnValue;
	}
	unsigned int BasicScreenCapture::GetNumOfTargets(const luabind::object& v) const
	{
		unsigned int returnValue;
		if(boost::optional<int> value = luabind::object_cast_nothrow<int>(v))
			returnValue = *value;
		else
			Logger::LogError("Wrong paramter type");
		return returnValue;
	}
	std::string BasicScreenCapture::GetCameraID(const luabind::object& v) const
	{
		std::string returnValue;

		if(boost::optional<GenericLuaObject*> value = luabind::object_cast_nothrow<GenericLuaObject*>(v))
			returnValue = (*value)->GetID();
		else
			Logger::LogError("Wrong paramter type");

		return returnValue;
	}
	std::string BasicScreenCapture::GetDrawSettingsID(const luabind::object& v) const
	{
		std::string returnValue;

		if(boost::optional<GenericLuaObject> value = luabind::object_cast_nothrow<GenericLuaObject>(v))
			returnValue = value->GetID();
		else
			Logger::LogError("Wrong paramter type");

		return returnValue;
	}
}

//*******************************************************************//
LuaScreenCapture::DepthScreenCapture::DepthScreenCapture(luabind::object const& table)
{
	unsigned int width = 1028;
	unsigned int height = 1028;
	unsigned int priority = 1000;
	std::string cameraID;
	std::string drawSettingsID;

	if(luabind::type(table) == LUA_TTABLE)
	{
		for(luabind::iterator it(table);
			it != luabind::iterator();
			++it)
		{
			std::string key = luabind::object_cast<std::string>(it.key());

				 if(key == Keys::ScreenShot::WIDTH)			{ width = luabind::object_cast<int>(*it); }
			else if(key == Keys::ScreenShot::HEIGHT)		{ height = luabind::object_cast<int>(*it); }
			else if(key == Keys::ScreenShot::CAMERAID)		{ cameraID = luabind::object_cast<GenericLuaObject>(*it).GetID(); }
			else if(key == Keys::ScreenShot::DRAWSETTINGSID){ drawSettingsID = luabind::object_cast<GenericLuaObject>(*it).GetID(); }
			else if(key == Keys::ScreenShot::PRIORITY)		{ priority = luabind::object_cast<int>(*it); }
		}
	}
	
	Components::Graphic->DepthScreenCaptureFactory()->Create(width, height, priority, cameraID, drawSettingsID, this->ID, this->TextureID);
}

void LuaScreenCapture::DepthScreenCapture::SetCameraID(GenericLuaObject cameraID)
{
	Components::Graphic->DepthScreenCaptureFactory()->SetCameraID(this->ID, cameraID.GetID());
}
void LuaScreenCapture::DepthScreenCapture::SetDrawSettingsID(GenericLuaObject dsID)
{
	Components::Graphic->DepthScreenCaptureFactory()->SetDrawSettingsID(this->ID, dsID.GetID());
}
LuaBasicTexture LuaScreenCapture::DepthScreenCapture::GetTexture()
{
	GenericLuaObject g(this->TextureID);
	LuaBasicTexture texture(g);
	return texture;
}
void LuaScreenCapture::DepthScreenCapture::Release()
{
	Components::Graphic->DepthScreenCaptureFactory()->Release(this->ID);
	this->ID = "";
	this->TextureID = "";
}

void LuaScreenCapture::DepthScreenCapture::Register(lua_State *lua)
{
	luabind::module(lua)[
		luabind::class_<LuaScreenCapture::DepthScreenCapture>("DepthScreenCapture")
			.def(luabind::constructor<luabind::object const&>())
			.def("SetCamera", &LuaScreenCapture::DepthScreenCapture::SetCameraID)
			.def("SetDrawSettingsID", &LuaScreenCapture::BasicScreenCapture::SetDrawSettingsID)
			.def("GetTexture", &LuaScreenCapture::DepthScreenCapture::GetTexture)
			.def("Release", &LuaScreenCapture::DepthScreenCapture::Release)
	];
}

//*******************************************************************//
LuaScreenCapture::CubeScreenCapture::CubeScreenCapture(luabind::object const& table)
{
	unsigned int width = 1028;
	unsigned int height = 1028;
	unsigned int priority = 1000;
	std::string cameraID;
	std::string drawSettingsID;

	if(luabind::type(table) == LUA_TTABLE)
	{
		for(luabind::iterator it(table);
			it != luabind::iterator();
			++it)
		{
			std::string key = luabind::object_cast<std::string>(it.key());

				 if(key == Keys::ScreenShot::WIDTH)			{ width = luabind::object_cast<int>(*it); }
			else if(key == Keys::ScreenShot::HEIGHT)		{ height = luabind::object_cast<int>(*it); }
			else if(key == Keys::ScreenShot::CAMERAID)		{ cameraID = luabind::object_cast<GenericLuaObject>(*it).GetID(); }
			else if(key == Keys::ScreenShot::DRAWSETTINGSID){ drawSettingsID = luabind::object_cast<GenericLuaObject>(*it).GetID(); }
			else if(key == Keys::ScreenShot::PRIORITY)		{ priority = luabind::object_cast<int>(*it); }
		}
	}
	Components::Graphic->CubeScreenCaptureFactory()->Create(width, height, priority, cameraID, drawSettingsID, this->ID, this->TextureID);
}

void LuaScreenCapture::CubeScreenCapture::SetCameraID(GenericLuaObject cameraID)
{
	Components::Graphic->CubeScreenCaptureFactory()->SetCameraID(this->ID, cameraID.GetID());
}
void LuaScreenCapture::CubeScreenCapture::SetDrawSettingsID(GenericLuaObject dsID)
{
	Components::Graphic->CubeScreenCaptureFactory()->SetDrawSettingsID(this->ID, dsID.GetID());
}
LuaBasicTexture LuaScreenCapture::CubeScreenCapture::GetTexture()
{
	GenericLuaObject g(this->TextureID);
	LuaBasicTexture texture(g);
	return texture;
}
void LuaScreenCapture::CubeScreenCapture::Release()
{
	Components::Graphic->CubeScreenCaptureFactory()->Release(this->ID);
	this->ID = "";
	this->TextureID = "";
}

void LuaScreenCapture::CubeScreenCapture::Register(lua_State *lua)
{
	luabind::module(lua)[
		luabind::class_<LuaScreenCapture::CubeScreenCapture>("CubeScreenCapture")
			.def(luabind::constructor<luabind::object const&>())
			.def("SetCamera", &LuaScreenCapture::CubeScreenCapture::SetCameraID)
			.def("SetDrawSettingsID", &LuaScreenCapture::BasicScreenCapture::SetDrawSettingsID)
			.def("GetTexture", &LuaScreenCapture::CubeScreenCapture::GetTexture)
			.def("Release", &LuaScreenCapture::CubeScreenCapture::Release)
	];
}