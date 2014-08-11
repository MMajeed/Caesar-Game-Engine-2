#include "GraphicObjectEntity.h"

#include "Rasterizer.h"
#include "GraphicManager.h"
#include "GraphicModel.h"
#include "VertexShader.h"
#include "GeometryShader.h"
#include "PixelShader.h"
#include "XNAConverter.h"
#include "ResourceManager.h"
#include <AnimationCommunicator\AnimationControllerConfig.h>
#include <PhysicsCommunicator\RigidBodyConfig.h>

GraphicObjectEntity::GraphicObjectEntity()
{
	this->Update(nullptr);
}
GraphicObjectEntity::GraphicObjectEntity(std::shared_ptr<ObjectEntity> v)
{
	this->Update(v);
}

void GraphicObjectEntity::Update(std::shared_ptr<ObjectEntity> v)
{
	this->UpdateTracker(v);
	this->UpdateLocation(v);
	this->UpdateRotation(v);
	this->UpdateScale(v);
	this->UpdateDepth(v);
	this->UpdatePriority(v);
	this->UpdateGraphicModelID(v);
	this->UpdateVertexShaderID(v);
	this->UpdateGeometryShaderID(v);
	this->UpdatePixelShaderID(v);
	this->UpdateAnimationID(v);
	this->UpdateAnimationJointName(v);
	this->UpdateRigidBodyID(v);
	this->UpdateGroupList(v);
	this->UpdateTextureList(v);
	this->UpdateUserData(v);
	this->UpdateFillMode(v);
	this->UpdateCullMode(v);
	this->UpdateLRS(v);
}

void GraphicObjectEntity::UpdateTracker(std::shared_ptr<ObjectEntity> obj)
{
	if(obj)	{ this->Tracker = obj->GetTracker();; }
	else	{ this->Tracker = 0; }
}
unsigned int GraphicObjectEntity::GetTracker() const
{
	return this->Tracker;
}

void GraphicObjectEntity::UpdateLocation(std::shared_ptr<ObjectEntity> obj)
{
	if(obj)	{ this->Location = ConvertVec4(obj->GetLocation()); }
	else	{ this->Location = XMFLOAT4(0.0, 0.0, 0.0, 1.0); }
}
XMFLOAT4 GraphicObjectEntity::GetLocation() const
{
	return this->Location;
}

void GraphicObjectEntity::UpdateRotation(std::shared_ptr<ObjectEntity> obj)
{
	if(obj)	{ this->Rotation = ConvertVec4(obj->GetRotation()); }
	else	{ this->Rotation = XMFLOAT4(0.0, 0.0, 0.0, 1.0); }
}
XMFLOAT4 GraphicObjectEntity::GetRotation() const
{
	return this->Rotation;
}

void GraphicObjectEntity::UpdateScale(std::shared_ptr<ObjectEntity> obj)
{
	if(obj)	{ this->Scale = ConvertVec4(obj->GetScale()); }
	else	{ this->Scale = XMFLOAT4(1.0, 1.0, 1.0, 1.0); }
}
XMFLOAT4 GraphicObjectEntity::GetScale() const
{
	return this->Scale;
}

void GraphicObjectEntity::UpdateDepth(std::shared_ptr<ObjectEntity> obj)
{
	if(obj)	{ this->Depth = obj->GetDepth(); }
	else	{ this->Depth = true; }
}
bool GraphicObjectEntity::GetDepth() const
{
	return this->Depth;
}

void GraphicObjectEntity::UpdatePriority(std::shared_ptr<ObjectEntity> obj)
{
	if(obj)	{ this->Priority = (float)obj->GetPriority(); }
	else	{ this->Priority = true; }
}
float GraphicObjectEntity::GetPriority() const
{
	return this->Priority;
}

void GraphicObjectEntity::UpdateGraphicModelID(std::shared_ptr<ObjectEntity> obj)
{
	if(obj)	{ this->GraphicModelID = obj->GetGraphicModelID(); }
}
std::string GraphicObjectEntity::GetGraphicModelID() const
{
	return this->GraphicModelID;
}
std::shared_ptr<GraphicModel> GraphicObjectEntity::GetGraphicModel() const
{
	const std::string& id = this->GraphicModelID;
	std::shared_ptr<GraphicModel> returnValue = ResourceManager::GraphicModelList.Find(id);
	return returnValue;
}

