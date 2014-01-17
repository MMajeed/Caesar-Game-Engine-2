#include "LuaModel.h"

#include "LuaManager.h"
#include <Model.h>
#include <string>
#include <Logger.h>

namespace LuaModel
{
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
			LuaModel::Vertices ver = luabind::object_cast<LuaModel::Vertices>(*it);
			this->model->Vertices.push_back(ver);
		}
	}
	luabind::object Model::GetVertices()
	{
		luabind::object returnValue = luabind::newtable(LuaManager::GetInstance().lua);

		for(std::size_t i = 0; i < this->model->Vertices.size(); ++i)
		{
			returnValue[i] = LuaModel::Vertices(this->model->Vertices[i]);
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
			luabind::class_<LuaModel::Model>("Model")
				.def(luabind::constructor<>())
				.property("Vertices", &LuaModel::Model::GetVertices, &LuaModel::Model::SetVertices)
				.property("Faces", &LuaModel::Model::GetFaces, &LuaModel::Model::SeFaces)
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

	void LuaModel::Vertices::Register(lua_State *lua)
	{
		luabind::module(lua)[
			luabind::class_<LuaModel::Vertices>("Vertice")
				.def(luabind::constructor<>())
				.def(luabind::constructor<luabind::object const&>())
				.property("Point", &LuaModel::Vertices::Point)
				.property("Normal", &LuaModel::Vertices::Normal)
				.property("Texture", &LuaModel::Vertices::Texture)
		];
	}
	//---------------------------------------------------------------------------//

	Model LuaModel::GetFirstModel(std::string fileName)
	{
		LuaModel::Model returnValue(std::make_shared<CHL::Model>(CHL::LoadModels(fileName)[0]));
		return returnValue;
	}
	luabind::object LuaModel::GetScene(std::string fileName)
	{
		luabind::object returnValue = luabind::newtable(LuaManager::GetInstance().lua);

		std::vector<CHL::Model> models = CHL::LoadModels(fileName);
		for(std::size_t i = 0; i < models.size(); ++i)
		{
			returnValue[i] = LuaModel::Model(std::make_shared<CHL::Model>(models[i]));
		}
		return returnValue;
	}
	//---------------------------------------------------------------------------//

	void LuaModel::RegisterAllLuaFunction(lua_State *lua)
	{
		LuaModel::Model::Register(lua);
		LuaModel::Vertices::Register(lua);
		luabind::module(lua)[
			luabind::def("LoadModel", LuaModel::GetFirstModel),
				luabind::def("LoadScene", LuaModel::GetScene)
		];
	}
}