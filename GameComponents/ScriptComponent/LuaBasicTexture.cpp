#include "LuaBasicTexture.h"

#include <GraphicCommunicator\AddBasicTexture.h>
#include <GraphicCommunicator\GraphicCommunicator.h>

LuaBasicTexture::LuaBasicTexture(int slot, std::string textureFile)
{
	std::shared_ptr<AddBasicTexture> msg(new AddBasicTexture(slot, textureFile));

	GraphicCommunicator::SubmitMessage(msg);

	this->ID = msg->ID;
}

void LuaBasicTexture::Register(lua_State *lua)
{
	luabind::module(lua) [
		luabind::class_<LuaBasicTexture>("BasicTexture")
		  .def(luabind::constructor<int, std::string>())
		  .def_readonly("ID", &LuaBasicTexture::ID)
	  ];
}