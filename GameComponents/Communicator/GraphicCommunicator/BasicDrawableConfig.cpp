#include "BasicDrawableConfig.h"
#include <Vertex.h>
#include <BasicDrawable.h>
#include <GraphicManager.h>
#include <GenerateGUID.h>
#include <ResourceManager.h>

namespace BasicDrawableConfig
{
	std::string Create(std::shared_ptr<CHL::Model> model,
					   std::string	vertexFileName,
					   std::string	pixelFileName,
					   std::string	GeometryFileName,
					   BasicDrawableConfig::CULL_MODE cullMode,
					   BasicDrawableConfig::FILL_MODE fillMode)
	{
		class  AddBasicDrawableMessage : public Message
		{
		public:
			AddBasicDrawableMessage(std::shared_ptr<CHL::Model> model,
									std::string	vertexFileName,
									std::string	pixelFileName,
									std::string	GeometryFileName,
									BasicDrawableConfig::CULL_MODE cullMode,
									BasicDrawableConfig::FILL_MODE fillMode)
			{
				this->ID = CHL::GenerateGUID();
				this->vertexFileName = vertexFileName;
				this->pixelFileName = pixelFileName;
				this->geometryFileName = GeometryFileName;
				this->cullMode = cullMode;
				this->fillMode = fillMode;
				this->model = model;
			}

			virtual Message::Status Work()
			{
				std::lock_guard<std::mutex> lock(GraphicManager::GetInstance().mutex);

				std::shared_ptr<BasicDrawable> newObject =
					BasicDrawable::Spawn(this->model,
										 this->vertexFileName,
										 this->pixelFileName,
										 this->geometryFileName,
										 static_cast<D3D11_CULL_MODE>(this->cullMode),
										 static_cast<D3D11_FILL_MODE>(this->fillMode));

				ResourceManager::DrawableList.Insert(this->ID, newObject);

				return Message::Status::Complete;
			}

			std::shared_ptr<CHL::Model> model;
			std::string	vertexFileName;
			std::string	pixelFileName;
			std::string	geometryFileName;
			BasicDrawableConfig::CULL_MODE cullMode;
			BasicDrawableConfig::FILL_MODE fillMode;

			std::string	ID;
		};

		std::shared_ptr<CHL::Model> modelClone(new CHL::Model(*model));
		std::shared_ptr<AddBasicDrawableMessage> msg
			(new AddBasicDrawableMessage(modelClone, vertexFileName, pixelFileName, GeometryFileName, cullMode, fillMode));
		GraphicManager::GetInstance().SubmitMessage(msg);
		return msg->ID;
	}
	std::string Create2D(std::shared_ptr<CHL::Model> model,
						 std::string	vertexFileName,
						 std::string	pixelFileName,
						 std::string	GeometryFileName,
						 BasicDrawableConfig::CULL_MODE cullMode,
						 BasicDrawableConfig::FILL_MODE fillMode)
	{
		
		return "";
	}

	void ChangeModel(std::string ID, std::shared_ptr<CHL::Model> model)
	{
		class ChangeModel : public Message
		{
		public:
			std::string ID;
			std::shared_ptr<CHL::Model> model;

			ChangeModel(const std::string& ID, const std::shared_ptr<CHL::Model>& model)
			{
				this->ID = ID;
				this->model = model;
			}

			virtual Message::Status Work()
			{
				std::lock_guard<std::mutex> lock(GraphicManager::GetInstance().mutex);

				auto object = ResourceManager::DrawableList.Find(this->ID);

				if(object)
				{
					std::shared_ptr<BasicDrawable> bdObj = std::dynamic_pointer_cast<BasicDrawable>(object);

					if(bdObj)
					{
						bdObj->ChangeModel(this->model);
					}
				}

				return Message::Status::Complete;
			}
		};
		std::shared_ptr<CHL::Model> modelClone(new CHL::Model(*model));
		std::shared_ptr<ChangeModel> msg(new ChangeModel(ID, modelClone));
		GraphicManager::GetInstance().SubmitMessage(msg);
	}

