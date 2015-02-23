#include "LuaShader.h"
#include <Components.h>

namespace LuaShader
{
	VertexShader::VertexShader(const GenericLuaObject& v) : GenericLuaObject(v){}
	VertexShader::VertexShader(const std::string& fileName)
	{
		this->ID = Components::Graphic->ShaderFactory()->VertexCreate(fileName);
	}
	void VertexShader::Release()
	{
		Components::Graphic->ShaderFactory()->VertexRelease(this->ID);
	}

	void VertexShader::Register(lua_State *lua)
	{
		luabind::module(lua)[
			luabind::class_<LuaShader::VertexShader, GenericLuaObject>("VertexShader")
				.def(luabind::constructor<const GenericLuaObject&>())
				.def(luabind::constructor<const std::string&>())
				.def("Release", &LuaShader::VertexShader::Release)
		];
	}

	//*******************************************************************//
	PixelShader::PixelShader(const GenericLuaObject& v) : GenericLuaObject(v){}
	PixelShader::PixelShader(const std::string& fileName)
	{
		this->ID = Components::Graphic->ShaderFactory()->PixelCreate(fileName);
	}
	void PixelShader::Release()
	{
		Components::Graphic->ShaderFactory()->PixelRelease(this->ID);
	}

	void PixelShader::Register(lua_State *lua)
	{
		luabind::module(lua)[
			luabind::class_<LuaShader::PixelShader, GenericLuaObject>("PixelShader")
				.def(luabind::constructor<const GenericLuaObject&>())
				.def(luabind::constructor<const std::string&>())
				.def("Release", &LuaShader::PixelShader::Release)
		];
	}

	//*******************************************************************//

	GeometryShader::GeometryShader(const GenericLuaObject& v) : GenericLuaObject(v){}
	GeometryShader::GeometryShader(const std::string& fileName)
	{
		this->ID = Components::Graphic->ShaderFactory()->GeometryCreate(fileName);
	}
	void GeometryShader::Release()
	{
		Components::Graphic->ShaderFactory()->GeometryRelease(this->ID);
	}

	void GeometryShader::Register(lua_State *lua)
	{
		luabind::module(lua)[
			luabind::class_<LuaShader::GeometryShader, GenericLuaObject>("GeometryShader")
				.def(luabind::constructor<const GenericLuaObject&>())
				.def(luabind::constructor<const std::string&>())
				.def("Release", &LuaShader::GeometryShader::Release)
		];
	}

};