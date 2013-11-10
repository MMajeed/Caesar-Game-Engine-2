#ifndef __LuaKeyAction__
#define __LuaKeyAction__

#include "LuaProcesses.h"
#include <string>
#include <luabind\luabind.hpp>

class LuaKeyAction : public LuaProcesses
{
public:
	enum class KeyStatWanted{ KeyUp = 0, KeyDown = 1 };

	LuaKeyAction(unsigned int inputKey, KeyStatWanted inputWanted, luabind::object inputFunction);

	virtual void Update(double realTime, double deltaTime);
	virtual void Action(lua_State *lua);

	unsigned int key;
	KeyStatWanted wanted;
	luabind::object function;

	KeyStatWanted currentKey;
};


#endif //__LuaKeyAction__