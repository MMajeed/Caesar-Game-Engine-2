#ifndef __SceneInfo__
#define __SceneInfo__

#include "Linker.h"

#include <Vector.h>
#include <Matrix.h>

class ObjectINFO;
class Drawable;

struct DrawableObject
{
	DrawableObject(){}
	DrawableObject(std::shared_ptr<ObjectINFO> ObjInfo, std::shared_ptr<Drawable> Drawable) : ObjInfo(ObjInfo), Drawable(Drawable){}
	std::shared_ptr<ObjectINFO> ObjInfo;
	std::shared_ptr<Drawable> Drawable;
};

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
	bool process2D;
};

#endif //__SceneInfo__