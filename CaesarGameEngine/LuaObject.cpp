#include "LuaObject.h"

#include <luabind\luabind.hpp>
#include <string>
#include <hash_map>

#include "Keys.h"
#include "AddObjectMessage.h"
#include "ObjectManager.h"

std::string LuaObject::Object::AddObject(luabind::object const& table)
{
	std::hash_map<std::string, std::string> mapKeys;
	if (luabind::type(table) != LUA_TTABLE)
    {	
		throw std::exception("Wrong paramter for AddObject, please send in a table with these values inside of them: ");
    }

	for (luabind::iterator it(table); it != luabind::iterator(); ++it)
	{ 
		mapKeys[luabind::object_cast<std::string>(it.key())] = luabind::object_cast<std::string>(*it);
	}

	std::shared_ptr<AddObjectMessage> msg(new AddObjectMessage(mapKeys));

	ObjectManager::GetInstance().SubmitMessage(msg);

	msg->WaitTillProcccesed();

	return msg->ID;
}

void LuaObject::Object::Register(lua_State *lua)
{
	luabind::module(lua) [
		luabind::def("AddObject", LuaObject::Object::AddObject)
	  ];
}