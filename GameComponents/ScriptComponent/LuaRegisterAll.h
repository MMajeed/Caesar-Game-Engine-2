#ifndef __LuaRegisterAll__
#define __LuaRegisterAll__

#include <Lua.hpp>
#include "LuaGraphic.h"
#include "LuaModel.h"
#include "LuaObject.h"
#include "LuaMath.h"
#include "LuaKeysID.h"
#include "LuaKeyActionSetup.h"
#include "LuaCamera.h"
#include "LuaLoopCallSetup.h"
#include "LuaBasicDrawableObject.h"
#include "LuaBasicTexture.h"
#include "LuaLight.h"

void LuaRegisterAll(lua_State *lua)
{
	LuaGraphic::RegisterAllLuaFunction(lua);
	LuaModel::RegisterAllLuaFunction(lua);
	LuaMath::RegisterAllLuaFunction(lua);
	LuaObject::RegisterAllLuaFunction(lua);
	LuaKeysID::RegisterAllLuaFunction(lua);
	LuaKeyActionSetup::RegisterAllLuaFunction(lua);
	LuaCamera::RegisterAllLuaFunction(lua);
	LuaLoopCallSetup::RegisterAllLuaFunction(lua);
	LuaBasicDrawableObject::RegisterAllLuaFunction(lua);
	LuaBasicTexture::RegisterAllLuaFunction(lua);
	LuaLight::RegisterAllLuaFunction(lua);
}


#endif //__LuaRegisterAll__