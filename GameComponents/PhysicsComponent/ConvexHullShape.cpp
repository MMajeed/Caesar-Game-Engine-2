#include "ConvexHullShape.h"

ConvexHullShape::ConvexHullShape()
{
	this->Info.stride = 3;
}

void ConvexHullShape::Init()
{
	this->pCollisionShape = 
		std::shared_ptr<btCollisionShape>(
			new btConvexHullShape(this->Info.points.data(), this->Info.points.size(), this->Info.stride));
}

std::shared_ptr<ConvexHullShape> ConvexHullShape::Spawn(std::shared_ptr<CHL::Model> model)
{
	std::shared_ptr<ConvexHullShape> returnValue(new ConvexHullShape());

	returnValue->Info.stride = model->NumberOfFaces;

	const std::vector<CML::Vec3>& vertices = model->Vertices;
	for(auto iter = vertices.cbegin();
		iter != vertices.cend();
		++iter)
	{
		const CML::Vec3& v = *iter;
		returnValue->Info.points.push_back((float)v(0));
		returnValue->Info.points.push_back((float)v(1));
		returnValue->Info.points.push_back((float)v(2));
	}
	
	returnValue->Init();
	return returnValue;
}