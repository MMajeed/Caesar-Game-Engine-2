#ifndef __SceneInfo__
#define __SceneInfo__

#include "Linker.h"

#include <Vector.h>
#include <Matrix.h>


struct SceneInfo
{
	CHL::Vec4 ClearColour;
	CHL::Vec4 Eye;
	CHL::Matrix4x4 CamerMatrix;
	CHL::Matrix4x4 ProjectionMatrix;
	CHL::Matrix4x4 TwoDimMatrix;
	double width;
	double height;
	double farZ;
	double nearZ;
};

#endif //__SceneInfo__