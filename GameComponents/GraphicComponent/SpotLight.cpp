#include "SpotLight.h"
#include <XNAConverter.h>
#include <3DMath.h>

cBuffer::CLightDesc SpotLight::GetLightDesc(std::shared_ptr<SpotLightINFO> lightInfo)
{
	cBuffer::CLightDesc light;
	light.material.diffuse = CHL::ConvertVec4(lightInfo->Diffuse);
	light.material.ambient = CHL::ConvertVec4(lightInfo->Ambient);
	light.material.specular = CHL::ConvertVec4(lightInfo->Specular);
	light.pos = CHL::ConvertVec4(lightInfo->Position);
	light.range = (float)lightInfo->Range;
	light.dir = CHL::ConvertVec4(lightInfo->Direction);
	light.spot = (float)lightInfo->Spot;
	light.attenuation = CHL::ConvertVec4(lightInfo->Attenuation);
	light.type = 3;
	light.shadowNum = -1;

	if(lightInfo->HasShadow == true)
	{
		XMFLOAT4X4 view = CHL::Convert4x4(SpotLight::CalculateViewMatrix(lightInfo));
		XMFLOAT4X4 pres = CHL::Convert4x4(SpotLight::CalculatePrespectiveMatrix(lightInfo));
		XMMATRIX T(
			0.5f, 0.0f, 0.0f, 0.0f,
			0.0f, -0.5f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.5f, 0.5f, 0.0f, 1.0f);

		XMMATRIX V = XMLoadFloat4x4(&view);
		XMMATRIX P = XMLoadFloat4x4(&pres);

		XMMATRIX VPT = V * P * T;
		VPT = XMMatrixTranspose(VPT);
		light.shadowMatrix = VPT;
	}

	return light;
}

CHL::Matrix4x4 SpotLight::CalculateViewMatrix(std::shared_ptr<SpotLightINFO> lightInfo)
{
	CHL::Vec4 vEye{0.0, 0.0, 0.0, 0.0};
	CHL::Vec4 vT{0.0, 0.0, 1.0, 0.0};
	CHL::Vec4 vUp{0.0, 1.0, 0.0, 0.0};
	double pitch; double yaw; double roll;

	vEye = lightInfo->Position;

	pitch = lightInfo->Direction(0);
	yaw = lightInfo->Direction(1);
	roll = lightInfo->Direction(2);

	return CHL::ViewCalculation(vEye, vT, vUp, pitch, yaw, roll);
}
CHL::Matrix4x4 SpotLight::CalculatePrespectiveMatrix(std::shared_ptr<SpotLightINFO> lightInfo)
{
	double FovAngleY = 1.570796327;
	double height = 2048;
	double width = 2048;
	double nearZ = 1.0;
	double farZ = lightInfo->Range;

	return CHL::PerspectiveFovLHCalculation(FovAngleY, height / width, nearZ, farZ);
}