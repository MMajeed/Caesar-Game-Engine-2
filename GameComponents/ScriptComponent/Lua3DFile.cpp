#include "Lua3DFile.h"

#include "LuaManager.h"
#include <Model.h>
#include <3DLoader.h>
#include <string>
#include <Logger.h>

namespace Lua3DFile
{
	namespace Model
	{
		//---------------------------------------------------------------------------//
		Model::Model()
		{
			this->model = std::shared_ptr<CHL::Model>(new CHL::Model());
		}
		Model::Model(std::shared_ptr<CHL::Model> model)
		{
			this->model = model;
		}
		Model::operator std::shared_ptr<CHL::Model>()
		{
			return this->model;
		}
		void Model::SetVertices(luabind::object const& table)
		{
			if(luabind::type(table) != LUA_TTABLE)
				Logger::LogError("Wrong paramter for Model::SetVertices, please send in a table");

			this->model->Vertices.clear();
			for(luabind::iterator it(table);
				it != luabind::iterator();
				++it)
			{
				Vertices ver = luabind::object_cast<Vertices>(*it);
				this->model->Vertices.push_back(ver);
			}
		}
		luabind::object Model::GetVertices()
		{
			luabind::object returnValue = luabind::newtable(LuaManager::GetInstance().lua);

			for(std::size_t i = 0; i < this->model->Vertices.size(); ++i)
			{
				returnValue[i] = Vertices(this->model->Vertices[i]);
			}

			return returnValue;
		}

		void Model::SeFaces(luabind::object const& table)
		{
			if(luabind::type(table) != LUA_TTABLE)
				Logger::LogError("Wrong paramter for Model::SeFaces, please send in a table");

			this->model->Faces.clear();
			for(luabind::iterator it(table);
				it != luabind::iterator();
				++it)
			{
				int ver = luabind::object_cast<int>(*it);
				this->model->Faces.push_back(ver);
			}
		}
		luabind::object Model::GetFaces()
		{
			luabind::object returnValue = luabind::newtable(LuaManager::GetInstance().lua);

			for(std::size_t i = 0; i < this->model->Faces.size(); ++i)
			{
				returnValue[i] = this->model->Faces[i];
			}

			return returnValue;
		}

		void Model::Register(lua_State *lua)
		{
			luabind::module(lua)[
				luabind::class_<Lua3DFile::Model::Model>("Model")
					.def(luabind::constructor<>())
					.property("Vertices", &Lua3DFile::Model::Model::GetVertices, &Lua3DFile::Model::Model::SetVertices)
					.property("Faces", &Lua3DFile::Model::Model::GetFaces, &Lua3DFile::Model::Model::SeFaces)
			];
		}
		//---------------------------------------------------------------------------//

		Vertices::Vertices()
		{
			this->Point = {0.0, 0.0, 0.0, 0.0};
			this->Normal = {0.0, 0.0, 0.0, 0.0};
			this->Texture = {0.0, 0.0, 0.0, 0.0};
		}
		Vertices::Vertices(luabind::object const& table)
		{
			if(luabind::type(table) != LUA_TTABLE)
				Logger::LogError("Wrong paramter for Vertices, please send in a table");

			this->Point = {0.0, 0.0, 0.0, 0.0};
			this->Normal = {0.0, 0.0, 0.0, 0.0};
			this->Texture = {0.0, 0.0, 0.0, 0.0};

			for(luabind::iterator it(table);
				it != luabind::iterator();
				++it)
			{
				std::string key = luabind::object_cast<std::string>(it.key());

				if(key == "Point")		{ this->Point = luabind::object_cast<LuaMath::Vector4>(*it); }
				else if(key == "Normal")	{ this->Normal = luabind::object_cast<LuaMath::Vector4>(*it); }
				else if(key == "Texture")	{ this->Texture = luabind::object_cast<LuaMath::Vector4>(*it); }
			}
		}
		Vertices::Vertices(CHL::Model::VerticesInfo vertices)
			: Point(vertices.Point), Normal(vertices.Normal), Texture(vertices.Texture)
		{
		}
		Vertices::operator CHL::Model::VerticesInfo()
		{
			CHL::Model::VerticesInfo returnValue;
			returnValue.Point = this->Point.vector;
			returnValue.Normal = this->Normal.vector;
			returnValue.Texture = this->Texture.vector;
			return returnValue;
		}

		void Vertices::Register(lua_State *lua)
		{
			luabind::module(lua)[
				luabind::class_<Lua3DFile::Model:: Vertices>("Vertice")
					.def(luabind::constructor<>())
					.def(luabind::constructor<luabind::object const&>())
					.property("Point", &Lua3DFile::Model::Vertices::Point)
					.property("Normal", &Lua3DFile::Model::Vertices::Normal)
					.property("Texture", &Lua3DFile::Model::Vertices::Texture)
			];
		}
		//---------------------------------------------------------------------------//
	}

	//---------------------------------------------------------------------------//

	namespace Animation
	{
		//---------------------------------------------------------------------------//
		Animation::Animation()
		{
			this->anim = std::shared_ptr<CHL::Animation>(new CHL::Animation());
		}
		Animation::Animation(std::shared_ptr<CHL::Animation> anim)
		{
			this->anim = anim;
		}
		Animation::operator std::shared_ptr<CHL::Animation>()
		{
			return this->anim;
		}
		void Animation::Register(lua_State *lua)
		{
			luabind::module(lua)[
				luabind::class_<Lua3DFile::Animation::Animation>("Animation")
					.def(luabind::constructor<>())
			];
		}
		//---------------------------------------------------------------------------//
	}

	//---------------------------------------------------------------------------//
	void LoadScene(std::string fileName)
	{
		lua_State *lua = LuaManager::GetInstance().lua;
		luabind::object outModels = luabind::newtable(lua);
		luabind::object outAnimation = luabind::newtable(lua);

		std::vector<std::shared_ptr<CHL::Model>> models;
		std::vector<std::shared_ptr<CHL::Animation>> animation;
		CHL::Load3DFile(fileName, models, animation);
		for(std::size_t i = 0; i < models.size(); ++i)
		{
			outModels[i + 1] = Lua3DFile::Model::Model(models[i]);
		}
		for(std::size_t i = 0; 0 < animation.size(); ++i)
		{
			outAnimation[i + 1] = Lua3DFile::Animation::Animation(animation[i]);
		}
		outModels.push(lua);
		outAnimation.push(lua);
	}
	//---------------------------------------------------------------------------//

	void Lua3DFile::RegisterAllLuaFunction(lua_State *lua)
	{
		Lua3DFile::Model::Model::Register(lua);
		Lua3DFile::Model::Vertices::Register(lua);

		Lua3DFile::Animation::Animation::Register(lua);

		luabind::module(lua)[
			luabind::def("LoadScene", Lua3DFile::LoadScene)
		];
	}
}