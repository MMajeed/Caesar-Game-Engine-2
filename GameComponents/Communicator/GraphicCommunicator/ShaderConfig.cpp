#include "ShaderConfig.h"

#include <GenerateGUID.h>
#include <Message.h>
#include <ResourceManager.h>
#include <GraphicManager.h>
#include <VertexShader.h>
#include <PixelShader.h>
#include <GeometryShader.h>

namespace ShaderConfig
{
	namespace Vertex
	{
		std::string Create(std::string fileName)
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

					ResourceManager::VertexShaderList.Insert(this->ID, newObject);

					return Message::Status::Complete;
				}

				std::string	FileName;
				std::string	ID;
			};

			std::shared_ptr<CreateMessage> msg(new CreateMessage(fileName));
			GraphicManager::GetInstance().SubmitMessage(msg);
			return msg->ID;
		}
		void Release(std::string ID)
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

					ResourceManager::VertexShaderList.Remove(this->ID);

					return Message::Status::Complete;
				}
			};

			std::shared_ptr<ReleaseMessage> msg(new ReleaseMessage(ID));
			GraphicManager::GetInstance().SubmitMessage(msg);
		}
	}
	namespace Pixel
	{
		std::string Create(std::string fileName)
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

					ResourceManager::PixelShaderList.Insert(this->ID, newObject);

					return Message::Status::Complete;
				}

				std::string	FileName;
				std::string	ID;
			};

			std::shared_ptr<CreateMessage> msg(new CreateMessage(fileName));
			GraphicManager::GetInstance().SubmitMessage(msg);
			return msg->ID;
		}
		void Release(std::string ID)
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

					ResourceManager::PixelShaderList.Remove(this->ID);

					return Message::Status::Complete;
				}
			};

			std::shared_ptr<ReleaseMessage> msg(new ReleaseMessage(ID));
			GraphicManager::GetInstance().SubmitMessage(msg);
		}
	}
	namespace Geometry
	{
		std::string Create(std::string fileName)
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

					ResourceManager::GeometryShaderList.Insert(this->ID, newObject);

					return Message::Status::Complete;
				}

				std::string	FileName;
				std::string	ID;
			};

			std::shared_ptr<CreateGeometryShaderMessage> msg(new CreateGeometryShaderMessage(fileName));
			GraphicManager::GetInstance().SubmitMessage(msg);
			return msg->ID;
		}
		void Release(std::string ID)
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

					ResourceManager::GeometryShaderList.Remove(this->ID);

					return Message::Status::Complete;
				}
			};

			std::shared_ptr<ReleaseGeometryShaderMessage> msg(new ReleaseGeometryShaderMessage(ID));
			GraphicManager::GetInstance().SubmitMessage(msg);
		}
	}
}