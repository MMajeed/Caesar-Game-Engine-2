#include "SetGraphicSettings.h"

#include <GraphicManager.h>

ClearScreenMessage::ClearScreenMessage(const CHL::Vec4& input)
	: colour(input)
{
}

Message::Status ClearScreenMessage::Work()
{
	GraphicManager::GetInstance().SceneInfo.ClearColour(0) = this->colour(0);
	GraphicManager::GetInstance().SceneInfo.ClearColour(1) = this->colour(1);
	GraphicManager::GetInstance().SceneInfo.ClearColour(2) = this->colour(2);

	return Message::Status::Complete;
}
