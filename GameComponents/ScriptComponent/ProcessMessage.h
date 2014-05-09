#ifndef __AdddProcessMessage__
#define __AdddProcessMessage__

#include "Linker.h"

#include <string>

#include <Message.h>
#include "LuaProcesses.h"
#include <memory>

namespace ProcessMessage
{
	ScriptComponentDLL_API void Add(std::shared_ptr<LuaProcesses> process);
	ScriptComponentDLL_API void Remove(std::string ID);
}

#endif //__AdddProcessMessage__