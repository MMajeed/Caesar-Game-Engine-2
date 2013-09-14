#ifndef __PlyFileDrawable__
#define __PlyFileDrawable__

#include "BasicDrawable.h"

class PlyFileDrawable : public BasicDrawable
{
public:
	virtual void Init();
	virtual void LoadPlyFile();
};


#endif //__PlyFileDrawable__