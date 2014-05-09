#ifndef __SPOTLIGHT__
#define __SPOTLIGHT__

#include <Singleton.h>
#include "Buffers.h"
#include <SpotLightINFO.h>
#include <Vector.h>
#include "SceneInfo.h"

namespace SpotLight
{
	GraphicComponentDLL_API cBuffer::CLightDesc GetLightDesc(std::shared_ptr<SpotLightINFO> lightInfo);
	GraphicComponentDLL_API CML::Matrix4x4 CalculateShadowMatrix(std::shared_ptr<SpotLightINFO> lightInfo, const CML::Vec4 eye);
	GraphicComponentDLL_API CML::Matrix4x4 CalculateViewMatrix(std::shared_ptr<SpotLightINFO> lightInfo, const CML::Vec4 eye);
	GraphicComponentDLL_API CML::Matrix4x4 CalculatePrespectiveMatrix(std::shared_ptr<SpotLightINFO> lightInfo, const CML::Vec4 eye);
	GraphicComponentDLL_API SceneInfo GetScene(std::shared_ptr<SpotLightINFO> lightInfo, const CML::Vec4 eye);
	static const unsigned int Width = 1024;
	static const unsigned int Height = 1024;
}

#endif //__SPOTLIGHT__