	void ChangeRastersizerState(std::string ID,
								BasicDrawableConfig::CULL_MODE cullMode,
								BasicDrawableConfig::FILL_MODE fillMode)
	{
		class ChangeRastersizerStateMessage : public Message
		{
		public:
			std::string ID;
			BasicDrawableConfig::CULL_MODE cullMode;
			BasicDrawableConfig::FILL_MODE fillMode;

			ChangeRastersizerStateMessage(std::string ID, BasicDrawableConfig::CULL_MODE cullMode, BasicDrawableConfig::FILL_MODE fillMode)
			{
				this->ID = ID;
				this->cullMode = cullMode;
				this->fillMode = fillMode;
			}

			virtual Message::Status Work()
			{
				std::lock_guard<std::mutex> lock(GraphicManager::GetInstance().mutex);

				auto object = ResourceManager::DrawableList.Find(this->ID);

				if(object)
				{
					std::shared_ptr<BasicDrawable> bdObj = std::dynamic_pointer_cast<BasicDrawable>(object);

					if(bdObj)
					{
						bdObj->ChangeRasterizerState(static_cast<D3D11_CULL_MODE>(this->cullMode),
													 static_cast<D3D11_FILL_MODE>(this->fillMode));
					}
				}

				return Message::Status::Complete;
			}
		};
		std::shared_ptr<ChangeRastersizerStateMessage> msg
			(new ChangeRastersizerStateMessage(ID, cullMode, fillMode));
		GraphicManager::GetInstance().SubmitMessage(msg);
	}

	void ChangeVS(std::string ID, std::string fileName)
	{
		class ChangeVSMessage : public Message
		{
		public:
			std::string ID;
			std::string fileName;

			ChangeVSMessage(std::string ID, std::string fileName)
			{
				this->ID = ID;
				this->fileName = fileName;
			}

			virtual Message::Status Work()
			{
				std::lock_guard<std::mutex> lock(GraphicManager::GetInstance().mutex);

				auto object = ResourceManager::DrawableList.Find(this->ID);

				if(object)
				{
					std::shared_ptr<BasicDrawable> bdObj = std::dynamic_pointer_cast<BasicDrawable>(object);

					if(bdObj)
					{
						bdObj->ChangeVS(this->fileName);
					}
				}

				return Message::Status::Complete;
			}
		};
		std::shared_ptr<ChangeVSMessage> msg
			(new ChangeVSMessage(ID, fileName));
		GraphicManager::GetInstance().SubmitMessage(msg);
	}
	void ChangeGS(std::string ID, std::string fileName)
	{
		class ChangeGSMessage : public Message
		{
		public:
			std::string ID;
			std::string fileName;

			ChangeGSMessage(std::string ID, std::string fileName)
			{
				this->ID = ID;
				this->fileName = fileName;
			}

			virtual Message::Status Work()
			{
				std::lock_guard<std::mutex> lock(GraphicManager::GetInstance().mutex);

				auto object = ResourceManager::DrawableList.Find(this->ID);

				if(object)
				{
					std::shared_ptr<BasicDrawable> bdObj = std::dynamic_pointer_cast<BasicDrawable>(object);

					if(bdObj)
					{
						bdObj->ChangeGS(this->fileName);
					}
				}

				return Message::Status::Complete;
			}
		};
		std::shared_ptr<ChangeGSMessage> msg
			(new ChangeGSMessage(ID, fileName));
		GraphicManager::GetInstance().SubmitMessage(msg);
	}
	void ChangePS(std::string ID, std::string fileName)
	{
		class ChangePSMessage : public Message
		{
		public:
			std::string ID;
			std::string fileName;

			ChangePSMessage(std::string ID, std::string fileName)
			{
				this->ID = ID;
				this->fileName = fileName;
			}

			virtual Message::Status Work()
			{
				std::lock_guard<std::mutex> lock(GraphicManager::GetInstance().mutex);

				auto object = ResourceManager::DrawableList.Find(this->ID);

				if(object)
				{
					std::shared_ptr<BasicDrawable> bdObj = std::dynamic_pointer_cast<BasicDrawable>(object);

					if(bdObj)
					{
						bdObj->ChangePS(this->fileName);
					}
				}

				return Message::Status::Complete;
			}
		};
		std::shared_ptr<ChangePSMessage> msg
			(new ChangePSMessage(ID, fileName));
		GraphicManager::GetInstance().SubmitMessage(msg);
	}
	void Release(std::string ID)
	{
		class ReleaseBasicDrawable : public Message
		{
		public:
			std::string ID;
			ReleaseBasicDrawable(std::string ID)
			{
				this->ID = ID;
			}

			virtual Message::Status Work()
			{
				std::lock_guard<std::mutex> lock(GraphicManager::GetInstance().mutex);

				ResourceManager::DrawableList.Remove(this->ID);

				return Message::Status::Complete;
			}
		};

		std::shared_ptr<ReleaseBasicDrawable> msg
			(new ReleaseBasicDrawable(ID));
		GraphicManager::GetInstance().SubmitMessage(msg);
	}
}