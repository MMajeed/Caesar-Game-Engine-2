#include "GraphicFactory.h"

#include <Logger.h>

GraphicFactory::GraphicFactory(const GraphicFactory::GraphicItem& input) : _ClassItems(input)
{
	if(this->Verify() == false)
	{
		Logger::LogError("Failed to load Graphic, factory component was not loaded.");
	}
}

bool GraphicFactory::Verify()
{
	if(this->_ClassItems._GraphicInterface == false){ return false; }
	if(this->_ClassItems._GraphicModelFactory == false){ return false; }
	if(this->_ClassItems._GraphicSettingsFactory == false){ return false; }
	if(this->_ClassItems._ShaderFactory == false){ return false; }
	if(this->_ClassItems._ScreenShotFactory == false){ return false; }
	if(this->_ClassItems._TextureFactory == false){ return false; }
	if(this->_ClassItems._BasicScreenCaptureFactory == false){ return false; }
	if(this->_ClassItems._CubeScreenCaptureFactory == false){ return false; }
	if(this->_ClassItems._DepthScreenCaptureFactory == false){ return false; }

	return true;
}

void GraphicFactory::SubmitMessage(std::shared_ptr<Message> msg)
{
	this->_ClassItems._GraphicInterface->SubmitMessage(msg);
}
std::shared_ptr<Interface> GraphicFactory::GetComponent()
{
	return this->_ClassItems._GraphicInterface;
}

std::shared_ptr<iGraphicModelFactory> GraphicFactory::GraphicModelFactory()
{
	return this->_ClassItems._GraphicModelFactory;
}
std::shared_ptr<iGraphicSettingsFactory> GraphicFactory::GraphicSettingsFactory()
{
	return this->_ClassItems._GraphicSettingsFactory;
}
std::shared_ptr<iShaderFactory> GraphicFactory::ShaderFactory()
{
	return this->_ClassItems._ShaderFactory;
}
std::shared_ptr<iScreenShotFactory> GraphicFactory::ScreenShotFactory()
{
	return this->_ClassItems._ScreenShotFactory;
}
std::shared_ptr<iTextureFactory> GraphicFactory::TextureFactory()
{
	return this->_ClassItems._TextureFactory;
}
std::shared_ptr<iBasicScreenCaptureFactory> GraphicFactory::BasicScreenCaptureFactory()
{
	return this->_ClassItems._BasicScreenCaptureFactory;
}
std::shared_ptr<iCubeScreenCaptureFactory> GraphicFactory::CubeScreenCaptureFactory()
{
	return this->_ClassItems._CubeScreenCaptureFactory;
}
std::shared_ptr<iDepthScreenCaptureFactory> GraphicFactory::DepthScreenCaptureFactory()
{
	return this->_ClassItems._DepthScreenCaptureFactory;
}