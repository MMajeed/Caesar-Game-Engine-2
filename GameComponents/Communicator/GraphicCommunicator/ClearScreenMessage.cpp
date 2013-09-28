#include "ClearScreenMessage.h"

#include <GraphicManager.h>

ClearScreenMessage::ClearScreenMessage(const boost::numeric::ublas::vector<double>& input)
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