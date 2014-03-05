#ifndef __DIRECTLIGHT__
#define __DIRECTLIGHT__

#include <Singleton.h>
#include <DirectionalLightINFO.h>
#include "Buffers.h"
#include <Vector.h>
#include "SceneInfo.h"

namespace DirectLight
{
	cBuffer::CLightDesc GetLightDesc(std::shared_ptr<DirectionalLightINFO> lightInfo);
	CML::Matrix4x4 CalculateShadowMatrix(std::shared_ptr<DirectionalLightINFO> lightInfo, const CML::Vec4 eye);
	CML::Matrix4x4 CalculateViewMatrix(std::shared_ptr<DirectionalLightINFO> lightInfo, const CML::Vec4 eye);
	CML::Matrix4x4 CalculatePrespectiveMatrix(std::shared_ptr<DirectionalLightINFO> lightInfo, const CML::Vec4 eye);
	SceneInfo GetScene(std::shared_ptr<DirectionalLightINFO> lightInfo, const CML::Vec4 eye);
	static const float radius = 100.0f;
	static const unsigned int Width = 1024;
	static const unsigned int Height = 1024;
}

#endif //__DIRECTLIGHT__