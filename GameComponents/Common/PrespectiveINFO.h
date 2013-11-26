#ifndef __PrespectiveINFO__
#define __PrespectiveINFO__

#include "Linker.h"
#include "INFO.h"
#include <string>

class PrespectiveINFO : public INFO
{
public:

	virtual std::shared_ptr<Object> Get(const std::string& ID);
	virtual void Set(const std::string& ID, std::shared_ptr<Object> obj);
	virtual std::shared_ptr<INFO> Clone();
};

#endif //__PrespectiveINFO__