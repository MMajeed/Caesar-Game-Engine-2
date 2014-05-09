#ifndef __GetMouseStatus__
#define __GetMouseStatus__

#include "Linker.h"
#include <utility>

namespace Mouse
{
	InputCommunicatorDLL_API std::pair<long, long> GetLoc();
}

#endif //__GetMouseStatus__