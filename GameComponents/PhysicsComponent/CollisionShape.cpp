#include "CollisionShape.h"

CollisionShape::CollisionShape()
{
	this->pCollisionShape = nullptr;
}

void CollisionShape::Destory()
{
	if(this->pCollisionShape){ delete this->pCollisionShape;}
}