#include "BasicScreenCaptureConfig.h"
#include <BasicScreenCapture.h>
#include <GraphicManager.h>
#include <boost/uuid/uuid_generators.hpp> // generators
#include <boost/uuid/uuid_io.hpp>         // streaming operators etc.
#include <InfoCommunicator/ObjectManagerOutput.h>
#include <BasicTexture.h>

BasicScreenCaptureConfig::AddBasicScreenCaptureMessage::AddBasicScreenCaptureMessage(unsigned int widthInput, unsigned int heightInput)
{
	this->ID = CHL::ToString(boost::uuids::random_generator()());
	this->width = widthInput;
	this->height = heightInput;
}

Message::Status BasicScreenCaptureConfig::AddBasicScreenCaptureMessage::Work()
{
	std::lock_guard<std::mutex> lock(GraphicManager::GetInstance().mutex);

	std::shared_ptr<BasicScreenCapture> newObject =
		BasicScreenCapture::Spawn(this->ID, this->width, this->height);

	GraphicManager::GetInstance().InsertScreenCapture(newObject);

	this->ID = newObject->ID;

	return Message::Status::Complete;
}

BasicScreenCaptureConfig::SnapPictureMessage::SnapPictureMessage(std::string ID, std::string cameraID, std::string prespectiveID)
{
	this->ID = ID;
	this->cameraID = cameraID;
	this->prespectiveID = prespectiveID;
	this->newTextureID = CHL::ToString(boost::uuids::random_generator()());
}

Message::Status BasicScreenCaptureConfig::SnapPictureMessage::Work()
{
	std::lock_guard<std::mutex> lock(GraphicManager::GetInstance().mutex);
	
	auto allScreenCaptures = GraphicManager::GetInstance().AllScreenCapture();

	auto ScreenCaptureIter = allScreenCaptures.find(this->ID);
	if (ScreenCaptureIter == allScreenCaptures.end())
	{
		throw std::exception(("Could not find screen capture with an ID of " + this->ID).c_str());
	}

	auto allObjects = ObjectManagerOutput::GetAllObjects();

	ScreenCaptureIter->second->Snap(allObjects, this->cameraID, this->prespectiveID);

	std::shared_ptr<Texture> newObject =
		BasicTexture::Spawn(this->newTextureID, ScreenCaptureIter->second->D3DInfo.pColorMapSRV);
	GraphicManager::GetInstance().InsertTexture(newObject);

	return Message::Status::Complete;
}