#include "BoxShape.h"

void BoxShape::Init()
{
	btVector3 halfExtent((float)this->Info.HalfExtents[0], (float)this->Info.HalfExtents[1], (float)this->Info.HalfExtents[2]);
	this->pCollisionShape = std::shared_ptr<btCollisionShape>(new btBoxShape(halfExtent));
}

std::shared_ptr<BoxShape> BoxShape::Spawn(CML::Vec3 halfExtent)
{
	std::shared_ptr<BoxShape> returnValue(new BoxShape());
	returnValue->Info.HalfExtents = halfExtent;
	returnValue->Init();
	return returnValue;
}