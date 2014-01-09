#include "Basic2DDrawable.h"
#include "GraphicManager.h"
#include "DX11Helper.h"
#include "Buffers.h"
#include <XNAConverter.h>
#include <Keys.h>
#include <3DMath.h>
#include <EntityCommunicator\EntityConfig.h>
#include <EntityCommunicator\ImportantIDConfig.h>
#include <WindowINFO.h>
#include <VecMath.h>

Basic2DDrawable::Basic2DDrawable()
{

}

std::shared_ptr<Basic2DDrawable> Basic2DDrawable::Spawn(const std::vector<Vertex>&	vectorVertices,
														const std::vector<WORD>&	vectorIndices,
														const std::string&			vertexFile,
														const std::string&			pixelFile,
														const std::string&			geometryFile,
														D3D11_CULL_MODE				cullMode,
														D3D11_FILL_MODE				fillMode)
{
	std::shared_ptr<Basic2DDrawable> newObject(new Basic2DDrawable());

	newObject->D3DInfo.vertices = vectorVertices;
	newObject->D3DInfo.indices = vectorIndices;
	newObject->D3DInfo.VertexShaderFileName = vertexFile;
	newObject->D3DInfo.PixelShaderFileName = pixelFile;
	newObject->D3DInfo.GeometryShaderFileName = geometryFile;
	newObject->D3DInfo.cullMode = cullMode;
	newObject->D3DInfo.fillMode = fillMode;

	newObject->Init();

	return newObject;
}

void Basic2DDrawable::CalculateWVP(const std::shared_ptr<ObjectINFO>& object, const SceneInfo& si, XMFLOAT4X4& worldFloat4x4, XMFLOAT4X4& finalFloat4x4)
{
	CHL::Vec4 loc = object->Location;
	loc(1) = -loc(1);
	loc = loc - CHL::Vec4({(si.width / 2.0), -(si.height / 2.0), 0.0, 0.0});
	
	CHL::Matrix4x4 mObjectFinal = CHL::ObjectCalculation(loc, object->Rotation, object->Scale);

	worldFloat4x4  = CHL::Convert4x4(mObjectFinal);
	XMFLOAT4X4 orthMatrix = CHL::Convert4x4(si.TwoDimMatrix);

	XMMATRIX finalMatrix = XMLoadFloat4x4(&worldFloat4x4) * XMLoadFloat4x4(&orthMatrix);
	XMStoreFloat4x4(&finalFloat4x4, finalMatrix);
}