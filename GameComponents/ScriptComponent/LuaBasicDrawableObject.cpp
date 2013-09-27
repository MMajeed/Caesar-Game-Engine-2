#include "LuaBasicDrawableObject.h"

#include <exception>
#include <Converter.h>
#include "LuaManager.h"
#include <GraphicCommunicator\AddBasicDrawableMessage.h>
#include <GraphicCommunicator\GetGraphicManager.h>
#include <Model.h>
#include <Keys.h>


LuaBasicDrawableObject::LuaBasicDrawableObject(luabind::object const& table)
{
	std::map<std::string, std::string> mapKeys;
	if (luabind::type(table) != LUA_TTABLE)
    {	
		throw std::exception("Wrong paramter for AddBasicObject, please send in a table with these values inside of them: \nModelFile\nVertexShaderFile\nPixelShaderFile\nTextureFile");
    }

	for (luabind::iterator it(table); it != luabind::iterator(); ++it)
	{ 
		mapKeys[luabind::object_cast<std::string>(it.key())] = luabind::object_cast<std::string>(*it);
	}
	std::string fileName = mapKeys[Keys::MODELFILE];
	std::string vertexFileName = mapKeys[Keys::VERTEXSHADERFILE];
	std::string pixelFileName = mapKeys[Keys::PIXELSHADERFILE];

	Model m(fileName);

	std::shared_ptr<AddBasicDrawableMessage> msg(
			new AddBasicDrawableMessage(m, vertexFileName, "VS", "vs_4_0", pixelFileName, "PS", "ps_4_0" ));

	GetGraphicManager::GetComponent()->SubmitMessage(msg);

	msg->WaitTillProcccesed();

	this->ID = msg->ID;
}

void LuaBasicDrawableObject::Register(lua_State *lua)
{
	luabind::module(lua) [
		luabind::class_<LuaBasicDrawableObject>("BasicDrawableObject")
		  .def(luabind::constructor<luabind::object const&>())
		  .def_readonly("ID", &LuaBasicDrawableObject::ID)
	  ];
}