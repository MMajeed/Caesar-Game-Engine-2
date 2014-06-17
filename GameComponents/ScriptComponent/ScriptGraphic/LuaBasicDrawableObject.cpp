#include "LuaBasicDrawableObject.h"

#include <exception>
#include <Converter.h>
#include "ScriptManager.h"
#include <GraphicCommunicator\BasicDrawableConfig.h>
#include <Keys.h>
#include <stdexcept>
#include <Logger.h>

namespace LuaBasicDrawableObject
{
	
	BasicDrawableObject::BasicDrawableObject(luabind::object const& table)
	{
		if(luabind::type(table) != LUA_TTABLE)
			Logger::LogError("Wrong paramter for AddBasicObject, please send in a table");

		std::shared_ptr<CHL::Model> model;
		std::string vertexFileName = "Assets/ShaderFiles/VS_0_Regular.cso";
		std::string pixelFileName = "Assets/ShaderFiles/PS_0_Generic.cso";
		std::string geometryFileName = "";
		int cullMode = 3;
		int fillMode = 3;
		int dimension = 3;


		for(luabind::iterator it(table);
			it != luabind::iterator();
			++it)
		{
 			std::string key = luabind::object_cast<std::string>(it.key());

 				 if(key == Keys::BasicDrawable::MODEL)				{ model = luabind::object_cast<LuaModel::Model>(*it); }
			else if(key == Keys::BasicDrawable::VERTEXSHADERFILE)	{ vertexFileName = luabind::object_cast<std::string>(*it); }
			else if(key == Keys::BasicDrawable::PIXELSHADERFILE)	{ pixelFileName = luabind::object_cast<std::string>(*it); }
			else if(key == Keys::BasicDrawable::GEOMETRYSHADERFILE)	{ geometryFileName = luabind::object_cast<std::string>(*it); }
			else if(key == Keys::BasicDrawable::CULLMODE)			{ cullMode = luabind::object_cast<int>(*it); }
			else if(key == Keys::BasicDrawable::FILLMODE)			{ fillMode = luabind::object_cast<int>(*it); }
			else if(key == Keys::BasicDrawable::DIMENSION)			{ dimension = luabind::object_cast<int>(*it); }
		}
		
		if(!model){	model = std::shared_ptr<CHL::Model>(new CHL::Model());	}

		if(dimension == 3)
		{
			this->ID = BasicDrawableConfig::Create(model,
												   vertexFileName, pixelFileName, geometryFileName,
												   static_cast<BasicDrawableConfig::CULL_MODE>(cullMode),
												   static_cast<BasicDrawableConfig::FILL_MODE>(fillMode));
		}
		else if(dimension == 2)
		{
			this->ID = BasicDrawableConfig::Create2D(model,
													 vertexFileName, pixelFileName, geometryFileName,
													 static_cast<BasicDrawableConfig::CULL_MODE>(cullMode),
													 static_cast<BasicDrawableConfig::FILL_MODE>(fillMode));
		}
	}
	void BasicDrawableObject::ChangeModel(LuaModel::Model model)
	{
		BasicDrawableConfig::ChangeModel(this->ID, model.model);
	}
	void BasicDrawableObject::ChangeRastersizerState(int cullMode, int fillMode)
	{
		BasicDrawableConfig::ChangeRastersizerState(this->ID,
													static_cast<BasicDrawableConfig::CULL_MODE>(cullMode),
													static_cast<BasicDrawableConfig::FILL_MODE>(fillMode));
	}
	void BasicDrawableObject::ChangeVS(std::string fileName)
	{
		BasicDrawableConfig::ChangeVS(this->ID, fileName);
	}
	void BasicDrawableObject::ChangeGS(std::string fileName)
	{
		BasicDrawableConfig::ChangeGS(this->ID, fileName);
	}
	void BasicDrawableObject::ChangePS(std::string fileName)
	{
		BasicDrawableConfig::ChangePS(this->ID, fileName);
	}
	void BasicDrawableObject::Release()
	{
		BasicDrawableConfig::Release(this->ID);
		this->ID = "";
	}
	void BasicDrawableObject::Register(lua_State *lua)
	{
		luabind::module(lua)[
			luabind::class_<BasicDrawableObject, GenericLuaObject>("BasicDrawableObject")
				.def(luabind::constructor<luabind::object const&>())
				.def("ChangeRastersizerState", &BasicDrawableObject::ChangeRastersizerState)
				.def("ChangeModel", &BasicDrawableObject::ChangeModel)
				.def("ChangeVS", &BasicDrawableObject::ChangeVS)
				.def("ChangeGS", &BasicDrawableObject::ChangeGS)
				.def("ChangePS", &BasicDrawableObject::ChangePS)
				.def("Release", &BasicDrawableObject::Release)
		];
	}
	//***********************************************************************//
	void RegisterAllLuaFunction(lua_State *lua)
	{
		BasicDrawableObject::Register(lua);

		luabind::object cullMode = luabind::newtable(lua);
		cullMode["None"] = 1;
		cullMode["Front"] = 2;
		cullMode["Back"] = 3;
		luabind::globals(lua)["CullMode"] = cullMode;

		luabind::object fillMode = luabind::newtable(lua);
		fillMode["Wireframe"] = 2;
		fillMode["Solid"] = 3;
		luabind::globals(lua)["FillMode"] = fillMode;

		luabind::object dimension = luabind::newtable(lua);
		dimension["2D"] = 2;
		dimension["3D"] = 3;
		luabind::globals(lua)["Dimension"] = dimension;
	}
}