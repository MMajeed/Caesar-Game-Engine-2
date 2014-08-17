#include "GraphicCameraEntity.h"

#include "GraphicObjectEntity.h"
#include "XNAConverter.h"
#include "ResourceManager.h"
#include "GraphicManager.h"
#include "3DMath.h"

GraphicCameraEntity::GraphicCameraEntity()
{
	this->Update(nullptr, 1024, 1024);
}
GraphicCameraEntity::GraphicCameraEntity(std::shared_ptr<CameraEntity> v, unsigned int width, unsigned int height)
{
	this->Update(v, width, height);
}

void GraphicCameraEntity::Update(std::shared_ptr<CameraEntity> v, unsigned int width, unsigned int height)
{
 	this->UpdateEye(v);
	this->UpdateTargetMagnitude(v);
	this->UpdateUp(v);
	this->UpdateRoll(v);
	this->UpdatePitch(v);
	this->UpdateYaw(v);
	this->UpdateFovAngleY(v);
	this->UpdateNearZ(v);
	this->UpdateFarZ(v);
	this->UpdateClearScreen(v);
	this->UpdateClearColor(v);
	this->UpdateInclusionState(v);
	this->UpdateInclusionList(v);
	this->UpdateTextureList(v);
	this->UpdateUserData(v);
	this->UpdateVertexShaderID(v);
	this->UpdateVertexShaderState(v);
	this->UpdatePixelShaderID(v);
	this->UpdatePixelShaderState(v);
	this->UpdateWidth(width);
	this->UpdateHeight(height);
	this->UpdateView(v);
	this->UpdateView2D(v);
	this->UpdatePerspective(v);
	this->UpdateOrthogonal(v);
}

std::vector<std::shared_ptr<GraphicObjectEntity>> 
	GraphicCameraEntity::FilterInclusionList(std::unordered_map<std::string, std::shared_ptr<GraphicObjectEntity>> list) const
{
	std::vector<std::shared_ptr<GraphicObjectEntity>> returnValue;
	returnValue.reserve(list.size());

	const CameraEntity::InclusionType& inclusionState = this->InclusionState;
	const std::set<std::string>& cameraInclusionList = this->InclusionList;
	for(auto iter = list.begin(); iter != list.end(); ++iter)
	{
		std::set<std::string> objGroup = iter->second->GetGroupList();

		std::vector<std::string> groupDifference;
		std::set_intersection(objGroup.cbegin(), objGroup.cend(),
							  cameraInclusionList.cbegin(), cameraInclusionList.cend(),
							  std::back_inserter(groupDifference));

		if(inclusionState == CameraEntity::InclusionType::Exclude)
		{// if CANT be on the list
			if(groupDifference.size() > 0){ continue; }
		}
		else if(inclusionState == CameraEntity::InclusionType::Include)
		{ // It has to be on the list for it to be added
			if(groupDifference.size() == 0){ continue; }
		}
		returnValue.push_back(iter->second);
	}

	XMFLOAT4 eye = this->GetEye();
	std::sort(returnValue.begin(), returnValue.end(),
			  [&eye](const std::shared_ptr<GraphicObjectEntity>& a, const std::shared_ptr<GraphicObjectEntity>& b) -> bool
	{
		float rankA = Length(eye, a->GetLocation());
		float rankB = Length(eye, b->GetLocation());

		rankA += a->GetPriority();
		rankB += b->GetPriority();

		return rankA > rankB;
	});

	return returnValue;
}

void GraphicCameraEntity::UpdateEye(std::shared_ptr<CameraEntity> obj)
{
	if(obj)	{ this->Eye = ConvertVec4(obj->GetEye()); }
	else	{ this->Eye = XMFLOAT4(0.0, 0.0, 0.0, 1.0); }
}
XMFLOAT4 GraphicCameraEntity::GetEye() const
{
	return this->Eye;
}

void GraphicCameraEntity::UpdateTargetMagnitude(std::shared_ptr<CameraEntity> obj)
{
	if(obj)	{ this->TargetMagnitude = ConvertVec4(obj->GetTargetMagnitude()); }
	else	{ this->TargetMagnitude = XMFLOAT4(0.0, 0.0, 1.0, 1.0); }
}
XMFLOAT4 GraphicCameraEntity::GetTargetMagnitude() const
{
	return this->TargetMagnitude;
}

void GraphicCameraEntity::UpdateUp(std::shared_ptr<CameraEntity> obj)
{
	if(obj)	{ this->Up = ConvertVec4(obj->GetUp()); }
	else	{ this->Up = XMFLOAT4(0.0, 1.0, 0.0, 1.0); }
}
XMFLOAT4 GraphicCameraEntity::GetUp() const
{
	return this->Up;
}

void GraphicCameraEntity::UpdateRoll(std::shared_ptr<CameraEntity> obj)
{
	if(obj)	{ this->Roll = (float)obj->GetRoll(); }
	else	{ this->Roll = 0.0f; }
}
float GraphicCameraEntity::GetRoll() const
{
	return this->Roll;
}

