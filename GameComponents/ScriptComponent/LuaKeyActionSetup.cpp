#include "LuaKeyActionSetup.h"

#include <luabind\luabind.hpp>

#include "LuaKeyAction.h"
#include "LuaManager.h"

std::string LuaKeyActionSetup::OnKeyDown(unsigned int key, luabind::object function)
{
	if (luabind::type(function) != LUA_TFUNCTION)
    {	
		throw std::invalid_argument("Wrong paramter for OnKeyDown, Please pass in the key and function");
    }

	std::shared_ptr<LuaKeyAction> newKeyAction(new LuaKeyAction(key, LuaKeyAction::KeyStatWanted::KeyDown, function));

	LuaManager::GetInstance().SubmitProcesses(newKeyAction);

	return newKeyAction->ID;
}
std::string LuaKeyActionSetup::OnKeyUp(unsigned int key, luabind::object const& function)
{
	if (luabind::type(function) != LUA_TFUNCTION)
    {	
		throw std::invalid_argument("Wrong paramter for OnKeyUp, Please pass in the key and function");
    }

	std::shared_ptr<LuaKeyAction> newKeyAction(new LuaKeyAction(key, LuaKeyAction::KeyStatWanted::KeyUp, function));

	LuaManager::GetInstance().SubmitProcesses(newKeyAction);

	return newKeyAction->ID;
}
	
void LuaKeyActionSetup::Register(lua_State *lua)
{
	luabind::module(lua)[
		luabind::def("OnKeyDown", LuaKeyActionSetup::OnKeyDown),
		luabind::def("OnKeyUp", LuaKeyActionSetup::OnKeyUp)
	  ];
}