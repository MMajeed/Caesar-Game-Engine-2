#ifndef __LuaKeyAction__
#define __LuaKeyAction__

#include "LuaProcesses.h"
#include <string>
#include <luabind\luabind.hpp>
#include <InputKeysEnum.h>

class ScriptComponentDLL_API LuaKeyAction : public LuaProcesses
{
public:
	LuaKeyAction(InputKeysEnum::KeyCode inputKey, InputKeysEnum::KeyStatus inputWanted, luabind::object inputFunction);

	virtual void Update(double realTime, double deltaTime);
	virtual void Action(lua_State *lua);

	InputKeysEnum::KeyCode key;
	InputKeysEnum::KeyStatus wanted;
	luabind::object function;
	InputKeysEnum::KeyStatus lastKeyState;
};


#endif //__LuaKeyAction__