void GraphicObjectEntity::UpdateVertexShaderID(std::shared_ptr<ObjectEntity> obj)
{
	if(obj)	{ this->VertexShaderID = obj->GetVertexShaderID(); }
}
std::string GraphicObjectEntity::GetVertexShaderID() const
{
	return this->VertexShaderID;
}
std::shared_ptr<VertexShader> GraphicObjectEntity::GetVertexShader() const
{
	const std::string& id = this->VertexShaderID;
	std::shared_ptr<VertexShader> returnValue = ResourceManager::VertexShaderList.Find(id);
	return returnValue;
}

void GraphicObjectEntity::UpdateGeometryShaderID(std::shared_ptr<ObjectEntity> obj)
{
	if(obj)	{ this->GeometryShaderID = obj->GetGeometryShaderID(); }
}
std::string GraphicObjectEntity::GetGeometryShaderID() const
{
	return this->GeometryShaderID;
}
std::shared_ptr<GeometryShader> GraphicObjectEntity::GetGeometryShader() const
{
	const std::string& id = this->GeometryShaderID;
	std::shared_ptr<GeometryShader> returnValue = ResourceManager::GeometryShaderList.Find(id);
	return returnValue;
}

void GraphicObjectEntity::UpdatePixelShaderID(std::shared_ptr<ObjectEntity> obj)
{
	if(obj)	{ this->PixelShaderID = obj->GetPixelShaderID(); }
}
std::string GraphicObjectEntity::GetPixelShaderID() const
{
	return this->PixelShaderID;
}
std::shared_ptr<PixelShader> GraphicObjectEntity::GetPixelShader() const
{
	const std::string& id = this->PixelShaderID;
	std::shared_ptr<PixelShader> returnValue = ResourceManager::PixelShaderList.Find(id);
	return returnValue;
}

void GraphicObjectEntity::UpdateAnimationID(std::shared_ptr<ObjectEntity> obj)
{
	if(obj)	{ this->AnimationID = obj->GetAnimationID(); }
}
std::string GraphicObjectEntity::GetAnimationID() const
{
	return this->AnimationID;
}
std::hash_map<std::string, XMFLOAT4X4> GraphicObjectEntity::GetAnimation() const
{
	std::hash_map<std::string, XMFLOAT4X4> returnValue;
	throw "To do: GetAnimation()";
	return returnValue;
}

void GraphicObjectEntity::UpdateAnimationJointName(std::shared_ptr<ObjectEntity> obj)
{
	if(obj)	{ this->AnimationJointName = obj->GetJointName(); }
}
std::string GraphicObjectEntity::GetAnimationJointName() const
{
	return this->AnimationJointName;
}
XMFLOAT4X4 GraphicObjectEntity::GetAnimationJoint() const
{
	const std::string& id = this->AnimationID;
	const std::string& jointName = this->AnimationJointName;
	CML::Matrix4x4 jaMatrix = AnimationControllerConfig::GetSingleJoint(id, jointName);
	XMFLOAT4X4 returnValue = Convert4x4(jaMatrix);
	return returnValue;
}

void GraphicObjectEntity::UpdateRigidBodyID(std::shared_ptr<ObjectEntity> obj)
{
	if(obj)	{ this->RigidBodyID = obj->GetRigidBodyID(); }
}
std::string GraphicObjectEntity::GetRigidBodyID() const
{
	return this->RigidBodyID;
}
XMFLOAT4X4 GraphicObjectEntity::GetRigidBody() const
{
	const std::string& id = this->RigidBodyID;
	CML::Matrix4x4 jaMatrix = RigidBodyConfig::GetTranslation(id);
	XMFLOAT4X4 returnValue = Convert4x4(jaMatrix);
	return returnValue;
}

void GraphicObjectEntity::UpdateGroupList(std::shared_ptr<ObjectEntity> obj)
{
	if(obj)	{ this->GroupList = obj->GetGroupList(); }
}
std::hash_set<std::string> GraphicObjectEntity::GetGroupList() const
{
	return this->GroupList;
}

