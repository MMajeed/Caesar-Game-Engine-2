#include "LuaManager.h"
#include "ClearScreenMessage.h"
#include "LuaGraphic.h"
#include "GraphicManager.h"
#include "AddBasicDrawableMessage.h"
#include "Model.h"
#include <Converter.h>
#include <boost/uuid/uuid_generators.hpp> // generators
#include <boost/uuid/uuid_io.hpp>         // streaming operators etc.

void LuaGraphic::ClearScreen::Action(double x, double y, double z)
{
	boost::numeric::ublas::vector<double> newColour(3);

	newColour(0) = x;	// Get the 1 paramter
	newColour(1) = y;	// Get the 2 paramter
	newColour(2) = z;	// Get the 3 paramter

	std::shared_ptr<ClearScreenMessage> msg(new ClearScreenMessage(newColour));

	GraphicManager().GetInstance().SubmitMessage(msg);
}

void LuaGraphic::ClearScreen::Register(lua_State *lua)
{
	luabind::module(lua) [
		luabind::def("ClearScreen", LuaGraphic::ClearScreen::Action)
	  ];
}

std::string LuaGraphic::AddObject::AddBasicObject(std::string fileName,
												  std::string vertexFileName,
												  std::string pixelFileName,
												  std::string texture)
{
	std::string newID = CHL::ToString(boost::uuids::random_generator()());
	Model m(fileName);

	std::shared_ptr<AddBasicDrawableMessage> msg(
			new AddBasicDrawableMessage(newID, m, vertexFileName, "VS", "vs_4_0", pixelFileName, "PS", "ps_4_0", texture ));

	GraphicManager().GetInstance().SubmitMessage(msg);

	return newID;
}
void LuaGraphic::AddObject::Register(lua_State *lua)
{
	luabind::module(lua) [
		luabind::def("AddBasicObject", LuaGraphic::AddObject::AddBasicObject)
	  ];
}