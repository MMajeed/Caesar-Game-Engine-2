#include "ClearScreenMessage.h"

#include "GraphicManager.h"

ClearScreenMessage::ClearScreenMessage(const boost::numeric::ublas::vector<double>& input)
	: colour(input)
{
}

Message::Status ClearScreenMessage::Work()
{
	GraphicManager::GetInstance().ClearColour = this->colour;
	return Message::Complete;
}