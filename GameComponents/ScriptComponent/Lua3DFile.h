#ifndef __Lua3DFile__
#define __Lua3DFile__

#include <Lua.hpp>
#include <luabind\luabind.hpp>
#include <memory>
#include <vector>
#include <Model.h>
#include <Animation.h>
#include "LuaMath.h"

namespace Lua3DFile
{
	namespace Model
	{
		class Vertices
		{
		public:
			Vertices();
			Vertices(luabind::object const& table);
			Vertices(CHL::Model::VerticesInfo vertices);
			operator CHL::Model::VerticesInfo();

			LuaMath::Vector4 Point;
			LuaMath::Vector4 Normal;
			LuaMath::Vector4 Texture;

			static void Register(lua_State *lua);
		};
		class Model
		{
		public:
			Model();
			Model(std::shared_ptr<CHL::Model> model);
			operator std::shared_ptr<CHL::Model>();

			void SetVertices(luabind::object const& table);
			luabind::object GetVertices();
			void SeFaces(luabind::object const& table);
			luabind::object GetFaces();

			std::shared_ptr<CHL::Model> model;

			static void Register(lua_State *lua);
		};
	}
	namespace Animation
	{
		class Animation
		{
		public:
			Animation();
			Animation(std::shared_ptr<CHL::Animation> anim);
			operator std::shared_ptr<CHL::Animation>();

			std::shared_ptr<CHL::Animation> anim;

			static void Register(lua_State *lua);
		};
	}

	void LoadScene(std::string fileName);

	void RegisterAllLuaFunction(lua_State *lua);
};

#endif //__Lua3DFile__