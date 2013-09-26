#include "GetScriptManager.h"

#include <LuaManager.h>

Interface* GetScriptManager::GetComponent()
{
	return &LuaManager::GetInstance();
}