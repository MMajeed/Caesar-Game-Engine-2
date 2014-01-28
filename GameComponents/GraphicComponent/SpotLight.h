#ifndef __SPOTLIGHT__
#define __SPOTLIGHT__

#include <Singleton.h>
#include "Buffers.h"
#include <SpotLightINFO.h>
#include <Vector.h>
#include "SceneInfo.h"

namespace SpotLight
{
	cBuffer::CLightDesc GetLightDesc(std::shared_ptr<SpotLightINFO> lightInfo);
	CML::Matrix4x4 CalculateShadowMatrix(std::shared_ptr<SpotLightINFO> lightInfo, const CML::Vec4 eye);
	CML::Matrix4x4 CalculateViewMatrix(std::shared_ptr<SpotLightINFO> lightInfo, const CML::Vec4 eye);
	CML::Matrix4x4 CalculatePrespectiveMatrix(std::shared_ptr<SpotLightINFO> lightInfo, const CML::Vec4 eye);
	SceneInfo GetScene(std::shared_ptr<SpotLightINFO> lightInfo, const CML::Vec4 eye);
}

#endif //__SPOTLIGHT__