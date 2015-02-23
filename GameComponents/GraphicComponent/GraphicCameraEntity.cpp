#include "GraphicCameraEntity.h"

#include "GraphicObjectEntity.h"
#include "XNAConverter.h"
#include "Resource.h"
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
	if(width != 0 || height != 0)
	{
		this->UpdateView(v);
		this->UpdateView2D(v);
		this->UpdatePerspective(v);
		this->UpdateOrthogonal(v);
	}
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