#ifndef __GraphicSettings__
#define __GraphicSettings__

#include "Linker.h"
#include <Message.h>
#include <Vector.h>
#include <string>

namespace GraphicSettings
{
	void ClearScreen(const CHL::Vec4& input);
	void Resize(unsigned int widthInput, unsigned int heightInput);
}




#endif //__GraphicSettings__