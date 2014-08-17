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
LuaBasicTexture::LuaBasicTexture(const GenericLuaObject& v) : GenericLuaObject(v){}
void LuaBasicTexture::Register(lua_State *lua)
{
	luabind::module(lua) [
		luabind::class_<LuaBasicTexture, GenericLuaObject>("BasicTexture")
		  .def(luabind::constructor<>())
		  .def(luabind::constructor<std::string>())
		  .def(luabind::constructor<const GenericLuaObject&>())
		  .def("Release", &LuaBasicTexture::Release)
	  ];
}