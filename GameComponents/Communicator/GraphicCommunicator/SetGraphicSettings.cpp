#include "SetGraphicSettings.h"

#include <GraphicManager.h>

ClearScreenMessage::ClearScreenMessage(const CHL::Vec4& input)
	: colour(input)
{
}

Message::Status ClearScreenMessage::Work()
{
	GraphicManager::GetInstance().ClearColour(0) = this->colour(0);
	GraphicManager::GetInstance().ClearColour(1) = this->colour(1);
	GraphicManager::GetInstance().ClearColour(2) = this->colour(2);

	return Message::Status::Complete;
}

SetCameraIDMessage::SetCameraIDMessage(const std::string& input)
: id(input)
{
}

Message::Status SetCameraIDMessage::Work()
{
	GraphicManager::GetInstance().SetCamera(this->id);
	return Message::Status::Complete;
}

SetPrespectiveIDMessage::SetPrespectiveIDMessage(const std::string& input)
: id(input)
{
}

Message::Status SetPrespectiveIDMessage::Work()
{
	GraphicManager::GetInstance().SetPrespective(this->id);
	return Message::Status::Complete;
}