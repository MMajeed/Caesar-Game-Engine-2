#ifndef __LuaScreenCapture__
#define __LuaScreenCapture__

#include "Linker.h"

#include <lua.hpp>
#include <luabind\luabind.hpp>
#include "LuaBasicTexture.h"
#include <LuaMath.h>
#include <GenericLuaObject.h>

namespace LuaScreenCapture
{
	class ScriptGraphicDLL_API BasicScreenCapture
	{
	public:
		BasicScreenCapture(const luabind::object& table);

		void SetCameraID(GenericLuaObject cameraID);

		luabind::object GetTexture();
		void Release();

	private:
		unsigned int GetWidth(const luabind::object& v) const;
		unsigned int GetHeight(const luabind::object& v) const;
		unsigned int GetPriority(const luabind::object& v) const;
		unsigned int GetNumOfTargets(const luabind::object& v) const;
		std::string GetCameraID(const luabind::object& v) const;
	public:
		std::string ID;
		std::vector<std::string> TextureID;

		static void Register(lua_State *lua);
	};

	class ScriptGraphicDLL_API DepthScreenCapture
	{
	public:
		DepthScreenCapture(luabind::object const& table);

		void SetCameraID(GenericLuaObject cameraID);
		LuaBasicTexture GetTexture();
		void Release();

		std::string ID;
		std::string TextureID;

		static void Register(lua_State *lua);
	};

	class ScriptGraphicDLL_API CubeScreenCapture
	{
	public:
		CubeScreenCapture(luabind::object const& table);

		void SetCameraID(GenericLuaObject cameraID);
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
