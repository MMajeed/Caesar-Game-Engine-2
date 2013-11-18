#ifndef __WindowINFO__
#define __WindowINFO__

#include "Linker.h"
#include "INFO.h"
#include <string>
#include <Windows.h>

class WindowINFO : public INFO
{
public:
	int Width;
	int Height;
	HWND HWND;

	virtual std::shared_ptr<Object> Get(const std::string& ID);
	virtual void Set(const std::string& ID, std::shared_ptr<Object> obj);
	virtual std::shared_ptr<INFO> Clone();
};

#endif //__WindowINFO__