#include "SpotLight.h"
#include "XNAConverter.h"
#include "3DMath.h"

namespace SpotLight
{
	cBuffer::CLightDesc GetLightDesc(std::shared_ptr<SpotLightINFO> lightInfo)
	{
		cBuffer::CLightDesc light;
		light.material.diffuse = ConvertVec4(lightInfo->Diffuse);
		light.material.ambient = ConvertVec4(lightInfo->Ambient);
		light.material.specular = ConvertVec4(lightInfo->Specular);
		light.pos = ConvertVec4(lightInfo->Position);
		light.range = (float)lightInfo->Range;
		light.dir = ConvertVec4(lightInfo->Direction);
		light.spot = (float)lightInfo->Spot;
		light.attenuation = ConvertVec4(lightInfo->Attenuation);
		light.type = 3;
		light.shadowNum = -1;

		return light;
	}
	CML::Matrix4x4 CalculateShadowMatrix(std::shared_ptr<SpotLightINFO> lightInfo, const CML::Vec4 eye)
	{
		XMFLOAT4X4 view = Convert4x4(SpotLight::CalculateViewMatrix(lightInfo, eye));
		XMFLOAT4X4 pres = Convert4x4(SpotLight::CalculatePrespectiveMatrix(lightInfo, eye));
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
		return Convert4x4(shadowMatrix);
	}
	CML::Matrix4x4 CalculateViewMatrix(std::shared_ptr<SpotLightINFO> lightInfo, const CML::Vec4 eye)
	{
		CML::Vec4 vEye{0.0, 0.0, 0.0, 0.0};
		CML::Vec4 vT{0.0, 0.0, 1.0, 0.0};
		CML::Vec4 vUp{0.0, 1.0, 0.0, 0.0};
		double pitch = 0.0; double yaw = 0.0; double roll = 0.0;

		vEye = lightInfo->Position;
		vT = lightInfo->Direction;

		return ViewCalculation(vEye, vT, vUp, pitch, yaw, roll);
	}
	CML::Matrix4x4 CalculatePrespectiveMatrix(std::shared_ptr<SpotLightINFO> lightInfo, const CML::Vec4 eye)
	{
		double FovAngleY = 1.570796327;
		double height = SpotLight::Height;
		double width = SpotLight::Width;
		double nearZ = 1.0;
		double farZ = lightInfo->Range;

		return PerspectiveFovLHCalculation(FovAngleY, height / width, nearZ, farZ);
	}
	SceneInfo GetScene(std::shared_ptr<SpotLightINFO> lightInfo, const CML::Vec4 eye)
	{
		SceneInfo returnValue;
		returnValue.Eye = lightInfo->Position;
		returnValue.CamerMatrix = CalculateViewMatrix(lightInfo, eye);
		returnValue.ProjectionMatrix = CalculatePrespectiveMatrix(lightInfo, eye);
		returnValue.TwoDimMatrix = CalculatePrespectiveMatrix(lightInfo, eye);
		returnValue.width = SpotLight::Width;
		returnValue.height = SpotLight::Height;
		returnValue.farZ = lightInfo->Range;
		returnValue.nearZ = 1.0;
		returnValue.InclusionState = SceneInfo::InclusionType::All;
		return returnValue;
	}
}