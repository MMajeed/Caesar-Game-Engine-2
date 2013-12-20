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

Basic2DDrawable::Basic2DDrawable(const std::string& inputID)
: BasicDrawable(inputID)
{

}

std::shared_ptr<Basic2DDrawable> Basic2DDrawable::Spawn(const std::string&			inputID,
														const std::vector<Vertex>&	vectorVertices,
														const std::vector<WORD>&	vectorIndices,
														const std::string&			vertexFile,
														const std::string&			pixelFile,
														D3D11_CULL_MODE				cullMode,
														D3D11_FILL_MODE				fillMode)
{
	std::shared_ptr<Basic2DDrawable> newObject(new Basic2DDrawable(inputID));

	newObject->D3DInfo.vertices = vectorVertices;
	newObject->D3DInfo.indices = vectorIndices;
	newObject->D3DInfo.VertexShaderInfo = vertexFile;
	newObject->D3DInfo.PixelShaderInfo = pixelFile;
	newObject->D3DInfo.cullMode = cullMode;
	newObject->D3DInfo.fillMode = fillMode;

	newObject->Init();

	return newObject;
}

void Basic2DDrawable::CalculateWVP(const std::shared_ptr<ObjectINFO>& object, XMFLOAT4X4& worldFloat4x4, XMFLOAT4X4& finalFloat4x4)
{
	auto window = EntityConfig::GetEntity(WindowINFOID::Get());
	std::shared_ptr<WindowINFO> windowInfo = std::dynamic_pointer_cast<WindowINFO>(window);

	CHL::Vec4 loc = object->Location;
	loc(1) = -loc(1);
	loc = loc - CHL::Vec4({(windowInfo->Width / 2.0), -(windowInfo->Height / 2.0), 0.0, 0.0});
	
	CHL::Matrix4x4 mObjectFinal = CHL::ObjectCalculation(loc, object->Rotation, object->Scale);

	XMFLOAT4X4 worldMatrix = CHL::Convert4x4(mObjectFinal);
	XMFLOAT4X4 orthMatrix = CHL::Convert4x4(GraphicManager::GetInstance().SceneInfo.OrthographicMatrix);

	XMMATRIX finalMatrix = XMLoadFloat4x4(&worldMatrix) * XMLoadFloat4x4(&orthMatrix);
	XMStoreFloat4x4(&finalFloat4x4, finalMatrix);
}