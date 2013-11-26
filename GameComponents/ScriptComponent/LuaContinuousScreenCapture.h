#ifndef __LuaContinuousScreenCapture__
#define __LuaContinuousScreenCapture__

#include <lua.hpp>
#include <luabind\luabind.hpp>
#include "LuaBasicTexture.h"
#include "LuaMath.h"

class LuaContinuousScreenCapture
{
public:
	class ContinuousBasicScreenCapture
	{
	public:
		ContinuousBasicScreenCapture(luabind::object const& table);

		void SetCameraMatrix(LuaMath::Matrix4x4 mat);
		void SetPrespectiveMatrix(LuaMath::Matrix4x4 mat);
		LuaBasicTexture GetTexture();

		std::string ID;
		std::string TextureID;

		static void Register(lua_State *lua);
	};

	class ContinuousDepthScreenCapture
	{
	public:
		ContinuousDepthScreenCapture(luabind::object const& table);
		
		void SetCameraMatrix(LuaMath::Matrix4x4 mat);
		void SetPrespectiveMatrix(LuaMath::Matrix4x4 mat);
		LuaBasicTexture GetTexture();

		std::string ID;
		std::string TextureID;

		static void Register(lua_State *lua);
	};

	class ContinuousCubeScreenCapture
	{
	public:
		ContinuousCubeScreenCapture(luabind::object const& table);
		
		void SetEye(LuaMath::Vector4 mat);
		LuaBasicTexture GetTexture();

		std::string ID;
		std::string TextureID;

		static void Register(lua_State *lua);
	};


	static inline void RegisterAllLuaFunction(lua_State *lua)
	{
		ContinuousBasicScreenCapture::Register(lua);
		ContinuousDepthScreenCapture::Register(lua);
		ContinuousCubeScreenCapture::Register(lua);
	}
};

#endif //__LuaContinuousScreenCapture__
