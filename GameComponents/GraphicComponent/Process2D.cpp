#include "Process2D.h"
#include <ObjectINFO.h>
#include "Basic2DDrawable.h"

namespace Process2D
{
	bool Filter(const DrawableObject& obj)
	{
		std::shared_ptr<Basic2DDrawable> objInfo = std::dynamic_pointer_cast<Basic2DDrawable>(obj.Drawable);
		if(!objInfo){ return false; }
	
		return true;
	}
}