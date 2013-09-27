#include "LuaGraphic.h"

#include <exception>
#include <Converter.h>
#include <boost/uuid/uuid_generators.hpp> // generators
#include <boost/uuid/uuid_io.hpp>         // streaming operators etc.

#include "LuaManager.h"
#include <GraphicCommunicator\ClearScreenMessage.h>
#include <GraphicCommunicator\GetGraphicManager.h>
#include <Model.h>
#include <Keys.h>

void LuaGraphic::ClearScreen::Action(double x, double y, double z)
{
	boost::numeric::ublas::vector<double> newColour(3);

	newColour(0) = x;	// Get the 1 paramter
	newColour(1) = y;	// Get the 2 paramter
	newColour(2) = z;	// Get the 3 paramter

	std::shared_ptr<ClearScreenMessage> msg(new ClearScreenMessage(newColour));

	GetGraphicManager::GetComponent()->SubmitMessage(msg);
}

void LuaGraphic::ClearScreen::Register(lua_State *lua)
{
	luabind::module(lua) [
		luabind::def("ClearScreen", LuaGraphic::ClearScreen::Action)
	  ];
}