#include "LuaInputKeyActionSetup.h"

#include <luabind\luabind.hpp>

#include "LuaKeyAction.h"
#include <ProcessMessage.h>
#include <Logger.h>

namespace LuaInputKeyActionSetup
{
	std::string OnKeyDown(int key, luabind::object const& function)
	{
		if(luabind::type(function) != LUA_TFUNCTION)
		{
			Logger::LogError("Wrong paramter for OnKeyDown, Please pass in the key and function");
		}

		std::shared_ptr<LuaKeyAction> newKeyAction(
			new LuaKeyAction(static_cast<InputKeysEnum::KeyCode>(key), InputKeysEnum::KeyStatus::KeyDown, function));
		ProcessMessage::Add(newKeyAction);
		return newKeyAction->ID;
	}
	std::string OnKeyUp(int key, luabind::object const& function)
	{
		if(luabind::type(function) != LUA_TFUNCTION)
		{
			Logger::LogError("Wrong paramter for OnKeyUp, Please pass in the key and function");
		}

		std::shared_ptr<LuaKeyAction> newKeyAction(
			new LuaKeyAction(static_cast<InputKeysEnum::KeyCode>(key), InputKeysEnum::KeyStatus::KeyUp, function));

		ProcessMessage::Add(newKeyAction);
		return newKeyAction->ID;
	}

	void RegisterAllLuaFunction(lua_State *lua)
	{
		luabind::module(lua)[
			luabind::def("OnKeyDown", LuaInputKeyActionSetup::OnKeyDown),
				luabind::def("OnKeyUp", LuaInputKeyActionSetup::OnKeyUp)
		];

		luabind::object keyState = luabind::newtable(lua);
		keyState["KeyUp"] = 0;
		keyState["KeyDown"] = 1;
		keyState["Unknown"] = 2;
		luabind::globals(lua)["KeyState"] = keyState;

		luabind::object keyCode = luabind::newtable(lua);
		keyCode["LBUTTON"] = 0x01;
		keyCode["RBUTTON"] = 0x02;
		keyCode["MBUTTON"] = 0x04;
		keyCode["XBUTTON1"] = 0x05;
		keyCode["XBUTTON2"] = 0x06;

		keyCode["SPACE"] = 0x20;
		keyCode["PRIOR"] = 0x21;
		keyCode["NEXT"] = 0x22;
		keyCode["END"] = 0x23;
		keyCode["HOME"] = 0x24;
		keyCode["LEFT"] = 0x25;
		keyCode["UP"] = 0x26;
		keyCode["RIGHT"] = 0x27;
		keyCode["DOWN"] = 0x28;
		keyCode["SELECT"] = 0x29;
		keyCode["PRINT"] = 0x2A;
		keyCode["EXECUTE"] = 0x2B;
		keyCode["SNAPSHOT"] = 0x2C;
		keyCode["INSERT"] = 0x2D;
		keyCode["DELETE"] = 0x2E;
		keyCode["HELP"] = 0x2F;

		keyCode["NUMPAD0"] = 0x60;
		keyCode["NUMPAD1"] = 0x61;
		keyCode["NUMPAD2"] = 0x62;
		keyCode["NUMPAD3"] = 0x63;
		keyCode["NUMPAD4"] = 0x64;
		keyCode["NUMPAD5"] = 0x65;
		keyCode["NUMPAD6"] = 0x66;
		keyCode["NUMPAD7"] = 0x67;
		keyCode["NUMPAD8"] = 0x68;
		keyCode["NUMPAD9"] = 0x69;
		keyCode["MULTIPLY"] = 0x6A;
		keyCode["ADD"] = 0x6B;
		keyCode["SEPARATOR"] = 0x6C;
		keyCode["SUBTRACT"] = 0x6D;
		keyCode["DECIMAL"] = 0x6E;
		keyCode["DIVIDE"] = 0x6F;
		keyCode["F1"] = 0x70;
		keyCode["F2"] = 0x71;
		keyCode["F3"] = 0x72;
		keyCode["F4"] = 0x73;
		keyCode["F5"] = 0x74;
		keyCode["F6"] = 0x75;
		keyCode["F7"] = 0x76;
		keyCode["F8"] = 0x77;
		keyCode["F9"] = 0x78;
		keyCode["F10"] = 0x79;
		keyCode["F11"] = 0x7A;
		keyCode["F12"] = 0x7B;

		keyCode["ESCAPE"] = 0x1B;
		keyCode["LSHIFT"] = 0xA0;
		keyCode["RSHIFT"] = 0xA1;
		keyCode["TAB"] = 0x09;
		keyCode["LCONTROL"] = 0xA2;
		keyCode["RCONTROL"] = 0xA3;
		keyCode["SHIFT"] = 0x10;
		keyCode["CONTROL"] = 0x11;
		keyCode["MENU"] = 0x12;

		keyCode["0"] = 0x30;
		keyCode["1"] = 0x31;
		keyCode["2"] = 0x32;
		keyCode["3"] = 0x33;
		keyCode["4"] = 0x34;
		keyCode["5"] = 0x35;
		keyCode["6"] = 0x36;
		keyCode["7"] = 0x37;
		keyCode["8"] = 0x38;
		keyCode["9"] = 0x39;
		keyCode["A"] = 0x41;
		keyCode["B"] = 0x42;
		keyCode["C"] = 0x43;
		keyCode["D"] = 0x44;
		keyCode["E"] = 0x45;
		keyCode["F"] = 0x46;
		keyCode["G"] = 0x47;
		keyCode["H"] = 0x48;
		keyCode["I"] = 0x49;
		keyCode["J"] = 0x4A;
		keyCode["K"] = 0x4B;
		keyCode["L"] = 0x4C;
		keyCode["M"] = 0x4D;
		keyCode["N"] = 0x4E;
		keyCode["O"] = 0x4F;
		keyCode["P"] = 0x50;
		keyCode["Q"] = 0x51;
		keyCode["R"] = 0x52;
		keyCode["S"] = 0x53;
		keyCode["T"] = 0x54;
		keyCode["U"] = 0x55;
		keyCode["V"] = 0x56;
		keyCode["W"] = 0x57;
		keyCode["X"] = 0x58;
		keyCode["Y"] = 0x59;
		keyCode["Z"] = 0x5A;
		luabind::globals(lua)["KeyCode"] = keyCode;
	}
};