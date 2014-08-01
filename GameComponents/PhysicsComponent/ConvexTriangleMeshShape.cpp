#include "ConvexTriangleMeshShape.h"

ConvexTriangleMeshShape::ConvexTriangleMeshShape()
{
	this->Info.Mesh = new btTriangleMesh(true, false);
}

void ConvexTriangleMeshShape::Init()
{
	this->pCollisionShape = std::shared_ptr<btCollisionShape>(new btConvexTriangleMeshShape(this->Info.Mesh));
}

std::shared_ptr<ConvexTriangleMeshShape> ConvexTriangleMeshShape::Spawn(std::shared_ptr<CHL::Model> model)
{
	std::shared_ptr<ConvexTriangleMeshShape> returnValue(new ConvexTriangleMeshShape());

	const std::vector<CML::Vec3>& vertices = model->Vertices;
	std::vector<unsigned int>& indices = model->Faces;

	for(unsigned int i = 0; i < indices.size(); i += 3)
	{
		const CML::Vec3& point1 = vertices[i];
		btVector3 btPoint1((float)point1(0), (float)point1(1), (float)point1(2));

		const CML::Vec3& point2 = vertices[i];
		btVector3 btPoint2((float)point2(0), (float)point2(1), (float)point2(2));

		const CML::Vec3& point3 = vertices[i];
		btVector3 btPoint3((float)point3(0), (float)point3(1), (float)point3(2));

		returnValue->Info.Mesh->addTriangle(btPoint1, btPoint2, btPoint3, true);
	}

	returnValue->Init();
	return returnValue;
}