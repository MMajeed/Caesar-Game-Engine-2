#include "ProcessMessage.h"
#include "ScriptManager.h"
 
namespace ProcessMessage
{
	void Add(std::shared_ptr<LuaProcesses> process)
	{
		class AdddProcessMessage : public Message
		{
		public:
			AdddProcessMessage(std::shared_ptr<LuaProcesses> process)
			{
				this->item = process;
			}

			virtual Message::Status Work()
			{
				std::lock_guard<std::mutex> lock(ScriptManager::GetInstance().mutex);

				ScriptManager::GetInstance().SubmitProcesses(this->item->ID, this->item);

				return Message::Status::Complete;
			}

			std::shared_ptr<LuaProcesses> item;
		};

		std::shared_ptr<AdddProcessMessage> msg(new AdddProcessMessage(process));
		ScriptManager::GetInstance().SubmitMessage(msg);
	}
	void Add(std::shared_ptr<LuaProcesses> process, std::string ID)
	{
		class AdddProcessMessage : public Message
		{
		public:
			AdddProcessMessage(std::shared_ptr<LuaProcesses> process, std::string ID)
			{
				this->ID = ID;
				this->item = process;
			}

			virtual Message::Status Work()
			{
				std::lock_guard<std::mutex> lock(ScriptManager::GetInstance().mutex);

				ScriptManager::GetInstance().SubmitProcesses(this->ID, this->item);

				return Message::Status::Complete;
			}

			std::shared_ptr<LuaProcesses> item;
			std::string ID;
		};

		std::shared_ptr<AdddProcessMessage> msg(new AdddProcessMessage(process, ID));
		ScriptManager::GetInstance().SubmitMessage(msg);
	}
	void Remove(std::string ID)
	{
		class RemoveProcessMessage : public Message
		{
		public:
			RemoveProcessMessage(std::string ID)
			{
				this->ID = ID;
			}

			virtual Message::Status Work()
			{
				std::lock_guard<std::mutex> lock(ScriptManager::GetInstance().mutex);

				ScriptManager::GetInstance().RemoveProcesses(this->ID);

				return Message::Status::Complete;
			}
			std::string ID;
		};

		std::shared_ptr<RemoveProcessMessage> msg(new RemoveProcessMessage(ID));
		ScriptManager::GetInstance().SubmitMessage(msg);
	}
}
