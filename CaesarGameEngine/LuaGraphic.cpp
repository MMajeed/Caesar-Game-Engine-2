#include "LuaGraphic.h"

#include <exception>
#include <Converter.h>
#include <boost/uuid/uuid_generators.hpp> // generators
#include <boost/uuid/uuid_io.hpp>         // streaming operators etc.

#include "LuaManager.h"
#include "ClearScreenMessage.h"
#include "GraphicManager.h"
#include "AddBasicDrawableMessage.h"
#include <Model.h>
#include "Keys.h"

void LuaGraphic::ClearScreen::Action(double x, double y, double z)
{
	boost::numeric::ublas::vector<double> newColour(3);

	newColour(0) = x;	// Get the 1 paramter
	newColour(1) = y;	// Get the 2 paramter
	newColour(2) = z;	// Get the 3 paramter

	std::shared_ptr<ClearScreenMessage> msg(new ClearScreenMessage(newColour));

	GraphicManager::GetInstance().SubmitMessage(msg);
}

void LuaGraphic::ClearScreen::Register(lua_State *lua)
{
	luabind::module(lua) [
		luabind::def("ClearScreen", LuaGraphic::ClearScreen::Action)
	  ];
}

std::string LuaGraphic::AddObject::AddBasicObject(luabind::object const& table)
{
	std::map<std::string, std::string> mapKeys;
	if (luabind::type(table) != LUA_TTABLE)
    {	
		throw std::exception("Wrong paramter for AddBasicObject, please send in a table with these values inside of them: \nModelFile\nVertexShaderFile\nPixelShaderFile\nTextureFile");
    }

	for (luabind::iterator it(table); it != luabind::iterator(); ++it)
	{ 
		mapKeys[luabind::object_cast<std::string>(it.key())] = luabind::object_cast<std::string>(*it);
	}
	std::string fileName = mapKeys[Keys::MODELFILE];
	std::string vertexFileName = mapKeys[Keys::VERTEXSHADERFILE];
	std::string pixelFileName = mapKeys[Keys::PIXELSHADERFILE];
	std::string texture = mapKeys[Keys::TEXTUREFILE];

	Model m(fileName);

	std::shared_ptr<AddBasicDrawableMessage> msg(
			new AddBasicDrawableMessage(m, vertexFileName, "VS", "vs_4_0", pixelFileName, "PS", "ps_4_0", texture ));

	GraphicManager::GetInstance().SubmitMessage(msg);

	msg->WaitTillProcccesed();

	return msg->ID;
}
void LuaGraphic::AddObject::Register(lua_State *lua)
{
	luabind::module(lua) [
		luabind::def("AddBasicDrawableObject", LuaGraphic::AddObject::AddBasicObject)
	  ];
}