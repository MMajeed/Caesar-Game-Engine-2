#ifndef __LuaRegisterAll__
#define __LuaRegisterAll__

#include <Lua.hpp>
#include "LuaGraphic.h"
#include "LuaModel.h"
#include "LuaObject.h"
#include "LuaMath.h"
#include "LuaKeysID.h"
#include "LuaInputKeyActionSetup.h"
#include "LuaCamera.h"
#include "LuaLoopCallSetup.h"
#include "LuaBasicDrawableObject.h"
#include "LuaBasicTexture.h"
#include "LuaLight.h"
#include "LuaScreenShot.h"
#include "LuaScreenCapture.h"
#include "LuaMouse.h"

void LuaRegisterAll(lua_State *lua)
{
	LuaGraphic::RegisterAllLuaFunction(lua);
	LuaModel::RegisterAllLuaFunction(lua);
	LuaMath::RegisterAllLuaFunction(lua);
	LuaObject::RegisterAllLuaFunction(lua);
	LuaKeysID::RegisterAllLuaFunction(lua);
	LuaInputKeyActionSetup::RegisterAllLuaFunction(lua);
	LuaCamera::RegisterAllLuaFunction(lua);
	LuaLoopCallSetup::RegisterAllLuaFunction(lua);
	LuaBasicDrawableObject::RegisterAllLuaFunction(lua);
	LuaBasicTexture::RegisterAllLuaFunction(lua);
	LuaLight::RegisterAllLuaFunction(lua);
	LuaScreenShot::RegisterAllLuaFunction(lua);
	LuaScreenCapture::RegisterAllLuaFunction(lua);
	LuaMouse::RegisterAllLuaFunction(lua);
}


#endif //__LuaRegisterAll__