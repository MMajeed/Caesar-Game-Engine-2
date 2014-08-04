#include "GraphicCameraEntity.h"

#include "GraphicObjectEntity.h"
#include "XNAConverter.h"
#include "ResourceManager.h"
#include "GraphicManager.h"

GraphicCameraEntity::GraphicCameraEntity(){}
GraphicCameraEntity::GraphicCameraEntity(std::weak_ptr<CameraEntity> v) : wp_Obj(v){}

XMFLOAT4 GraphicCameraEntity::GetEye() const
{
	XMFLOAT4 returnValue(0.0, 0.0, 0.0, 0.0);
	if(std::shared_ptr<CameraEntity> obj = this->wp_Obj.lock())
	{
		returnValue = ConvertVec4(obj->GetEye());
	}
	return returnValue;
}
XMFLOAT4 GraphicCameraEntity::GetTargetMagnitude() const
{
	XMFLOAT4 returnValue(0.0, 0.0, 1.0, 0.0);
	if(std::shared_ptr<CameraEntity> obj = this->wp_Obj.lock())
	{
		returnValue = ConvertVec4(obj->GetTargetMagnitude());
	}
	return returnValue;
}
XMFLOAT4 GraphicCameraEntity::GetUp() const
{
	XMFLOAT4 returnValue(0.0, 1.0, 0.0, 0.0);
	if(std::shared_ptr<CameraEntity> obj = this->wp_Obj.lock())
	{
		returnValue = ConvertVec4(obj->GetUp());
	}
	return returnValue;
}
float GraphicCameraEntity::GetRoll() const
{
	float returnValue = 0.0f;
	if(std::shared_ptr<CameraEntity> obj = this->wp_Obj.lock())
	{
		returnValue = (float)obj->GetRoll();
	}
	return returnValue;
}
float GraphicCameraEntity::GetPitch() const
{
	float returnValue = 0.0f;
	if(std::shared_ptr<CameraEntity> obj = this->wp_Obj.lock())
	{
		returnValue = (float)obj->GetPitch();
	}
	return returnValue;
}
float GraphicCameraEntity::GetYaw() const
{
	float returnValue = 0.0f;
	if(std::shared_ptr<CameraEntity> obj = this->wp_Obj.lock())
	{
		returnValue = (float)obj->GetYaw();
	}
	return returnValue;
}
float GraphicCameraEntity::GetFovAngleY() const
{
	float returnValue = 0.785398163f;
	if(std::shared_ptr<CameraEntity> obj = this->wp_Obj.lock())
	{
		returnValue = (float)obj->GetFovAngleY();
	}
	return returnValue;
}
float GraphicCameraEntity::GetNearZ() const
{
	float returnValue = 0.01f;
	if(std::shared_ptr<CameraEntity> obj = this->wp_Obj.lock())
	{
		returnValue = (float)obj->GetNearZ();
	}
	return returnValue;
}
float GraphicCameraEntity::GetFarZ() const
{
	float returnValue = 5000.0f;
	if(std::shared_ptr<CameraEntity> obj = this->wp_Obj.lock())
	{
		returnValue = (float)obj->GetFarZ();
	}
	return returnValue;
}
std::array<float, 4> GraphicCameraEntity::GetClearColor() const
{
	std::array<float, 4> returnValue = {0.5f, 0.5f, 0.5f, 1.0f};
	if(std::shared_ptr<CameraEntity> obj = this->wp_Obj.lock())
	{
		CML::Vec4 color = obj->GetClearColor();
		returnValue = {{(float)color[0], (float)color[1], (float)color[2], (float)color[3]}};
	}
	return returnValue;
}
std::hash_set<std::shared_ptr<BasicTexture>> GraphicCameraEntity::GetGlobalTexture2D() const
{
	std::hash_set<std::shared_ptr<BasicTexture>> returnValue;
	if(std::shared_ptr<CameraEntity> obj = this->wp_Obj.lock())
	{
		std::hash_set<std::string> textureList = obj->GetGlobalTexture2D();
		for(auto iter = textureList.begin(); iter != textureList.end(); ++iter)
		{
			std::string id = *iter;
			std::shared_ptr<BasicTexture> tx = ResourceManager::TextureList.Find(id);
			if(tx)
			{
				returnValue.insert(tx);
			}
		}
	}
	return returnValue;
}
std::hash_set<std::shared_ptr<BasicTexture>> GraphicCameraEntity::GetGlobalTextureCube() const
{
	std::hash_set<std::shared_ptr<BasicTexture>> returnValue;
	if(std::shared_ptr<CameraEntity> obj = this->wp_Obj.lock())
	{
		std::hash_set<std::string> textureList = obj->GetGlobalTextureCube();
		for(auto iter = textureList.begin(); iter != textureList.end(); ++iter)
		{
			std::string id = *iter;
			std::shared_ptr<BasicTexture> tx = ResourceManager::TextureList.Find(id);
			if(tx)
			{
				returnValue.insert(tx);
			}
		}
	}
	return returnValue;
}
std::hash_map<std::string, std::vector<char>> GraphicCameraEntity::GetUserData() const
{
	std::hash_map<std::string, std::vector<char>>  returnValue;
	if(std::shared_ptr<CameraEntity> obj = this->wp_Obj.lock())
	{
		returnValue = obj->GetUserData();
	}
	return returnValue;
}
CameraEntity::InclusionType GraphicCameraEntity::GetInclusionState() const
{
	CameraEntity::InclusionType returnValue = CameraEntity::InclusionType::Exclude;
	if(std::shared_ptr<CameraEntity> obj = this->wp_Obj.lock())
	{
		returnValue = obj->GetInclusionState();
	}
	return returnValue;
}
std::vector<GraphicObjectEntity> GraphicCameraEntity::FilterInclusionList(std::hash_map<std::string, GraphicObjectEntity> list) const
{
	std::vector<GraphicObjectEntity> returnValue;

	if(std::shared_ptr<CameraEntity> cam = this->wp_Obj.lock())
	{
		CameraEntity::InclusionType inclusionState = cam->GetInclusionState();
		std::hash_set<std::string> cameraInclusionList = cam->GetInclusionList();
		for(auto iter = list.begin(); iter != list.end(); ++iter)
		{
			std::hash_set<std::string> objGroup = iter->second.GetGroupList();

			std::vector<std::string> groupDifference;
			std::set_intersection(objGroup.begin(), objGroup.end(),
									cameraInclusionList.begin(), cameraInclusionList.end(),
									std::back_inserter(groupDifference));

			if(inclusionState == CameraEntity::InclusionType::Exclude)
			{// if CANT be on the list
				if(groupDifference.size() > 0){ continue; } 
			}
			else if(inclusionState == CameraEntity::InclusionType::Include)
			{ // It has to be on the list for it to be added
				if(groupDifference.size() == 0){ continue; }
			}
			returnValue.push_back(GraphicObjectEntity(iter->second));
		}
	}
	else
	{
		for(auto iter = list.begin(); iter != list.end(); ++iter)
		{
			returnValue.push_back(GraphicObjectEntity(iter->second));
		}
	}

	return returnValue;
}

