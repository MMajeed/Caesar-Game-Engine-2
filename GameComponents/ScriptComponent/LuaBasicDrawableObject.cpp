#include "LuaBasicDrawableObject.h"

#include <exception>
#include <Converter.h>
#include "LuaManager.h"
#include <GraphicCommunicator\BasicDrawableConfig.h>
#include <Model.h>
#include <Keys.h>
#include "LuaModel.h"
#include <stdexcept>

LuaBasicDrawableObject::LuaBasicDrawableObject(luabind::object const& table)
{
	if (luabind::type(table) != LUA_TTABLE)
		throw std::invalid_argument("Wrong paramter for AddBasicObject, please send in a table");

	std::shared_ptr<CHL::Model> model;
	std::string vertexFileName = "";
	std::string pixelFileName = "";
	int cullMode = 3 ;
	int fillMode = 3;

	for (luabind::iterator it(table);
		it != luabind::iterator();
		++it)
	{
		std::string key = luabind::object_cast<std::string>(it.key());

		     if (key == Keys::BasicDrawable::MODELFILE)			{ model = luabind::object_cast<LuaModel::Model>(*it); }
		else if (key == Keys::BasicDrawable::VERTEXSHADERFILE)	{ vertexFileName = luabind::object_cast<std::string>(*it); }
		else if (key == Keys::BasicDrawable::PIXELSHADERFILE)	{ pixelFileName = luabind::object_cast<std::string>(*it); }
		else if (key == Keys::BasicDrawable::CULLMODE)			{ cullMode = luabind::object_cast<int>(*it); }
		else if (key == Keys::BasicDrawable::FILLMODE)			{ fillMode = luabind::object_cast<int>(*it); }
	}

	if(vertexFileName.empty()) throw std::invalid_argument(Keys::BasicDrawable::VERTEXSHADERFILE + " value was missing for BasicDrawableObject");
	if(pixelFileName.empty()) throw std::invalid_argument(Keys::BasicDrawable::PIXELSHADERFILE + " value was missing for BasicDrawableObject");

	this->ID =  BasicDrawableConfig::Create(model, 
											vertexFileName, pixelFileName,
											static_cast<BasicDrawableConfig::CULL_MODE>(cullMode),
											static_cast<BasicDrawableConfig::FILL_MODE>(fillMode));
}

void LuaBasicDrawableObject::ChangeRastersizerState(int cullMode, int fillMode)
{	
	BasicDrawableConfig::ChangeRastersizerState(this->ID,
												static_cast<BasicDrawableConfig::CULL_MODE>(cullMode),
												static_cast<BasicDrawableConfig::FILL_MODE>(fillMode));
}

void LuaBasicDrawableObject::Release()
{
	BasicDrawableConfig::Release(this->ID);
	this->ID = "";
}

void LuaBasicDrawableObject::Register(lua_State *lua)
{
	luabind::module(lua) [
		luabind::class_<LuaBasicDrawableObject>("BasicDrawableObject")
		  .def(luabind::constructor<luabind::object const&>())
		  .def_readonly("ID", &LuaBasicDrawableObject::ID)
		  .def("ChangeRastersizerState", &LuaBasicDrawableObject::ChangeRastersizerState)
		  .def("Release", &LuaBasicDrawableObject::Release)
	  ];

	luabind::object cullMode = luabind::newtable(lua);	
	cullMode["None"] = 1;
	cullMode["Front"] = 2;
	cullMode["Back"] = 3;
	luabind::globals(lua)["CullMode"] = cullMode;

	luabind::object fillMode = luabind::newtable(lua);	
	fillMode["Wireframe"] = 2;
	fillMode["Solid"] = 3;
	luabind::globals(lua)["FillMode"] = fillMode;
}