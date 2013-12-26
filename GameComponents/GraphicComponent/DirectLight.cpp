#include "DirectLight.h"
#include <XNAConverter.h>
#include "GraphicManager.h"
#include <3DMath.h>

cBuffer::CLightDesc DirectLight::GetLightDesc(std::shared_ptr<DirectionalLightINFO> lightInfo)
{
	cBuffer::CLightDesc light;
	light.material.diffuse = CHL::ConvertVec4(lightInfo->Diffuse);
	light.material.ambient = CHL::ConvertVec4(lightInfo->Ambient);
	light.material.specular = CHL::ConvertVec4(lightInfo->Specular);
	light.dir = CHL::ConvertVec4(lightInfo->Direction);
	light.type = 1;
	light.shadowNum = -1;

	
	return light;
}
CHL::Matrix4x4 DirectLight::CalculateShadowMatrix(std::shared_ptr<DirectionalLightINFO> lightInfo)
{
	XMFLOAT4X4 view = CHL::Convert4x4(DirectLight::CalculateViewMatrix(lightInfo));
	XMFLOAT4X4 pres = CHL::Convert4x4(DirectLight::CalculatePrespectiveMatrix(lightInfo));
	XMMATRIX T(
		0.5f, 0.0f, 0.0f, 0.0f,
		0.0f, -0.5f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.0f, 1.0f);

	XMMATRIX V = XMLoadFloat4x4(&view);
	XMMATRIX P = XMLoadFloat4x4(&pres);

	XMMATRIX VPT = V * P * T;
	VPT = XMMatrixTranspose(VPT);
		
	XMFLOAT4X4 shadowMatrix;
	XMStoreFloat4x4(&shadowMatrix, VPT);
	return CHL::Convert4x4(shadowMatrix);
}
CHL::Matrix4x4 DirectLight::CalculateViewMatrix(std::shared_ptr<DirectionalLightINFO> lightInfo)
{
	double pitch; double yaw; double roll;

	pitch = lightInfo->Direction(0);
	yaw = lightInfo->Direction(1);
	roll = lightInfo->Direction(2);

	XMFLOAT3 dir((float)pitch, (float)yaw, (float)roll);
	CHL::Vec4 eye;// = GraphicManager::GetInstance().SceneInfo.Eye;
	XMVECTOR center = XMVectorSet((float)eye(0), (float)eye(1), (float)eye(2), (float)eye(3));

	XMVECTOR lightDir = XMLoadFloat3(&dir);
	XMVECTOR lightPos = ( DirectLight::radius * lightDir ) + center;
	XMVECTOR targetPos = center;
	XMVECTOR up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	XMMATRIX V = XMMatrixLookAtLH(lightPos, targetPos, up);

	XMFLOAT4X4 vFloat4x4;
	XMStoreFloat4x4(&vFloat4x4, V);
	return CHL::Convert4x4(vFloat4x4);
}
CHL::Matrix4x4 DirectLight::CalculatePrespectiveMatrix(std::shared_ptr<DirectionalLightINFO> lightInfo)
{
	double pitch; double yaw; double roll;

	pitch = lightInfo->Direction(0);
	yaw = lightInfo->Direction(1);
	roll = lightInfo->Direction(2);

	XMFLOAT3 dir((float)pitch, (float)yaw, (float)roll);
	CHL::Vec4 eye;// = GraphicManager::GetInstance().SceneInfo.Eye;
	XMVECTOR center = XMVectorSet((float)eye(0), (float)eye(1), (float)eye(2), (float)eye(3));

	XMVECTOR lightDir = XMLoadFloat3(&dir);
	XMVECTOR lightPos = ( DirectLight::radius * lightDir ) + center;
	XMVECTOR targetPos = center;
	XMVECTOR up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	XMMATRIX V = XMMatrixLookAtLH(lightPos, targetPos, up);

	// Transform bounding sphere to light space.
	XMFLOAT3 sphereCenterLS;
	XMStoreFloat3(&sphereCenterLS, XMVector3TransformCoord(targetPos, V));

	// Ortho frustum in light space encloses scene.
	float l = sphereCenterLS.x - DirectLight::radius;
	float b = sphereCenterLS.y - DirectLight::radius;
	float n = sphereCenterLS.z - DirectLight::radius;
	float r = sphereCenterLS.x + DirectLight::radius;
	float t = sphereCenterLS.y + DirectLight::radius;
	float f = sphereCenterLS.z + DirectLight::radius;
	XMMATRIX P = XMMatrixOrthographicOffCenterLH(l, r, b, t, n, f);

	XMFLOAT4X4 pFloat4x4;
	XMStoreFloat4x4(&pFloat4x4, P);
	return CHL::Convert4x4(pFloat4x4);
}