void GraphicCameraEntity::UpdatePitch(std::shared_ptr<CameraEntity> obj)
{
	if(obj)	{ this->Pitch = (float)obj->GetPitch(); }
	else	{ this->Pitch = 0.0f; }
}
float GraphicCameraEntity::GetPitch() const
{
	return this->Pitch;
}

void GraphicCameraEntity::UpdateYaw(std::shared_ptr<CameraEntity> obj)
{
	if(obj)	{ this->Yaw = (float)obj->GetYaw(); }
	else	{ this->Yaw = 0.0f; }
}
float GraphicCameraEntity::GetYaw() const
{
	return this->Yaw;
}

void GraphicCameraEntity::UpdateFovAngleY(std::shared_ptr<CameraEntity> obj)
{
	if(obj)	{ this->FovAngleY = (float)obj->GetFovAngleY(); }
	else	{ this->FovAngleY = 0.785398163f; }
}
float GraphicCameraEntity::GetFovAngleY() const
{
	return this->FovAngleY;
}

void GraphicCameraEntity::UpdateNearZ(std::shared_ptr<CameraEntity> obj)
{
	if(obj)	{ this->NearZ = (float)obj->GetNearZ(); }
	else	{ this->NearZ = 0.01f; }
}
float GraphicCameraEntity::GetNearZ() const
{
	return this->NearZ;
}

void GraphicCameraEntity::UpdateFarZ(std::shared_ptr<CameraEntity> obj)
{
	if(obj)	{ this->FarZ = (float)obj->GetFarZ(); }
	else	{ this->FarZ = 5000.0f; }
}
float GraphicCameraEntity::GetFarZ() const
{
	return this->FarZ;
}

void GraphicCameraEntity::UpdateClearScreen(std::shared_ptr<CameraEntity> obj)
{
	if(obj) { this->ClearScreen = obj->GetClearScreen(); }
	else	{ this->ClearScreen =  true; }
}
bool GraphicCameraEntity::GetClearScreen() const
{
	return this->ClearScreen;
}

void GraphicCameraEntity::UpdateClearColor(std::shared_ptr<CameraEntity> obj)
{
	if(obj)	
	{
		auto clearValue = obj->GetClearColor();
		this->ClearColor = {{(float)clearValue(0), (float)clearValue(1), (float)clearValue(2), (float)clearValue(3)}};
	}
	else	{ this->ClearColor = {{0.0f, 0.0f, 0.0f, 1.0f}}; }
}
std::array<float, 4> GraphicCameraEntity::GetClearColor() const
{
	return this->ClearColor;
}

void GraphicCameraEntity::UpdateInclusionState(std::shared_ptr<CameraEntity> obj)
{
	if(obj)	{ this->InclusionState = obj->GetInclusionState(); }
	else	{ this->InclusionState = CameraEntity::InclusionType::Exclude; }
}
CameraEntity::InclusionType GraphicCameraEntity::GetInclusionState() const
{
	return this->InclusionState;
}

void GraphicCameraEntity::UpdateInclusionList(std::shared_ptr<CameraEntity> obj)
{
	if(obj)	{ this->InclusionList = obj->GetInclusionList(); }
}
std::set<std::string> GraphicCameraEntity::GetInclusionList() const
{
	return this->InclusionList;
}

void GraphicCameraEntity::UpdateTextureList(std::shared_ptr<CameraEntity> obj)
{
	if(obj)	{ this->TextureList = obj->GetTexture(); }
}
std::unordered_map<std::string, std::string> GraphicCameraEntity::GetTextureList() const
{
	return this->TextureList;
}
std::unordered_map<std::string, std::shared_ptr<BasicTexture>> GraphicCameraEntity::GetTexture() const
{
	std::unordered_map<std::string, std::shared_ptr<BasicTexture>> returnValue;

	for(const auto& iter : this->TextureList)
	{
		returnValue[iter.first] = this->FindTexture(iter.second);
	}

	return returnValue;
}
std::shared_ptr<BasicTexture> GraphicCameraEntity::FindTexture(const std::string& ID) const
{
	std::shared_ptr<BasicTexture> returnValue;

	auto iter = this->TextureList.find(ID);
	if(iter != this->TextureList.end())
	{
		returnValue = ResourceManager::TextureList.Find(iter->second);
	}
	return returnValue;
}

void GraphicCameraEntity::UpdateUserData(std::shared_ptr<CameraEntity> obj)
{
	if(obj)	{ this->UserData = obj->GetUserData(); }
}
std::unordered_map<std::string, std::shared_ptr<Object>> GraphicCameraEntity::GetUserData() const
{
	return this->UserData;
}
std::shared_ptr<Object> GraphicCameraEntity::FindUserData(const std::string& ID) const
{
	std::shared_ptr<Object> returnValue;
	auto iter = this->UserData.find(ID);
	if(iter != this->UserData.cend())
	{
		returnValue = iter->second;
	}
	return returnValue;
}

void GraphicCameraEntity::UpdateVertexShaderID(std::shared_ptr<CameraEntity> obj)
{
	if(obj)	{ this->VertexShaderID = obj->GetVertexShaderID(); }
}
std::string GraphicCameraEntity::GetVertexShaderID() const
{
	return this->VertexShaderID;
}
std::shared_ptr<VertexShader> GraphicCameraEntity::GetVertexShader() const
{
	const std::string& id = this->VertexShaderID;
	std::shared_ptr<VertexShader> returnValue = ResourceManager::VertexShaderList.Find(id);
	return returnValue;
}

