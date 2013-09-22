#include "LuaKeySetup.h"

#include <luabind\luabind.hpp>

#include "AddKeyStateAction.h"
#include "LuaManager.h"

std::string LuaKeySetup::OnKeyDown(unsigned int key, luabind::object function)
{
	if (luabind::type(function) != LUA_TFUNCTION)
    {	
		throw std::exception("Wrong paramter for OnKeyDown, Please pass in the key and function");
    }

	std::shared_ptr<AddKeyStateAction> msg(
		new AddKeyStateAction(key, AddKeyStateAction::StateWanted::KeyDown, function));

	LuaManager::GetInstance().SubmitMessage(msg);

	return msg->ID;
}
std::string LuaKeySetup::OnKeyUp(unsigned int key, luabind::object const& function)
{
	if (luabind::type(function) != LUA_TFUNCTION)
    {	
		throw std::exception("Wrong paramter for OnKeyUp, Please pass in the key and function");
    }

	return "";
}
std::string LuaKeySetup::OnKeyHold(unsigned int key, luabind::object const& function)
{
	if (luabind::type(function) != LUA_TFUNCTION)
    {	
		throw std::exception("Wrong paramter for OnKeyHold, Please pass in the key and function");
    }

	return "";
}
	
void LuaKeySetup::Register(lua_State *lua)
{
	luabind::module(lua)[
		luabind::def("OnKeyDown", LuaKeySetup::OnKeyDown),
		luabind::def("OnKeyUp", LuaKeySetup::OnKeyUp),
		luabind::def("OnKeyHold", LuaKeySetup::OnKeyHold)
	  ];
}