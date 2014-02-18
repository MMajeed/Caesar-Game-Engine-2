#include "Constraint.h"

Constraint::Constraint()
{
	this->pConstraint = nullptr;
}

void Constraint::Destory()
{
	if(this->pConstraint){ delete this->pConstraint; }
}