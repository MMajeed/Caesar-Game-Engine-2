#include "LuaGraphic.h"
#include "ScriptManager.h"
#include <GraphicCommunicator\GraphicSettings.h>
#include <GraphicCommunicator\GraphicCommunicator.h>
#include <Keys.h>
#include <LuaOnResize.h>
#include <ProcessMessage.h>
#include <Logger.h>

namespace LuaGraphic
{
	void SetMainCamera(const GenericLuaObject& cam)
	{
		GraphicSettings::SetMainCamera(cam.GetID());
	}
	void SetMainDrawSettings(const GenericLuaObject& ds)
	{
		GraphicSettings::SetMainDrawSettings(ds.GetID());
	}
	void ChangeWindowsTitle(std::string title)
	{
		GraphicSettings::ChangeWindowsText(title);
	}
	void MoveWindow(unsigned int x, unsigned int y)
	{
		GraphicSettings::MoveWindow(x, y);
	}
	void ResizeWindow(unsigned int height, unsigned int width)
	{
		GraphicSettings::ResizeWindow(height, width);
	}
	void ResizeClient(unsigned int height, unsigned int width)
	{
		GraphicSettings::ResizeClient(height, width);
	}
	void ResizeRender(unsigned int height, unsigned int width)
	{
		GraphicSettings::ResizeRender(height, width);
	}
	void DiableResize()
	{
		GraphicSettings::DisableResize();
	}
	void EnableResize()
	{
		GraphicSettings::EnableResize();
	}
	void FullScreen()
	{
		GraphicSettings::FullScreen();
	}
	void LeaveFullScreen()
	{
		GraphicSettings::LeaveFullScreen();
	}
	bool IsFullScreen()
	{
		return GraphicSettings::IsFullScreen();
	}
	luabind::object GetClientSize()
	{
		unsigned int height; unsigned int width;
		GraphicSettings::GetClientSize(height, width);
		luabind::object returnValue = luabind::newtable(ScriptManager::GetInstance().lua);
		returnValue["Height"] = height;
		returnValue["Width"] = width;
		return returnValue;
	}
	luabind::object GetWindowSize()
	{
		unsigned int height; unsigned int width;
		GraphicSettings::GetWindowSize(height, width);
		luabind::object returnValue = luabind::newtable(ScriptManager::GetInstance().lua);
		returnValue["Height"] = height;
		returnValue["Width"] = width;
		return returnValue;
	}
	luabind::object GetRenderSize()
	{
		unsigned int height; unsigned int width;
		GraphicSettings::GetRenderSize(height, width);
		luabind::object returnValue = luabind::newtable(ScriptManager::GetInstance().lua);
		returnValue["Height"] = height;
		returnValue["Width"] = width;
		return returnValue;
	}
	luabind::object GetWindowLoc()
	{
		unsigned int x; unsigned int y;
		GraphicSettings::GetWindowsLocation(x, y); 
		luabind::object returnValue = luabind::newtable(ScriptManager::GetInstance().lua);
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
		GraphicSettings::VSync(v);
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