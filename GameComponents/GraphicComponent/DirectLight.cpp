#include "DirectLight.h"
#include <XNAConverter.h>
#include <DirectionalLightINFO.h>

cBuffer::CLightDesc DirectLight::GetLightDesc(std::shared_ptr<DirectionalLightINFO> lightInfo)
{
	cBuffer::CLightDesc light;
	light.material.diffuse = CHL::ConvertVec4(lightInfo->Diffuse);
	light.material.ambient = CHL::ConvertVec4(lightInfo->Ambient);
	light.material.specular = CHL::ConvertVec4(lightInfo->Specular);
	light.dir = CHL::ConvertVec4(lightInfo->Direction);
	light.type = 1;
	light.shadowNum = -1;

	if(lightInfo->HasShadow == true)
	{
		XMFLOAT4X4 view = CHL::Convert4x4(DirectLight::CalculateViewMatrix(lightInfo));
		XMFLOAT4X4 pres = CHL::Convert4x4(DirectLight::CalculatePrespectiveMatrix(lightInfo));
		light.lightView = XMLoadFloat4x4(&view);
		light.lightPrespective = XMLoadFloat4x4(&pres);
	}
	return light;
}

CHL::Matrix4x4 DirectLight::CalculateViewMatrix(std::shared_ptr<DirectionalLightINFO> lightInfo)
{
	double pitch; double yaw; double roll;

	pitch = lightInfo->Direction(0);
	yaw = lightInfo->Direction(1);
	roll = lightInfo->Direction(2);

	XMFLOAT3 dir((float)pitch, (float)yaw, (float)roll);
	XMFLOAT3 center(0.0f, 0.0f, 0.0f);

	XMVECTOR lightDir = XMLoadFloat3(&dir);
	XMVECTOR lightPos = DirectLight::radius * lightDir;
	XMVECTOR targetPos = XMLoadFloat3(&center);
	XMVECTOR up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	XMMATRIX V = XMMatrixLookAtLH(lightPos, targetPos, up);
	V = XMMatrixTranspose(V);

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
	XMFLOAT3 center(0.0f, 0.0f, 0.0f);

	XMVECTOR lightDir = XMLoadFloat3(&dir);
	XMVECTOR lightPos = DirectLight::radius*lightDir;
	XMVECTOR targetPos = XMLoadFloat3(&center);
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

	P = XMMatrixTranspose(P);

	XMFLOAT4X4 pFloat4x4;
	XMStoreFloat4x4(&pFloat4x4, P);
	return CHL::Convert4x4(pFloat4x4);
}