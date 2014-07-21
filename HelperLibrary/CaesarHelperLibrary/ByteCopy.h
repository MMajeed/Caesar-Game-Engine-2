#ifndef __ByteCopy__
#define __ByteCopy__

#include "Linker.h"
#include <vector>

namespace CHL
{
	template<typename T>
	void ByteCopy(const T& v, std::vector<char>& byte, unsigned int offset = 0)
	{
		byte.resize(offset + sizeof(T));
		memcpy(&byte[offset], &v, sizeof(T));
	}
}

#endif //__Object__