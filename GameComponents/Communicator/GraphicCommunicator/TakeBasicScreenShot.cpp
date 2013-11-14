#include "TakeBasicScreenShot.h"
#include <BasicScreenCapture.h>
#include <GraphicManager.h>
#include <boost/uuid/uuid_generators.hpp> // generators
#include <boost/uuid/uuid_io.hpp>         // streaming operators etc.
#include <InfoCommunicator/ObjectManagerOutput.h>
#include <BasicTexture.h>

TakeBasicScreenShot::TakeBasicScreenShot(unsigned int width, unsigned int height, std::string cameraID, std::string prespectiveID)
{
	this->cameraID = cameraID;
	this->prespectiveID = prespectiveID;
	this->newTextureID = CHL::ToString(boost::uuids::random_generator()());
	this->width = width;
	this->height = height;
}

Message::Status TakeBasicScreenShot::Work()
{
	std::lock_guard<std::mutex> lock(GraphicManager::GetInstance().mutex);
	
	std::shared_ptr<BasicScreenCapture> newBasicScreenCapture =
		BasicScreenCapture::Spawn(CHL::ToString(boost::uuids::random_generator()()), this->width, this->height);
	
	auto allObjects = ObjectManagerOutput::GetAllObjects();

	newBasicScreenCapture->Snap(allObjects, this->cameraID, this->prespectiveID);

	auto texture = newBasicScreenCapture->GetScreenTexture();
	std::shared_ptr<Texture> newTexture =
		BasicTexture::Spawn(this->newTextureID, texture);
	GraphicManager::GetInstance().InsertTexture(newTexture);

	newBasicScreenCapture->Destory();

	return Message::Status::Complete;
}
