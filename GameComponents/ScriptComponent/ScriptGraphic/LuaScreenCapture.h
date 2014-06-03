#ifndef __LuaScreenCapture__
#define __LuaScreenCapture__

#include <lua.hpp>
#include <luabind\luabind.hpp>
#include "LuaBasicTexture.h"
#include <LuaMath.h>
#include <ScriptEntity\LuaCamera.h>

namespace LuaScreenCapture
{
	class BasicScreenCapture
	{
	public:
		BasicScreenCapture(luabind::object const& table);

		void SetCameraID(LuaCamera cameraID);
		LuaBasicTexture GetTexture();
		void Release();

		std::string ID;
		std::string TextureID;

		static void Register(lua_State *lua);
	};

	class DepthScreenCapture
	{
	public:
		DepthScreenCapture(luabind::object const& table);

		void SetCameraID(LuaCamera cameraID);
		LuaBasicTexture GetTexture();
		void Release();

		std::string ID;
		std::string TextureID;

		static void Register(lua_State *lua);
	};

	class CubeScreenCapture
	{
	public:
		CubeScreenCapture(luabind::object const& table);

		void SetCameraID(LuaCamera cameraID);
		LuaBasicTexture GetTexture();
		void Release();

		std::string ID;
		std::string TextureID;

		static void Register(lua_State *lua);
	};


	static inline void RegisterAllLuaFunction(lua_State *lua)
	{
		BasicScreenCapture::Register(lua);
		DepthScreenCapture::Register(lua);
		CubeScreenCapture::Register(lua);
	}
};

#endif //__LuaScreenCapture__
