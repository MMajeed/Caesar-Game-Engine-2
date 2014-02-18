#include "SphereShape.h"

void SphereShape::Init()
{
	this->pCollisionShape = std::shared_ptr<btCollisionShape>(new btSphereShape((btScalar)this->Info.Radius));
}

std::shared_ptr<SphereShape> SphereShape::Spawn(double radius)
{
	std::shared_ptr<SphereShape> returnValue(new SphereShape());
	returnValue->Info.Radius = radius;
	returnValue->Init();
	return returnValue;
}