#include "AnimationFactory.h"

#include <Logger.h>

AnimationFactory::AnimationFactory(const AnimationFactory::AnimationItem& input) : _ClassItems(input)
{
	if(this->Verify() == false)
	{
		Logger::LogError("Failed to load Animation, factory component was not loaded.");
	}
}

bool AnimationFactory::Verify()
{
	if(this->_ClassItems._AnimationInterface == false){ return false; }
	if(this->_ClassItems._AnimationControllerFactory == false){ return false; }
	if(this->_ClassItems._BasicAnimationFactory == false){ return false; }

	return true;
}

void AnimationFactory::SubmitMessage(std::shared_ptr<Message> msg)
{
	this->_ClassItems._AnimationInterface->SubmitMessage(msg);
}
void AnimationFactory::SubmitMessage(std::function<Message::Status()> func)
{
	std::shared_ptr<FuncMessage> msg(new FuncMessage(func));
	this->_ClassItems._AnimationInterface->SubmitMessage(msg);
}
std::shared_ptr<Interface> AnimationFactory::GetComponent()
{
	return this->_ClassItems._AnimationInterface;
}

std::mutex& AnimationFactory::Mutex()
{
	return this->_ClassItems._AnimationInterface->mutex;
}

std::shared_ptr<iAnimationControllerFactory> AnimationFactory::AnimationControllerFactory()
{
	return this->_ClassItems._AnimationControllerFactory;
}
std::shared_ptr<iBasicAnimationFactory> AnimationFactory::BasicAnimationFactory()
{
	return this->_ClassItems._BasicAnimationFactory;
}