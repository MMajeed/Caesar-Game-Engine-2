#include "ScriptFactorySetup.h"

#include "ScriptManager.h"

namespace ScriptFactorySetup
{
	ScriptFactory::ScriptItem Load()
	{
		ScriptFactory::ScriptItem returnValue;

		returnValue._ScriptInterface = ScriptManager::GetPointer();

		return returnValue;
	}
};