void GraphicObjectEntity::UpdateTextureList(std::shared_ptr<ObjectEntity> obj)
{
	if(obj)	{ this->TextureList = obj->GetTexture(); }
}
std::hash_map<std::string, std::string> GraphicObjectEntity::GetTextureList() const
{
	return this->TextureList;
}
std::hash_map<std::string, std::shared_ptr<BasicTexture>> GraphicObjectEntity::GetTexture() const
{
	std::hash_map<std::string, std::shared_ptr<BasicTexture>> returnValue;

	for(const auto& iter : this->TextureList)
	{
		returnValue[iter.first] = this->FindTexture(iter.second);
	}

	return returnValue;
}
std::shared_ptr<BasicTexture> GraphicObjectEntity::FindTexture(const std::string& ID) const
{
	std::shared_ptr<BasicTexture> returnValue;

	auto iter = this->TextureList.find(ID);
	if(iter != this->TextureList.end())
	{
		returnValue = ResourceManager::TextureList.Find(iter->second);
	}
	return returnValue;
}

void GraphicObjectEntity::UpdateUserData(std::shared_ptr<ObjectEntity> obj)
{
	if(obj)	{ this->UserData = obj->GetUserData(); }
}
std::hash_map<std::string, std::shared_ptr<Object>> GraphicObjectEntity::GetUserData() const
{
	return this->UserData;
}
std::shared_ptr<Object> GraphicObjectEntity::FindUserData(const std::string& ID) const
{
	std::shared_ptr<Object> returnValue;
	auto iter = this->UserData.find(ID);
	if(iter != this->UserData.cend())
	{
		returnValue = iter->second;
	}
	return returnValue;
}

void GraphicObjectEntity::UpdateFillMode(std::shared_ptr<ObjectEntity> obj)
{
	if(obj)	{ this->FillMode = static_cast<D3D11_FILL_MODE>(obj->GetFillMode()); }
}
D3D11_FILL_MODE GraphicObjectEntity::GetFillMode() const
{
	return this->FillMode;
}

void GraphicObjectEntity::UpdateCullMode(std::shared_ptr<ObjectEntity> obj)
{
	if(obj)	{ this->CullMode = static_cast<D3D11_CULL_MODE>(obj->GetCullMode()); }
}
D3D11_CULL_MODE GraphicObjectEntity::GetCullMode() const
{
	return this->CullMode;
}

void GraphicObjectEntity::UpdateLRS(std::shared_ptr<ObjectEntity> obj)
{
	XMFLOAT4 location = this->GetLocation();
	XMFLOAT4 rotation = this->GetRotation();
	XMFLOAT4 scale = this->GetScale();
	
	XMMATRIX xmTranslate = XMMatrixTranslation(location.x, location.y, location.z);

	XMMATRIX xmRotateX = XMMatrixRotationX(rotation.x);
	XMMATRIX xmRotateY = XMMatrixRotationY(rotation.y);
	XMMATRIX xmRotateZ = XMMatrixRotationZ(rotation.z);

	XMMATRIX xmScaling = XMMatrixScaling(scale.x, scale.y, scale.z);

	XMMATRIX xmObjectFinal = XMMatrixIdentity();
	xmObjectFinal = XMMatrixMultiply(xmObjectFinal, xmScaling);
	xmObjectFinal = XMMatrixMultiply(xmObjectFinal, xmRotateX);
	xmObjectFinal = XMMatrixMultiply(xmObjectFinal, xmRotateY);
	xmObjectFinal = XMMatrixMultiply(xmObjectFinal, xmRotateZ);
	xmObjectFinal = XMMatrixMultiply(xmObjectFinal, xmTranslate);

	XMStoreFloat4x4(&this->LRS, xmObjectFinal);
}
XMFLOAT4X4 GraphicObjectEntity::GetLRS() const
{
	return this->LRS;
}

XMFLOAT4X4 GraphicObjectEntity::GetWorld() const
{
	XMMATRIX worldMatrix = XMMatrixIdentity();

	if(this->AnimationID.empty() != true &&
	   this->AnimationJointName.empty() != true)
	{
		XMFLOAT4X4 animation = this->GetAnimationJoint();
		worldMatrix = XMLoadFloat4x4(&animation);
	}
	
	
	XMFLOAT4X4 LRS = this->GetLRS();
	worldMatrix = worldMatrix * XMLoadFloat4x4(&LRS);

	if(this->RigidBodyID.empty() != true)
	{
		XMFLOAT4X4 rigidBody = this->GetRigidBody();
		worldMatrix = worldMatrix * XMLoadFloat4x4(&rigidBody);
	}

	XMFLOAT4X4 world;
	XMStoreFloat4x4(&world, worldMatrix);
	return world;
}