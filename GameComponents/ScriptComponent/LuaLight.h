#ifndef __LuaLight__
#define __LuaLight__

#include <Lua.hpp>
#include <luabind\luabind.hpp>
#include "LuaUblas.h"
#include <string>

class LuaLight
{
public:
	class Light
	{
	public:
		LuaUblas::Vector4 GetDiffuse();
		void SetDiffuse(LuaUblas::Vector4 vec);

		LuaUblas::Vector4 GetAmient();
		void SetAmbient(LuaUblas::Vector4 vec);

		LuaUblas::Vector4 GetSpecular();
		void SetSpecular(LuaUblas::Vector4 vec);

		int GetSlot();
		void SetSlot(int i);

		std::string ID;
	};

	class DirectionalLight : public Light
	{
	public:
		DirectionalLight(int slot, LuaUblas::Vector4 diffuse, LuaUblas::Vector4 ambient, LuaUblas::Vector4 specular, LuaUblas::Vector4 direction );
		
		LuaUblas::Vector4 GetDirection();
		void SetDirection(LuaUblas::Vector4 vec);

		static void Register(lua_State *lua);
	};

	class PointLight : public Light
	{
	public:
		PointLight(int slot, LuaUblas::Vector4 diffuse, LuaUblas::Vector4 ambient, LuaUblas::Vector4 specular, LuaUblas::Vector4 position, double range, LuaUblas::Vector4 att);

		LuaUblas::Vector4 GetPosition();
		void SetPosition(LuaUblas::Vector4 vec);

		double GetRange();
		void SetRange(double val);

		LuaUblas::Vector4 GetAttenuation();
		void SetAttenuation(LuaUblas::Vector4 vec);

		static void Register(lua_State *lua);
	};

	class SpotLight : public Light
	{
	public:
		SpotLight(int slot, LuaUblas::Vector4 diffuse, LuaUblas::Vector4 ambient, LuaUblas::Vector4 specular, LuaUblas::Vector4 position, double range, LuaUblas::Vector4 Direction, double spot, LuaUblas::Vector4  att);

		LuaUblas::Vector4 GetPosition();
		void SetPosition(LuaUblas::Vector4 vec);

		double GetRange();
		void SetRange(double val);

		LuaUblas::Vector4 GetDirection();
		void SetDirection(LuaUblas::Vector4 vec);

		double GetSpot();
		void SetSpot(double val);

		LuaUblas::Vector4 GetAttenuation();
		void SetAttenuation(LuaUblas::Vector4 vec);

		static void Register(lua_State *lua);
	};

	static inline void RegisterAllLuaFunction(lua_State *lua)
	{
		DirectionalLight::Register(lua);
		PointLight::Register(lua);
		SpotLight::Register(lua);
	}
};

#endif //__LuaLight__
