#include "LuaGraphic.h"
#include "ScriptManager.h"
#include <Resource.h>
#include <Components.h>
#include <Keys.h>
#include <LuaOnResize.h>
#include <ProcessMessage.h>
#include <Logger.h>

namespace LuaGraphic
{
	void SetMainCamera(const GenericLuaObject& cam)
	{
		Components::Graphic->GraphicSettingsFactory()->SetMainCamera(cam.GetID());
	}
	void SetMainDrawSettings(const GenericLuaObject& ds)
	{
		Components::Graphic->GraphicSettingsFactory()->SetMainDrawSettings(ds.GetID());
	}
	void ChangeWindowsTitle(std::string title)
	{
		Components::Graphic->GraphicSettingsFactory()->ChangeWindowsText(title);
	}
	void MoveWindow(unsigned int x, unsigned int y)
	{
		Components::Graphic->GraphicSettingsFactory()->MoveWindow(x, y);
	}
	void ResizeWindow(unsigned int height, unsigned int width)
	{
		Components::Graphic->GraphicSettingsFactory()->ResizeWindow(height, width);
	}
	void ResizeClient(unsigned int height, unsigned int width)
	{
		Components::Graphic->GraphicSettingsFactory()->ResizeClient(height, width);
	}
	void ResizeRender(unsigned int height, unsigned int width)
	{
		Components::Graphic->GraphicSettingsFactory()->ResizeRender(height, width);
	}
	void DiableResize()
	{
		Components::Graphic->GraphicSettingsFactory()->DisableResize();
	}
	void EnableResize()
	{
		Components::Graphic->GraphicSettingsFactory()->EnableResize();
	}
	void FullScreen()
	{
		Components::Graphic->GraphicSettingsFactory()->FullScreen();
	}
	void LeaveFullScreen()
	{
		Components::Graphic->GraphicSettingsFactory()->LeaveFullScreen();
	}
	bool IsFullScreen()
	{
		return Components::Graphic->GraphicSettingsFactory()->IsFullScreen();
	}
	luabind::object GetClientSize()
	{
		unsigned int height; unsigned int width;
		Components::Graphic->GraphicSettingsFactory()->GetClientSize(height, width);
		luabind::object returnValue = luabind::newtable(Resource::lua);
		returnValue["Height"] = height;
		returnValue["Width"] = width;
		return returnValue;
	}
	luabind::object GetWindowSize()
	{
		unsigned int height; unsigned int width;
		Components::Graphic->GraphicSettingsFactory()->GetWindowSize(height, width);
		luabind::object returnValue = luabind::newtable(Resource::lua);
		returnValue["Height"] = height;
		returnValue["Width"] = width;
		return returnValue;
	}
	luabind::object GetRenderSize()
	{
		unsigned int height; unsigned int width;
		Components::Graphic->GraphicSettingsFactory()->GetRenderSize(height, width);
		luabind::object returnValue = luabind::newtable(Resource::lua);
		returnValue["Height"] = height;
		returnValue["Width"] = width;
		return returnValue;
	}
	luabind::object GetWindowLoc()
	{
		unsigned int x; unsigned int y;
		Components::Graphic->GraphicSettingsFactory()->GetWindowsLocation(x, y); 
		luabind::object returnValue = luabind::newtable(Resource::lua);
		returnValue["X"] = x;
		returnValue["Y"] = y;
		return returnValue;
	}
	void CallOnResize(luabind::object const& function)
	{
		if(luabind::type(function) != LUA_TFUNCTION)
		{
			Logger::LogError("Wrong paramter for LoopCall, Please pass in how many seconds apart and function");
		}

		std::shared_ptr<LuaOnResize> process(new LuaOnResize(function));

		ProcessMessage::Add(process);
	}
	void VSync(bool v)
	{
		Components::Graphic->GraphicSettingsFactory()->VSync(v);
	}

	void RegisterAllLuaFunction(lua_State *lua)
	{
		luabind::module(lua)[
			luabind::def("SetMainCamera", LuaGraphic::SetMainCamera),
			luabind::def("SetMainDrawSettings", LuaGraphic::SetMainDrawSettings),
			luabind::def("SetWindowsTitle", LuaGraphic::ChangeWindowsTitle),
			luabind::def("MoveWindow", LuaGraphic::MoveWindow),
			luabind::def("ReizeWindow", LuaGraphic::ResizeWindow),
			luabind::def("ResizeRender", LuaGraphic::ResizeRender),
			luabind::def("ReizeClient", LuaGraphic::ResizeClient),
			luabind::def("FullScreen", LuaGraphic::FullScreen),
			luabind::def("DiableResize", LuaGraphic::DiableResize),
			luabind::def("EnableResize", LuaGraphic::EnableResize),
			luabind::def("LeaveFullScreen", LuaGraphic::LeaveFullScreen),
			luabind::def("IsFullScreen", LuaGraphic::IsFullScreen),
			luabind::def("GetWindowSize", LuaGraphic::GetWindowSize),
			luabind::def("GetClientSize", LuaGraphic::GetClientSize),
			luabind::def("GetRenderSize", LuaGraphic::GetRenderSize),
			luabind::def("GetWindowLocs", LuaGraphic::GetWindowLoc),
			luabind::def("CallOnResize", LuaGraphic::CallOnResize),
			luabind::def("VSync", LuaGraphic::VSync)
		];
	}
};