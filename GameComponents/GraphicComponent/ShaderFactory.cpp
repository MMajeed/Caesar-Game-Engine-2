#include "ShaderFactory.h"

#include <GenerateGUID.h>
#include <Message.h>
#include "Resource.h"
#include "GraphicManager.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "GeometryShader.h"

std::string ShaderFactory::VertexCreate(std::string fileName)
{
	class CreateMessage : public Message
	{
	public:
		CreateMessage(std::string texture)
		{
			this->ID = CHL::GenerateGUID();
			this->FileName = texture;
		}

		virtual Message::Status Work()
		{
			std::lock_guard<std::mutex> lock(GraphicManager::GetInstance().mutex);

			std::shared_ptr<VertexShader> newObject = VertexShader::Spawn(this->FileName);

			Resource::VertexShaderList[this->ID] = newObject;

			return Message::Status::Complete;
		}

		std::string	FileName;
		std::string	ID;
	};

	std::shared_ptr<CreateMessage> msg(new CreateMessage(fileName));
	GraphicManager::GetInstance().SubmitMessage(msg);
	return msg->ID;
}
void ShaderFactory::VertexRelease(std::string ID)
{
	class ReleaseMessage : public Message
	{
	public:
		std::string ID;
		ReleaseMessage(std::string ID)
		{
			this->ID = ID;
		}

		virtual Message::Status Work()
		{
			std::lock_guard<std::mutex> lock(GraphicManager::GetInstance().mutex);

			Resource::VertexShaderList.erase(this->ID);

			return Message::Status::Complete;
		}
	};

	std::shared_ptr<ReleaseMessage> msg(new ReleaseMessage(ID));
	GraphicManager::GetInstance().SubmitMessage(msg);
}

std::string ShaderFactory::PixelCreate(std::string fileName)
{
	class CreateMessage : public Message
	{
	public:
		CreateMessage(std::string texture)
		{
			this->ID = CHL::GenerateGUID();
			this->FileName = texture;
		}

		virtual Message::Status Work()
		{
			std::lock_guard<std::mutex> lock(GraphicManager::GetInstance().mutex);

			std::shared_ptr<PixelShader> newObject = PixelShader::Spawn(this->FileName);

			Resource::PixelShaderList[this->ID] = newObject;

			return Message::Status::Complete;
		}

		std::string	FileName;
		std::string	ID;
	};

	std::shared_ptr<CreateMessage> msg(new CreateMessage(fileName));
	GraphicManager::GetInstance().SubmitMessage(msg);
	return msg->ID;
}
void ShaderFactory::PixelRelease(std::string ID)
{
	class ReleaseMessage : public Message
	{
	public:
		std::string ID;
		ReleaseMessage(std::string ID)
		{
			this->ID = ID;
		}

		virtual Message::Status Work()
		{
			std::lock_guard<std::mutex> lock(GraphicManager::GetInstance().mutex);

			Resource::PixelShaderList.erase(this->ID);

			return Message::Status::Complete;
		}
	};

	std::shared_ptr<ReleaseMessage> msg(new ReleaseMessage(ID));
	GraphicManager::GetInstance().SubmitMessage(msg);
}

std::string ShaderFactory::GeometryCreate(std::string fileName)
{
	class CreateGeometryShaderMessage : public Message
	{
	public:
		CreateGeometryShaderMessage(std::string texture)
		{
			this->ID = CHL::GenerateGUID();
			this->FileName = texture;
		}

		virtual Message::Status Work()
		{
			std::lock_guard<std::mutex> lock(GraphicManager::GetInstance().mutex);

			std::shared_ptr<GeometryShader> newObject = GeometryShader::Spawn(this->FileName);

			Resource::GeometryShaderList[this->ID] = newObject;

			return Message::Status::Complete;
		}

		std::string	FileName;
		std::string	ID;
	};

	std::shared_ptr<CreateGeometryShaderMessage> msg(new CreateGeometryShaderMessage(fileName));
	GraphicManager::GetInstance().SubmitMessage(msg);
	return msg->ID;
}
void ShaderFactory::GeometryRelease(std::string ID)
{
	class ReleaseGeometryShaderMessage : public Message
	{
	public:
		std::string ID;
		ReleaseGeometryShaderMessage(std::string ID)
		{
			this->ID = ID;
		}

		virtual Message::Status Work()
		{
			std::lock_guard<std::mutex> lock(GraphicManager::GetInstance().mutex);

			Resource::GeometryShaderList.erase(this->ID);

			return Message::Status::Complete;
		}
	};

	std::shared_ptr<ReleaseGeometryShaderMessage> msg(new ReleaseGeometryShaderMessage(ID));
	GraphicManager::GetInstance().SubmitMessage(msg);
}