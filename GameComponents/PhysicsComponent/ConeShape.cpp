#include "ConeShape.h"

void ConeShape::Init()
{
	this->pCollisionShape = new btConeShape((btScalar)this->Info.Radius, (btScalar)this->Info.Height);
}

std::shared_ptr<ConeShape> ConeShape::Spawn(double radius, double height)
{
	std::shared_ptr<ConeShape> returnValue(new ConeShape());
	returnValue->Info.Radius = radius;
	returnValue->Info.Height = height;
	returnValue->Init();
	return returnValue;
}