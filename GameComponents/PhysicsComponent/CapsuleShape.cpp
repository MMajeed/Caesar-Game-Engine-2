#include "CapsuleShape.h"

void CapsuleShape::Init()
{
	this->pCollisionShape = new btCapsuleShape((btScalar)this->Info.Radius, (btScalar)this->Info.Height);
}

std::shared_ptr<CapsuleShape> CapsuleShape::Spawn(double radius, double height)
{
	std::shared_ptr<CapsuleShape> returnValue(new CapsuleShape());
	returnValue->Info.Radius = radius;
	returnValue->Info.Height = height;
	returnValue->Init();
	return returnValue;
}