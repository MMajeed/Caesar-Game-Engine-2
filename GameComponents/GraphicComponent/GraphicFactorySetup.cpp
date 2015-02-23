#include "GraphicFactorySetup.h"

#include "GraphicModelFactory.h"
#include "GraphicSettingsFactory.h"
#include "ShaderFactory.h"
#include "ScreenShotFactory.h"
#include "TextureFactory.h"
#include "BasicScreenCaptureFactory.h"
#include "CubeScreenCaptureFactory.h"
#include "DepthScreenCaptureFactory.h"
#include "GraphicManager.h"

namespace GraphicFactorySetup
{
	GraphicFactory::GraphicItem Load()
	{
		GraphicFactory::GraphicItem returnValue;

		returnValue._GraphicModelFactory = std::shared_ptr<GraphicModelFactory>(new GraphicModelFactory);
		returnValue._GraphicSettingsFactory = std::shared_ptr<GraphicSettingsFactory>(new GraphicSettingsFactory);
		returnValue._ShaderFactory = std::shared_ptr<ShaderFactory>(new ShaderFactory);
		returnValue._ScreenShotFactory = std::shared_ptr<ScreenShotFactory>(new ScreenShotFactory);
		returnValue._TextureFactory = std::shared_ptr<TextureFactory>(new TextureFactory);
		returnValue._BasicScreenCaptureFactory = std::shared_ptr<BasicScreenCaptureFactory>(new BasicScreenCaptureFactory);
		returnValue._CubeScreenCaptureFactory = std::shared_ptr<CubeScreenCaptureFactory>(new CubeScreenCaptureFactory);
		returnValue._DepthScreenCaptureFactory = std::shared_ptr<DepthScreenCaptureFactory>(new DepthScreenCaptureFactory);
		returnValue._GraphicInterface = GraphicManager::GetPointer();

		return returnValue;
	}
};