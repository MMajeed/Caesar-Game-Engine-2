#ifndef __DIRECTLIGHT__
#define __DIRECTLIGHT__

#include <Singleton.h>
#include <DirectionalLightINFO.h>
#include "Buffers.h"
#include <Matrix.h>
#include "SceneInfo.h"

namespace DirectLight
{
	cBuffer::CLightDesc GetLightDesc(std::shared_ptr<DirectionalLightINFO> lightInfo);
	CHL::Matrix4x4 CalculateShadowMatrix(std::shared_ptr<DirectionalLightINFO> lightInfo, const CHL::Vec4 eye);
	CHL::Matrix4x4 CalculateViewMatrix(std::shared_ptr<DirectionalLightINFO> lightInfo, const CHL::Vec4 eye);
	CHL::Matrix4x4 CalculatePrespectiveMatrix(std::shared_ptr<DirectionalLightINFO> lightInfo, const CHL::Vec4 eye);
	SceneInfo GetScene(std::shared_ptr<DirectionalLightINFO> lightInfo, const CHL::Vec4 eye);
	static const float radius = 100.0f;
}

#endif //__DIRECTLIGHT__