void GraphicCameraEntity::UpdateVertexShaderState(std::shared_ptr<CameraEntity> obj)
{
	if(obj)	{ this->VertexShaderState = obj->GetVertexShaderState(); }
	else { this->VertexShaderState = CameraEntity::CAMERA_SHADER_TYPE::DEFAULT; }
}
CameraEntity::CAMERA_SHADER_TYPE GraphicCameraEntity::GetVertexShaderState() const
{
	return this->VertexShaderState;
}

void GraphicCameraEntity::UpdatePixelShaderID(std::shared_ptr<CameraEntity> obj)
{
	if(obj)	{ this->PixelShaderID = obj->GetPixelShaderID(); }
}
std::string GraphicCameraEntity::GetPixelShaderID() const
{
	return this->PixelShaderID;
}
std::shared_ptr<PixelShader> GraphicCameraEntity::GetPixelShader() const
{
	const std::string& id = this->PixelShaderID;
	std::shared_ptr<PixelShader> returnValue = ResourceManager::PixelShaderList.Find(id);
	return returnValue;
}

void GraphicCameraEntity::UpdatePixelShaderState(std::shared_ptr<CameraEntity> obj)
{
	if(obj)	{ this->PixelShaderState = obj->GetPixelShaderState(); }
	else { this->PixelShaderState = CameraEntity::CAMERA_SHADER_TYPE::DEFAULT; }
}
CameraEntity::CAMERA_SHADER_TYPE GraphicCameraEntity::GetPixelShaderState() const
{
	return this->PixelShaderState;
}

void GraphicCameraEntity::UpdateWidth(unsigned int v)
{
	this->Width = v;
}
unsigned int GraphicCameraEntity::GetWidth() const
{
	return this->Width;
}

void GraphicCameraEntity::UpdateHeight(unsigned int v)
{
	this->Height = v;
}
unsigned int GraphicCameraEntity::GetHeight() const
{
	return this->Height;
}

void GraphicCameraEntity::UpdateView(std::shared_ptr<CameraEntity> obj)
{
	const XMFLOAT4& f4Eye = this->Eye;
	XMVECTOR vEye = XMVectorSet(f4Eye.x, f4Eye.y, f4Eye.z, f4Eye.w);
	const XMFLOAT4& f4Up = this->Up;
	XMVECTOR vUp = XMVectorSet(f4Up.x, f4Up.y, f4Up.z, f4Up.w);
	const XMFLOAT4& f4TM = this->TargetMagnitude;
	XMVECTOR vTM = XMVectorSet(f4TM.x, f4TM.y, f4TM.z, f4TM.w);

	XMMATRIX RotationMatrix = XMMatrixRotationRollPitchYaw(this->GetPitch(), this->GetYaw(), this->GetRoll());

	vTM = XMVector3TransformCoord(vTM, RotationMatrix);
	vUp = XMVector3TransformCoord(vUp, RotationMatrix);

	vTM += vEye;

	XMStoreFloat4x4(&this->View, XMMatrixLookAtRH(vEye, vTM, vUp));
}
XMFLOAT4X4 GraphicCameraEntity::GetView() const
{
	return this->View;
}

void GraphicCameraEntity::UpdateView2D(std::shared_ptr<CameraEntity> obj)
{
	float widthHalf = this->Width / 2.f;
	float heightHalf = this->Height / 2.f;
	XMVECTOR vEye = XMVectorSet(widthHalf, heightHalf, 0.0, 0.0);
	XMVECTOR vTM = XMVectorSet(0.0, 0.0, 1.0, 0.0);
	XMVECTOR vUp = XMVectorSet(0.0, -1.0, 0.0, 0.0);

	vTM += vEye;

	XMStoreFloat4x4(&this->View2D, XMMatrixLookAtRH(vEye, vTM, vUp));
}
XMFLOAT4X4 GraphicCameraEntity::GetView2D() const
{
	return this->View2D;
}

void GraphicCameraEntity::UpdatePerspective(std::shared_ptr<CameraEntity> obj)
{
	XMMATRIX xmPrespective = XMMatrixPerspectiveFovRH(this->FovAngleY,
													  (float)this->Width / (float)this->Height,
													  this->NearZ, this->FarZ);
	XMStoreFloat4x4(&this->Perspective, xmPrespective);
}
XMFLOAT4X4 GraphicCameraEntity::GetPerspective() const
{
	return this->Perspective;
}

void GraphicCameraEntity::UpdateOrthogonal(std::shared_ptr<CameraEntity> obj)
{
	XMMATRIX xmPrespective = XMMatrixOrthographicRH((float)this->Width, (float)this->Height,
													this->NearZ, this->FarZ);
	XMStoreFloat4x4(&this->Orthogonal, xmPrespective);
}
XMFLOAT4X4 GraphicCameraEntity::GetOrthogonal() const
{
	return this->Orthogonal;
}