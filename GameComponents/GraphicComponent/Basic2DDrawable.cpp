#include "Basic2DDrawable.h"
#include "GraphicManager.h"
#include "DX11Helper.h"
#include "Buffers.h"
#include "XNAConverter.h"
#include <Keys.h>
#include "3DMath.h"
#include <EntityCommunicator\EntityConfig.h>
#include <EntityCommunicator\ImportantIDConfig.h>
#include <VecOperators.h>

Basic2DDrawable::Basic2DDrawable()
{

}

std::shared_ptr<Basic2DDrawable> Basic2DDrawable::Spawn(std::shared_ptr<CHL::Model> model,
														const std::string&			vertexFile,
														const std::string&			pixelFile,
														const std::string&			geometryFile,
														D3D11_CULL_MODE				cullMode,
														D3D11_FILL_MODE				fillMode)
{
	std::shared_ptr<Basic2DDrawable> newObject(new Basic2DDrawable());

	newObject->ProcessModel(model);
	newObject->D3DInfo.VertexShaderFileName = vertexFile;
	newObject->D3DInfo.PixelShaderFileName = pixelFile;
	newObject->D3DInfo.GeometryShaderFileName = geometryFile;
	newObject->D3DInfo.cullMode = cullMode;
	newObject->D3DInfo.fillMode = fillMode;

	newObject->Init();

	return newObject;
}

void Basic2DDrawable::ProcessModel(std::shared_ptr<CHL::Model> model)
{
	auto vectorFaces = model->Faces;
	this->D3DInfo.indices.clear();
	this->D3DInfo.indices.reserve(vectorFaces.size());
	for(std::size_t i = 0; i < vectorFaces.size(); ++i)
	{
		this->D3DInfo.indices.push_back((WORD)vectorFaces[i]);
	}

	auto modelVertices = model->Vertices;
	this->D3DInfo.vertices.clear();
	this->D3DInfo.vertices.reserve(modelVertices.size());

	for(std::size_t i = 0; i < modelVertices.size(); ++i)
	{
		Vertex v;
		auto ver = modelVertices[i];
		v.Pos = XMFLOAT4((float)ver.Point(0), (float)(ver.Point(1) * -1.0f), (float)ver.Point(2), 1.0);
		v.Normal = XMFLOAT4((float)ver.Normal(0), (float)ver.Normal(1), (float)ver.Normal(2), 1.0);
		v.Texture = XMFLOAT3((float)ver.Texture(0), (float)ver.Texture(1), (float)ver.Texture(2));

		this->D3DInfo.vertices.push_back(v);
	}
}

void Basic2DDrawable::CalculateWVP(const std::shared_ptr<ObjectINFO>& object, const SceneInfo& si, XMFLOAT4X4& worldFloat4x4, XMFLOAT4X4& finalFloat4x4)
{
	CML::Vec4 loc = object->Location;
	loc(1) = -loc(1);
	loc = loc - CML::Vec4({(si.width / 2.0), -(si.height / 2.0), 0.0, 0.0});
	
	CML::Matrix4x4 mObjectFinal = ObjectCalculation(loc, object->Rotation, object->Scale);

	worldFloat4x4  = Convert4x4(mObjectFinal);
	XMFLOAT4X4 orthMatrix = Convert4x4(si.TwoDimMatrix);

	XMMATRIX finalMatrix = XMLoadFloat4x4(&worldFloat4x4) * XMLoadFloat4x4(&orthMatrix);
	XMStoreFloat4x4(&finalFloat4x4, finalMatrix);
}