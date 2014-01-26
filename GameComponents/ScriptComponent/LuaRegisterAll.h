#ifndef __LuaRegisterAll__
#define __LuaRegisterAll__

#include <Lua.hpp>
#include "LuaGraphic.h"
#include "Lua3DFile.h"
#include "LuaObject.h"
#include "LuaMath.h"
#include "LuaKeysID.h"
#include "LuaInputKeyActionSetup.h"
#include "LuaCamera.h"
#include "LuaThreadSetup.h"
#include "LuaBasicDrawableObject.h"
#include "LuaBasicTexture.h"
#include "LuaLight.h"
#include "LuaScreenShot.h"
#include "LuaScreenCapture.h"
#include "LuaMouse.h"
#include "LuaComponentManager.h"
void LuaRegisterAll(lua_State *lua)
{
	LuaGraphic::RegisterAllLuaFunction(lua);
	Lua3DFile::RegisterAllLuaFunction(lua);
	LuaMath::RegisterAllLuaFunction(lua);
	LuaObject::RegisterAllLuaFunction(lua);
	LuaKeysID::RegisterAllLuaFunction(lua);
	LuaInputKeyActionSetup::RegisterAllLuaFunction(lua);
	LuaCamera::RegisterAllLuaFunction(lua);
	LuaThreadSetup::RegisterAllLuaFunction(lua);
	LuaBasicDrawableObject::RegisterAllLuaFunction(lua);
	LuaBasicTexture::RegisterAllLuaFunction(lua);
	LuaLight::RegisterAllLuaFunction(lua);
	LuaScreenShot::RegisterAllLuaFunction(lua);
	LuaScreenCapture::RegisterAllLuaFunction(lua);
	LuaMouse::RegisterAllLuaFunction(lua);
	LuaComponentManager::RegisterAllLuaFunction(lua);
}


#endif //__LuaRegisterAll__