#include "LuaGraphic.h"
#include "ScriptManager.h"
#include <GraphicCommunicator\GraphicSettings.h>
#include <GraphicCommunicator\GraphicCommunicator.h>
#include <Keys.h>

namespace LuaGraphic
{
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
	luabind::object GetClientsSize()
	{
		unsigned int height; unsigned int width;
		GraphicSettings::GetWindowsClientSize(height, width);
		luabind::object returnValue = luabind::newtable(ScriptManager::GetInstance().lua);
		returnValue["Height"] = height;
		returnValue["Width"] = width;
		return returnValue;
	}
	luabind::object GetWindowsSize()
	{
		unsigned int height; unsigned int width;
		GraphicSettings::GetWindowsWindowSize(height, width);
		luabind::object returnValue = luabind::newtable(ScriptManager::GetInstance().lua);
		returnValue["Height"] = height;
		returnValue["Width"] = width;
		return returnValue;
	}
	luabind::object GetWindowsLoc()
	{
		unsigned int x; unsigned int y;
		GraphicSettings::GetWindowsLocation(x, y); 
		luabind::object returnValue = luabind::newtable(ScriptManager::GetInstance().lua);
		returnValue["X"] = x;
		returnValue["Y"] = y;
		return returnValue;
	}
	void SetScreenTexture(GenericLuaObject tx)
	{
		GraphicSettings::SetScreenTexture(tx.ID);
	}

	void RegisterAllLuaFunction(lua_State *lua)
	{
		luabind::module(lua)[
			luabind::def("SetWindowsTitle", LuaGraphic::ChangeWindowsTitle),
			luabind::def("MoveWindow", LuaGraphic::MoveWindow),
			luabind::def("ReizeWindow", LuaGraphic::ResizeWindow),
			luabind::def("ReizeClient", LuaGraphic::ResizeClient),
			luabind::def("FullScreen", LuaGraphic::FullScreen),
			luabind::def("DiableResize", LuaGraphic::DiableResize),
			luabind::def("EnableResize", LuaGraphic::EnableResize),
			luabind::def("LeaveFullScreen", LuaGraphic::LeaveFullScreen),
			luabind::def("IsFullScreen", LuaGraphic::IsFullScreen),
			luabind::def("GetWindowsSize", LuaGraphic::GetWindowsSize),
			luabind::def("GetClientsSize", LuaGraphic::GetClientsSize),
			luabind::def("GetWindowsLocs", LuaGraphic::GetWindowsLoc),
			luabind::def("SetScreenTexture", LuaGraphic::SetScreenTexture)
		];
	}
};