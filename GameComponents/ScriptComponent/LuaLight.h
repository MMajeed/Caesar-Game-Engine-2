#ifndef __LuaLight__
#define __LuaLight__

#include <Lua.hpp>
#include <luabind\luabind.hpp>
#include "LuaMath.h"
#include <string>

class LuaLight
{
public:
	class Light
	{
	public:
		LuaMath::Vector4 GetDiffuse();
		void SetDiffuse(LuaMath::Vector4 vec);

		LuaMath::Vector4 GetAmient();
		void SetAmbient(LuaMath::Vector4 vec);

		LuaMath::Vector4 GetSpecular();
		void SetSpecular(LuaMath::Vector4 vec);

		std::string ID;
	};

	class DirectionalLight : public Light
	{
	public:
		DirectionalLight(luabind::object const& table);
		
		LuaMath::Vector4 GetDirection();
		void SetDirection(LuaMath::Vector4 vec);

		static void Register(lua_State *lua);
	};

	class PointLight : public Light
	{
	public:
		PointLight(luabind::object const& table);

		LuaMath::Vector4 GetPosition();
		void SetPosition(LuaMath::Vector4 vec);

		double GetRange();
		void SetRange(double val);

		LuaMath::Vector4 GetAttenuation();
		void SetAttenuation(LuaMath::Vector4 vec);

		static void Register(lua_State *lua);
	};

	class SpotLight : public Light
	{
	public:
		SpotLight(luabind::object const& table);

		LuaMath::Vector4 GetPosition();
		void SetPosition(LuaMath::Vector4 vec);

		double GetRange();
		void SetRange(double val);

		LuaMath::Vector4 GetDirection();
		void SetDirection(LuaMath::Vector4 vec);

		double GetSpot();
		void SetSpot(double val);

		LuaMath::Vector4 GetAttenuation();
		void SetAttenuation(LuaMath::Vector4 vec);

		void ApplyShadow();
		void RemoveShadow();
		bool GetShadowState();

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
