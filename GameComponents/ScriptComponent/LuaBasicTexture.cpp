#include "LuaBasicTexture.h"

#include <GraphicCommunicator\AddBasicTexture.h>
#include <GraphicCommunicator\GraphicCommunicator.h>

LuaBasicTexture::LuaBasicTexture(std::string textureFile)
{
	std::shared_ptr<AddBasicTexture> msg(new AddBasicTexture(textureFile));

	GraphicCommunicator::SubmitMessage(msg);

	this->ID = msg->ID;
}

void LuaBasicTexture::Register(lua_State *lua)
{
	luabind::module(lua) [
		luabind::class_<LuaBasicTexture>("BasicTexture")
		  .def(luabind::constructor<std::string>())
		  .def_readonly("ID", &LuaBasicTexture::ID)
	  ];
}