void GraphicCameraEntity::UpdateView()
{
	XMFLOAT4X4 returnValue;

	XMFLOAT4 f4Eye = this->GetEye();
	XMVECTOR vEye = XMVectorSet(f4Eye.x, f4Eye.y, f4Eye.z, f4Eye.w);
	XMFLOAT4 f4Up = this->GetUp();
	XMVECTOR vUp = XMVectorSet(f4Up.x, f4Up.y, f4Up.z, f4Up.w);
	XMFLOAT4 f4TM = this->GetTargetMagnitude();
	XMVECTOR vTM = XMVectorSet(f4TM.x, f4TM.y, f4TM.z, f4TM.w);

	XMMATRIX RotationMatrix = XMMatrixRotationRollPitchYaw(this->GetPitch(), this->GetYaw(), this->GetRoll());

	vTM = XMVector3TransformCoord(vTM, RotationMatrix);
	vUp = XMVector3TransformCoord(vUp, RotationMatrix);

	vTM += vEye;

	XMStoreFloat4x4(&returnValue, XMMatrixLookAtLH(vEye, vTM, vUp));

	this->view = returnValue;
}
void GraphicCameraEntity::UpdatePerspective()
{
	XMFLOAT4X4 returnValue;

	auto window = GraphicManager::GetInstance().window;
	XMMATRIX xmPrespective = XMMatrixPerspectiveFovLH(this->GetFovAngleY(),
													  (float)window.width / (float)window.height,
													  this->GetNearZ(), this->GetFarZ());
	XMStoreFloat4x4(&returnValue, xmPrespective);

	this->perspective = returnValue;
}
void GraphicCameraEntity::UpdateOrthogonal()
{
	XMFLOAT4X4 returnValue;

	auto window = GraphicManager::GetInstance().window;
	XMMATRIX xmPrespective = XMMatrixOrthographicLH((float)window.width , (float)window.height,
													 this->GetNearZ(), this->GetFarZ());
	XMStoreFloat4x4(&returnValue, xmPrespective);

	this->orthogonal = returnValue;
}
XMFLOAT4X4 GraphicCameraEntity::GetView() const
{
	return this->view;
}
XMFLOAT4X4 GraphicCameraEntity::GetPerspective() const
{
	return this->perspective;
}
XMFLOAT4X4 GraphicCameraEntity::GetOrthogonal() const
{
	return this->orthogonal;
}