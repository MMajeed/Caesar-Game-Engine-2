#ifndef __INFO__
#define __INFO__

#include "Linker.h"
#include <string>
#include <Object.h>
#include <memory>

class CommonDLL_API INFO
{
public:
	INFO();

	std::string ID;

	virtual std::shared_ptr<Object> Get(const std::string& ID);
	virtual void Set(const std::string& ID, std::shared_ptr<Object> obj);
	virtual std::shared_ptr<INFO> Clone() = 0;
};

typedef std::shared_ptr<INFO> SP_INFO;

#endif //__INFO__