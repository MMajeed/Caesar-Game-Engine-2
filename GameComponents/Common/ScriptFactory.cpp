#include "ScriptFactory.h"

#include <Logger.h>

ScriptFactory::ScriptFactory(const ScriptFactory::ScriptItem& input) : _ClassItems(input)
{
	if(this->Verify() == false)
	{
		Logger::LogError("Failed to load Script, factory component was not loaded.");
	}
}

bool ScriptFactory::Verify()
{
	if(this->_ClassItems._ScriptInterface == false){ return false; }

	return true;
}

void ScriptFactory::SubmitMessage(std::shared_ptr<Message> msg)
{
	this->_ClassItems._ScriptInterface->SubmitMessage(msg);
}
void ScriptFactory::SubmitMessage(std::function<Message::Status()> func)
{
	std::shared_ptr<FuncMessage> msg(new FuncMessage(func));
	this->_ClassItems._ScriptInterface->SubmitMessage(msg);
}
std::shared_ptr<Interface> ScriptFactory::GetComponent()
{
	return this->_ClassItems._ScriptInterface;
}

std::mutex& ScriptFactory::Mutex()
{
	return this->_ClassItems._ScriptInterface->mutex;
}