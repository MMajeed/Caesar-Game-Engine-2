#include "LuaGraphic.h"
#include "LuaManager.h"
#include <GraphicCommunicator\SetGraphicSettings.h>
#include <GraphicCommunicator\GraphicCommunicator.h>

void LuaGraphic::ClearScreen::Action(double x, double y, double z)
{
	CHL::Vec4 newColour;

	newColour(0) = x;	// Get the 1 paramter
	newColour(1) = y;	// Get the 2 paramter
	newColour(2) = z;	// Get the 3 paramter

	std::shared_ptr<ClearScreenMessage> msg(new ClearScreenMessage(newColour));

	GraphicCommunicator::SubmitMessage(msg);
}

void LuaGraphic::ClearScreen::Register(lua_State *lua)
{
	luabind::module(lua) [
		luabind::def("ClearScreen", LuaGraphic::ClearScreen::Action)
	  ];
}