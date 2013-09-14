#include "LuaManager.h"
#include "ClearScreenMessage.h"
#include "LuaGraphic.h"
#include "GraphicManager.h"

void LuaGraphic::ClearScreen::Action(double x, double y, double z)
{
	boost::numeric::ublas::vector<double> newColour(3);

	newColour(0) = x;	// Get the 1 paramter
	newColour(1) = y;	// Get the 2 paramter
	newColour(2) = z;	// Get the 3 paramter

	std::shared_ptr<ClearScreenMessage> msg(new ClearScreenMessage(newColour));

	GraphicManager().GetInstance().SubmitMessage(msg);
}

void LuaGraphic::ClearScreen::Register()
{
	lua_State *lua = LuaManager::GetInstance().lua;

	luabind::module(lua) [
		luabind::def("ClearScreen", LuaGraphic::ClearScreen::Action)
	  ];
}