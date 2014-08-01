#ifndef __LuaShader__
#define __LuaShader__

#include "Linker.h"

#include <lua.hpp>
#include <luabind\luabind.hpp>
#include <GenericLuaObject.h>

namespace LuaShader
{
	class ScriptGraphicDLL_API VertexShader : public GenericLuaObject
	{
	public:
		VertexShader(const GenericLuaObject& v);
		VertexShader(const std::string& fileName);
		void Release();

		static void Register(lua_State *lua);
	};
	class ScriptGraphicDLL_API PixelShader : public GenericLuaObject
	{
	public:
		PixelShader(const GenericLuaObject& v);
		PixelShader(const std::string& fileName);
		void Release();

		static void Register(lua_State *lua);
	};
	class ScriptGraphicDLL_API GeometryShader : public GenericLuaObject
	{
	public:
		GeometryShader(const GenericLuaObject& v);
		GeometryShader(const std::string& fileName);
		void Release();

		static void Register(lua_State *lua);
	};


	static inline void RegisterAllLuaFunction(lua_State *lua)
	{
		VertexShader::Register(lua);
		PixelShader::Register(lua);
		GeometryShader::Register(lua);
	}
};

#endif //__LuaShader__
