#include "LuaModel.h"

#include "ScriptManager.h"
#include "Resource.h"
#include <Model.h>
#include <3DLoader.h>
#include <string>
#include <Logger.h>

namespace LuaModel
{
	//------------------------- Start Model ---------------------------------------//
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

	unsigned int Model::GetNumberFaces()
	{
		return this->model->NumberOfFaces;
	}
	void Model::SetNumberFaces(const luabind::object& v)
	{
		if(boost::optional<unsigned int> value = luabind::object_cast_nothrow<unsigned int>(v))
			this->model->NumberOfFaces = *value;
		else
			Logger::LogError("Wrong paramter type");
	}

	void Model::SetFaces(luabind::object const& table)
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
		luabind::object returnValue = luabind::newtable(Resource::lua);

		for(std::size_t i = 0; i < this->model->Faces.size(); ++i)
		{
			returnValue[i] = this->model->Faces[i];
		}

		return returnValue;
	}

	void Model::SetVertices(luabind::object const& table)
	{
		if(luabind::type(table) != LUA_TTABLE)
			Logger::LogError("Wrong paramter for Model::SeVertices, please send in a table");

		this->model->Vertices.clear();
		for(luabind::iterator it(table);
			it != luabind::iterator();
			++it)
		{
			CML::Vec4 ver = luabind::object_cast<LuaMath::Vector4>(*it);
			this->model->Vertices.push_back(ver);
		}
	}
	luabind::object Model::GetVertices()
	{
		luabind::object returnValue = luabind::newtable(Resource::lua);

		for(std::size_t i = 0; i < this->model->Vertices.size(); ++i)
		{
			returnValue[i] = this->model->Vertices[i];
		}

		return returnValue;
	}

	void Model::SetNormal(luabind::object const& table)
	{
		if(luabind::type(table) != LUA_TTABLE)
			Logger::LogError("Wrong paramter for Model::SeNormal, please send in a table");

		this->model->Normal.clear();
		for(luabind::iterator it(table);
			it != luabind::iterator();
			++it)
		{
			CML::Vec4 ver = luabind::object_cast<LuaMath::Vector4>(*it);
			this->model->Normal.push_back(ver);
		}
	}
	luabind::object Model::GetNormal()
	{
		luabind::object returnValue = luabind::newtable(Resource::lua);

		for(std::size_t i = 0; i < this->model->Normal.size(); ++i)
		{
			returnValue[i] = this->model->Normal[i];
		}

		return returnValue;
	}

	void Model::SetTangents(luabind::object const& table)
	{
		if(luabind::type(table) != LUA_TTABLE)
			Logger::LogError("Wrong paramter for Model::SeTangents, please send in a table");

		this->model->Tangents.clear();
		for(luabind::iterator it(table);
			it != luabind::iterator();
			++it)
		{
			CML::Vec4 ver = luabind::object_cast<LuaMath::Vector4>(*it);
			this->model->Tangents.push_back(ver);
		}
	}
	luabind::object Model::GetTangents()
	{
		luabind::object returnValue = luabind::newtable(Resource::lua);

		for(std::size_t i = 0; i < this->model->Tangents.size(); ++i)
		{
			returnValue[i] = this->model->Tangents[i];
		}

		return returnValue;
	}

	void Model::SetBitangents(luabind::object const& table)
	{
		if(luabind::type(table) != LUA_TTABLE)
			Logger::LogError("Wrong paramter for Model::SeBitangents, please send in a table");

		this->model->Bitangents.clear();
		for(luabind::iterator it(table);
			it != luabind::iterator();
			++it)
		{
			CML::Vec4 ver = luabind::object_cast<LuaMath::Vector4>(*it);
			this->model->Bitangents.push_back(ver);
		}
	}
	luabind::object Model::GetBitangents()
	{
		luabind::object returnValue = luabind::newtable(Resource::lua);

		for(std::size_t i = 0; i < this->model->Bitangents.size(); ++i)
		{
			returnValue[i] = this->model->Bitangents[i];
		}

		return returnValue;
	}

	void Model::SetColor(luabind::object const& table)
	{
		if(luabind::type(table) != LUA_TTABLE)
			Logger::LogError("Wrong paramter for Model::SeColor, please send in a table");

		this->model->Color.clear();
		for(luabind::iterator it(table);
			it != luabind::iterator();
			++it)
		{
			CML::Vec4 ver = luabind::object_cast<LuaMath::Vector4>(*it);
			this->model->Color.push_back(ver);
		}
	}
	luabind::object Model::GetColor()
	{
		luabind::object returnValue = luabind::newtable(Resource::lua);

		for(std::size_t i = 0; i < this->model->Color.size(); ++i)
		{
			returnValue[i] = this->model->Color[i];
		}

		return returnValue;
	}

	void Model::SetTexture(luabind::object const& table)
	{
		if(luabind::type(table) != LUA_TTABLE)
			Logger::LogError("Wrong paramter for Model::SeTexture, please send in a table");

		this->model->Texture.clear();
		for(luabind::iterator it(table);
			it != luabind::iterator();
			++it)
		{
			CML::Vec4 ver = luabind::object_cast<LuaMath::Vector4>(*it);
			this->model->Texture.push_back(ver);
		}
	}
	luabind::object Model::GetTexture()
	{
		luabind::object returnValue = luabind::newtable(Resource::lua);

		for(std::size_t i = 0; i < this->model->Texture.size(); ++i)
		{
			returnValue[i] = this->model->Texture[i];
		}

		return returnValue;
	}

	void Model::Register(lua_State *lua)
	{
		luabind::module(lua)[
			luabind::class_<LuaModel::Model>("Model")
				.def(luabind::constructor<>())
				.property("NumberFaces", &LuaModel::Model::GetNumberFaces, &LuaModel::Model::SetNumberFaces)
				.property("Faces", &LuaModel::Model::GetFaces, &LuaModel::Model::SetFaces)
				.property("Vertices", &LuaModel::Model::GetVertices, &LuaModel::Model::SetVertices)
				.property("Normal", &LuaModel::Model::GetNormal, &LuaModel::Model::SetNormal)
				.property("Tangents", &LuaModel::Model::GetTangents, &LuaModel::Model::SetTangents)
				.property("Bitangents", &LuaModel::Model::GetBitangents, &LuaModel::Model::SetBitangents)
				.property("Color", &LuaModel::Model::GetColor, &LuaModel::Model::SetColor)
				.property("Texture", &LuaModel::Model::GetTexture, &LuaModel::Model::SetTexture)
		];
	}
	//-----------------------------End Model--------------------------------------//

	void RegisterAllLuaFunction(lua_State *lua)
	{
		LuaModel::Model::Register(lua);
	}
}