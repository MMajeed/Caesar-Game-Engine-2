#include "Entity.h"
#include "Keys.h"
#include <GenerateGUID.h>

Entity::Entity()
{
	this->ID = CHL::GenerateGUID();
}
Entity::Entity(const Entity& c)
	: metux()
{

}

std::string Entity::GetID(){ return this->ID; }
