#ifndef __SceneInfo__
#define __SceneInfo__

#include "Linker.h"
#include <vector>
#include <set>
#include <Vector.h>
#include <Vector.h>
#include "Buffers.h"
#include <array>
#include <Matrix.h>

class ObjectEntity;
class Drawable;

struct GraphicComponentDLL_API  DrawableObject
{
	DrawableObject(){}
	DrawableObject(std::shared_ptr<ObjectEntity> ObjInfo, std::shared_ptr<Drawable> Drawable) : ObjInfo(ObjInfo), Drawable(Drawable){}
	std::shared_ptr<ObjectEntity> ObjInfo;
	std::shared_ptr<Drawable> Drawable;
};

struct GraphicComponentDLL_API  SceneInfo
{
	enum class InclusionType { Exclude = 0, Include = 1, All = 2};

	CML::Vec4 ClearColour;
	CML::Vec4 Eye;
	CML::Matrix4x4 CamerMatrix;
	CML::Matrix4x4 ProjectionMatrix;
	CML::Matrix4x4 TwoDimMatrix;
	double width;
	double height;
	double farZ;
	double nearZ;
	bool process2D;
	std::vector<std::string> Global2DTexture;
	std::vector<std::string> GlobalCubeTexture;
	std::array<float, 16> GlobalUserData;

	InclusionType InclusionState;
	std::set<std::string> ObjectList;
};

#endif //__SceneInfo__