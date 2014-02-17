#include "BoxShape.h"

void BoxShape::Init()
{
	btVector3 halfExtent(this->Info.HalfExtents[0], this->Info.HalfExtents[1], this->Info.HalfExtents[2]);
	this->pCollisionShape = new btBoxShape(halfExtent);
}

std::shared_ptr<BoxShape> BoxShape::Spawn(CML::Vec3 halfExtent)
{
	std::shared_ptr<BoxShape> returnValue(new BoxShape());
	returnValue->Info.HalfExtents = halfExtent;
	returnValue->Init();
	return returnValue;
}