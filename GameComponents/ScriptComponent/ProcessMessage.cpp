#include "ProcessMessage.h"
#include "LuaManager.h"
 
namespace ProcessMessage
{
	std::string Add(std::shared_ptr<LuaProcesses> process)
	{
		class AdddProcessMessage : public Message
		{
		public:
			AdddProcessMessage(std::shared_ptr<LuaProcesses> process)
			{
				this->ID = CHL::GenerateGUID();
				this->item = process;
			}

			virtual Message::Status Work()
			{
				std::lock_guard<std::mutex> lock(LuaManager::GetInstance().mutex);

				LuaManager::GetInstance().SubmitProcesses(this->ID, this->item);

				return Message::Status::Complete;
			}

			std::shared_ptr<LuaProcesses> item;
			std::string ID;
		};

		std::shared_ptr<AdddProcessMessage> msg(new AdddProcessMessage(process));
		LuaManager::GetInstance().SubmitMessage(msg);
		return msg->ID;
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
				std::lock_guard<std::mutex> lock(LuaManager::GetInstance().mutex);

				LuaManager::GetInstance().RemoveProcesses(this->ID);

				return Message::Status::Complete;
			}
			std::string ID;
		};

		std::shared_ptr<RemoveProcessMessage> msg(new RemoveProcessMessage(ID));
		LuaManager::GetInstance().SubmitMessage(msg);
	}
}
