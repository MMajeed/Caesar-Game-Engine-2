#ifndef __ScriptFactory__
#define __ScriptFactory__

#include "Linker.h"

#include "Interface.h"
#include <memory>
#include <string>

class CommonDLL_API ScriptFactory
{
public:
	struct ScriptItem
	{
		std::shared_ptr<Interface> _ScriptInterface;
	};

	ScriptFactory(const ScriptFactory::ScriptItem& input);

	virtual bool Verify();

	virtual void SubmitMessage(std::shared_ptr<Message> msg);
	virtual std::shared_ptr<Interface> GetComponent();

protected:
	ScriptItem _ClassItems;
};

#endif //__ScriptFactory__