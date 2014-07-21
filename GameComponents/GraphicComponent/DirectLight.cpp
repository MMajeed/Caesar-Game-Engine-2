//#include "DirectLight.h"
//#include "XNAConverter.h"
//#include "GraphicManager.h"
//#include "3DMath.h"
//
//namespace DirectLight
//{
//	cBuffer::CLightDesc GetLightDesc(std::shared_ptr<DirectionalLightINFO> lightInfo)
//	{
//		cBuffer::CLightDesc light;
//		light.material.diffuse = ConvertVec4(lightInfo->Diffuse);
//		light.material.ambient = ConvertVec4(lightInfo->Ambient);
//		light.material.specular = ConvertVec4(lightInfo->Specular);
//		light.dir = ConvertVec4(lightInfo->Direction);
//		light.type = 1;
//		light.shadowNum = -1;
//
//		return light;
//	}
//	CML::Matrix4x4 CalculateShadowMatrix(std::shared_ptr<DirectionalLightINFO> lightInfo, const CML::Vec4 eye)
//	{
//		XMFLOAT4X4 view = Convert4x4(DirectLight::CalculateViewMatrix(lightInfo, eye));
//		XMFLOAT4X4 pres = Convert4x4(DirectLight::CalculatePrespectiveMatrix(lightInfo, eye));
//		XMMATRIX T(
//			0.5f, 0.0f, 0.0f, 0.0f,
//			0.0f, -0.5f, 0.0f, 0.0f,
//			0.0f, 0.0f, 1.0f, 0.0f,
//			0.5f, 0.5f, 0.0f, 1.0f);
//
//		XMMATRIX V = XMLoadFloat4x4(&view);
//		XMMATRIX P = XMLoadFloat4x4(&pres);
//
//		XMMATRIX VPT = V * P * T;
//		VPT = XMMatrixTranspose(VPT);
//
//		XMFLOAT4X4 shadowMatrix;
//		XMStoreFloat4x4(&shadowMatrix, VPT);
//		return Convert4x4(shadowMatrix);
//	}
//	CML::Matrix4x4 CalculateViewMatrix(std::shared_ptr<DirectionalLightINFO> lightInfo, const CML::Vec4 eye)
//	{
//		double pitch; double yaw; double roll;
//
//		pitch = lightInfo->Direction(0);
//		yaw = lightInfo->Direction(1);
//		roll = lightInfo->Direction(2);
//
//		XMFLOAT3 dir((float)pitch, (float)yaw, (float)roll);
//		XMVECTOR center = XMVectorSet((float)eye(0), (float)eye(1), (float)eye(2), (float)eye(3));
//
//		XMVECTOR lightDir = XMLoadFloat3(&dir);
//		XMVECTOR lightPos = (DirectLight::radius * lightDir) + center;
//		XMVECTOR targetPos = center;
//		XMVECTOR up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
//
//		XMMATRIX V = XMMatrixLookAtLH(lightPos, targetPos, up);
//
//		XMFLOAT4X4 vFloat4x4;
//		XMStoreFloat4x4(&vFloat4x4, V);
//		return Convert4x4(vFloat4x4);
//	}
//	CML::Matrix4x4 CalculatePrespectiveMatrix(std::shared_ptr<DirectionalLightINFO> lightInfo, const CML::Vec4 eye)
//	{
//		double pitch; double yaw; double roll;
//
//		pitch = lightInfo->Direction(0);
//		yaw = lightInfo->Direction(1);
//		roll = lightInfo->Direction(2);
//
//		XMFLOAT3 dir((float)pitch, (float)yaw, (float)roll);
//		XMVECTOR center = XMVectorSet((float)eye(0), (float)eye(1), (float)eye(2), (float)eye(3));
//
//		XMVECTOR lightDir = XMLoadFloat3(&dir);
//		XMVECTOR lightPos = (DirectLight::radius * lightDir) + center;
//		XMVECTOR targetPos = center;
//		XMVECTOR up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
//
//		XMMATRIX V = XMMatrixLookAtLH(lightPos, targetPos, up);
//
//		// Transform bounding sphere to light space.
//		XMFLOAT3 sphereCenterLS;
//		XMStoreFloat3(&sphereCenterLS, XMVector3TransformCoord(targetPos, V));
//
//		// Ortho frustum in light space encloses scene.
//		float l = sphereCenterLS.x - DirectLight::radius;
//		float b = sphereCenterLS.y - DirectLight::radius;
//		float n = sphereCenterLS.z - DirectLight::radius;
//		float r = sphereCenterLS.x + DirectLight::radius;
//		float t = sphereCenterLS.y + DirectLight::radius;
//		float f = sphereCenterLS.z + DirectLight::radius;
//		XMMATRIX P = XMMatrixOrthographicOffCenterLH(l, r, b, t, n, f);
//
//		XMFLOAT4X4 pFloat4x4;
//		XMStoreFloat4x4(&pFloat4x4, P);
//		return Convert4x4(pFloat4x4);
//	}
//	SceneInfo GetScene(std::shared_ptr<DirectionalLightINFO> lightInfo, const CML::Vec4 eye)
//	{
//		SceneInfo returnValue;
//		returnValue.Eye = eye;
//		returnValue.CamerMatrix = CalculateViewMatrix(lightInfo, eye);
//		returnValue.ProjectionMatrix = CalculatePrespectiveMatrix(lightInfo, eye);
//		returnValue.TwoDimMatrix = CalculatePrespectiveMatrix(lightInfo, eye);
//		returnValue.width = DirectLight::Width;
//		returnValue.height = DirectLight::Height;
//		returnValue.farZ = DirectLight::radius; 
//		returnValue.nearZ = 1.0;
//		returnValue.InclusionState = SceneInfo::InclusionType::All;
//		return returnValue;
//	}
//}