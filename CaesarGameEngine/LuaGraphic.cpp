#include "LuaManager.h"
#include "ClearScreenMessage.h"
#include "LuaGraphic.h"
#include "GraphicManager.h"

int LuaGraphic::ClearScreen::Action(lua_State *lua)
{
	boost::numeric::ublas::vector<double> newColour(3);

	newColour(0) = (float)lua_tonumber(lua, 1);	// Get the 1 paramter
	newColour(1) = (float)lua_tonumber(lua, 2);	// Get the 2 paramter
	newColour(2) = (float)lua_tonumber(lua, 3);	// Get the 3 paramter
	lua_pop(lua, 3);

	std::shared_ptr<ClearScreenMessage> msg(new ClearScreenMessage(newColour));

	GraphicManager().GetInstance().SubmitMessage(msg);

	return 0;
}

void LuaGraphic::ClearScreen::Register()
{
	lua_State *lua = LuaManager::GetInstance().lua;

	lua_register(lua, "ClearScreen", LuaGraphic::ClearScreen::Action);	// Register the function
}