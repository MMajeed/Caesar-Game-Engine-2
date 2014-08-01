#include "LuaShader.h"
#include <GraphicCommunicator\ShaderConfig.h>

namespace LuaShader
{
	VertexShader::VertexShader(const GenericLuaObject& v) : GenericLuaObject(v){}
	VertexShader::VertexShader(const std::string& fileName)
	{
		this->ID = ShaderConfig::Vertex::Create(fileName);
	}
	void VertexShader::Release()
	{
		ShaderConfig::Vertex::Release(this->ID);
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
		this->ID = ShaderConfig::Pixel::Create(fileName);
	}
	void PixelShader::Release()
	{
		ShaderConfig::Pixel::Release(this->ID);
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
		this->ID = ShaderConfig::Geometry::Create(fileName);
	}
	void GeometryShader::Release()
	{
		ShaderConfig::Geometry::Release(this->ID);
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