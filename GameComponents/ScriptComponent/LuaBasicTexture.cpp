#include "LuaBasicTexture.h"

#include <GraphicCommunicator\BasicTextureConfig.h>

LuaBasicTexture::LuaBasicTexture(std::string textureFile)
{
	this->ID = BasicTextureConfig::Create(textureFile);
}
void LuaBasicTexture::Release()
{
	BasicTextureConfig::Release(this->ID);
	this->ID = "";
}
void LuaBasicTexture::Register(lua_State *lua)
{
	luabind::module(lua) [
		luabind::class_<LuaBasicTexture>("BasicTexture")
		  .def(luabind::constructor<std::string>())
		  .def("Release", &LuaBasicTexture::Release)
		  .def_readonly("ID", &LuaBasicTexture::ID)
	  ];
}