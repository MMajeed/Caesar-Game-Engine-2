#include "LuaOnResize.h"
#include "LuaError.h"
#include "ScriptManager.h"
#include <Components.h>
#include <Logger.h>
#include "ProcessMessage.h"

LuaOnResize::LuaOnResize(luabind::object inputFunction)
{
	this->function = inputFunction;

	Components::Graphic->GraphicSettingsFactory()->GetClientSize(this->lastCheckedHeight, this->lastCheckedWidth);
}

void LuaOnResize::Action(lua_State *lua)
{
	unsigned int width;
	unsigned int height;
	
	Components::Graphic->GraphicSettingsFactory()->GetClientSize(height, width);

	if(this->lastCheckedHeight != height ||
	   this->lastCheckedWidth != width)
	{
		try
		{
			this->lastCheckedHeight = height;
			this->lastCheckedWidth = width;
			luabind::call_function<void>(this->function, this->ID, this->lastCheckedWidth, this->lastCheckedHeight);
		}
		catch(...)
		{
			Logger::LogError(LuaError::GetLuaError(lua));
		}
	}
}

void LuaOnResize::Update(double realTime, double deltaTime)
{

}