#ifndef __SceneFilter__
#define __SceneFilter__

#include "Linker.h"

#include <string>
#include <INFO.h>

class SceneFilter
{
public:
	SceneFilter(const std::string& inputID) : ID(inputID){};

	virtual bool Filter(SP_INFO) = 0;
	
	std::string ID;
};


#endif //__SceneFilter__