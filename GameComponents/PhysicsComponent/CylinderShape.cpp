#include "CylinderShape.h"

void CylinderShape::Init()
{
	btVector3 halfExtent((btScalar)this->Info.HalfExtents[0], 
						 (btScalar)this->Info.HalfExtents[1],
						 (btScalar)this->Info.HalfExtents[2]);
	this->pCollisionShape = std::shared_ptr<btCollisionShape>(new btCylinderShape(halfExtent));
}

std::shared_ptr<CylinderShape> CylinderShape::Spawn(CML::Vec3 halfExtent)
{
	std::shared_ptr<CylinderShape> returnValue(new CylinderShape());
	returnValue->Info.HalfExtents = halfExtent;
	returnValue->Init();
	return returnValue;
}