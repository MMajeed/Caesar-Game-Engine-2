#include "LuaBasicDrawableObject.h"

#include <exception>
#include <Converter.h>
#include "LuaManager.h"
#include <GraphicCommunicator\BasicDrawableConfig.h>
#include <GraphicCommunicator\GraphicCommunicator.h>
#include <Model.h>
#include <Keys.h>


LuaBasicDrawableObject::LuaBasicDrawableObject(luabind::object const& table)
{
	if (luabind::type(table) != LUA_TTABLE)
		throw std::exception("Wrong paramter for AddBasicObject, please send in a table");

	std::string fileName = "";
	std::string vertexFileName = "";
	std::string pixelFileName = "";
	int cullMode = 3 ;
	int fillMode = 3;
	bool antialiasedLine = true; 
	bool multisampleEnable = true;

	for (luabind::iterator it(table);
		it != luabind::iterator();
		++it)
	{
		std::string key = luabind::object_cast<std::string>(it.key());

		     if (key == Keys::BasicDrawable::MODELFILE)			{ fileName = luabind::object_cast<std::string>(*it); }
		else if (key == Keys::BasicDrawable::VERTEXSHADERFILE)	{ vertexFileName = luabind::object_cast<std::string>(*it); }
		else if (key == Keys::BasicDrawable::PIXELSHADERFILE)	{ pixelFileName = luabind::object_cast<std::string>(*it); }
		else if (key == Keys::BasicDrawable::CULLMODE)			{ cullMode = luabind::object_cast<int>(*it); }
		else if (key == Keys::BasicDrawable::FILLMODE)			{ fillMode = luabind::object_cast<int>(*it); }
		else if (key == Keys::BasicDrawable::ANTIALIASEDLINE)	{ antialiasedLine = luabind::object_cast<bool>(*it); }
		else if (key == Keys::BasicDrawable::MULTISAMPLEENABLE)	{ multisampleEnable = luabind::object_cast<bool>(*it); }
	}

	if (fileName.empty()) throw std::exception( (Keys::BasicDrawable::MODELFILE + " value was missing for BasicDrawableObject ").c_str() );
	if (vertexFileName.empty()) throw std::exception((Keys::BasicDrawable::VERTEXSHADERFILE + " value was missing for BasicDrawableObject").c_str());
	if (pixelFileName.empty()) throw std::exception((Keys::BasicDrawable::PIXELSHADERFILE + " value was missing for BasicDrawableObject").c_str());


	Model m(fileName);

	std::shared_ptr<BasicDrawableConfig::AddBasicDrawableMessage> msg(
		new BasicDrawableConfig::AddBasicDrawableMessage
				(m, vertexFileName, pixelFileName,
				static_cast<BasicDrawableConfig::CULL_MODE>(cullMode),
				static_cast<BasicDrawableConfig::FILL_MODE>(fillMode),
				antialiasedLine, 
				multisampleEnable ));

	GraphicCommunicator::SubmitMessage(msg);

	this->ID = msg->ID;
}

void LuaBasicDrawableObject::ChangeRastersizerState(int cullMode, int fillMode, bool antialiasedLine, bool multisampleEnable)
{	
	std::shared_ptr<BasicDrawableConfig::ChangeRastersizerState> msg(
		new BasicDrawableConfig::ChangeRastersizerState(
				this->ID,
				static_cast<BasicDrawableConfig::CULL_MODE>(cullMode),
				static_cast<BasicDrawableConfig::FILL_MODE>(fillMode),
				antialiasedLine, 
				multisampleEnable));

	GraphicCommunicator::SubmitMessage(msg);
}

void LuaBasicDrawableObject::Register(lua_State *lua)
{
	luabind::module(lua) [
		luabind::class_<LuaBasicDrawableObject>("BasicDrawableObject")
		  .def(luabind::constructor<luabind::object const&>())
		  .def_readonly("ID", &LuaBasicDrawableObject::ID)
		  .def("ChangeRastersizerState", &LuaBasicDrawableObject::ChangeRastersizerState)
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