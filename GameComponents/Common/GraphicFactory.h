#ifndef __GraphicFactory__
#define __GraphicFactory__

#include "Linker.h"

#include "Interface.h"
#include "iGraphicModelFactory.h"
#include "iGraphicSettingsFactory.h"
#include "iShaderFactory.h"
#include "iScreenShotFactory.h"
#include "iTextureFactory.h"
#include "iBasicScreenCaptureFactory.h"
#include "iCubeScreenCaptureFactory.h"
#include "iDepthScreenCaptureFactory.h"
#include <memory>
#include <string>

class CommonDLL_API GraphicFactory
{
public:
	struct GraphicItem
	{
		std::shared_ptr<Interface> _GraphicInterface;
		std::shared_ptr<iGraphicModelFactory> _GraphicModelFactory;
		std::shared_ptr<iGraphicSettingsFactory> _GraphicSettingsFactory;
		std::shared_ptr<iShaderFactory> _ShaderFactory;
		std::shared_ptr<iScreenShotFactory> _ScreenShotFactory;
		std::shared_ptr<iTextureFactory> _TextureFactory;
		std::shared_ptr<iBasicScreenCaptureFactory> _BasicScreenCaptureFactory;
		std::shared_ptr<iCubeScreenCaptureFactory> _CubeScreenCaptureFactory;
		std::shared_ptr<iDepthScreenCaptureFactory> _DepthScreenCaptureFactory;
	};

	GraphicFactory(const GraphicFactory::GraphicItem& input);

	virtual bool Verify();

	virtual void SubmitMessage(std::shared_ptr<Message> msg);
	virtual std::shared_ptr<Interface> GetComponent();

	virtual std::shared_ptr<iGraphicModelFactory> GraphicModelFactory();
	virtual std::shared_ptr<iGraphicSettingsFactory> GraphicSettingsFactory();
	virtual std::shared_ptr<iShaderFactory> ShaderFactory();
	virtual std::shared_ptr<iScreenShotFactory> ScreenShotFactory();
	virtual std::shared_ptr<iTextureFactory> TextureFactory();
	virtual std::shared_ptr<iBasicScreenCaptureFactory> BasicScreenCaptureFactory();
	virtual std::shared_ptr<iCubeScreenCaptureFactory> CubeScreenCaptureFactory();
	virtual std::shared_ptr<iDepthScreenCaptureFactory> DepthScreenCaptureFactory();
protected:
	GraphicItem _ClassItems;
};

#endif //__GraphicFactory__