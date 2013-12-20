#include "BasicDrawableConfig.h"
#include <Vertex.h>
#include <BasicDrawable.h>
#include <Basic2DDrawable.h>
#include <GraphicManager.h>
#include <GenerateGUID.h>


namespace BasicDrawableConfig
{
	std::string Create(std::shared_ptr<CHL::Model> model,
					   std::string	vertexFileName,
					   std::string	pixelFileName,
					   BasicDrawableConfig::CULL_MODE cullMode,
					   BasicDrawableConfig::FILL_MODE fillMode)
	{
		class  AddBasicDrawableMessage : public Message
		{
		public:
			AddBasicDrawableMessage(std::shared_ptr<CHL::Model> model,
									std::string	vertexFileName,
									std::string	pixelFileName,
									BasicDrawableConfig::CULL_MODE cullMode,
									BasicDrawableConfig::FILL_MODE fillMode)
			{
				this->ID = CHL::GenerateGUID();
				this->vertexFileName = vertexFileName;
				this->pixelFileName = pixelFileName;
				this->cullMode = cullMode;
				this->fillMode = fillMode;
				this->model = model;
			}

			virtual Message::Status Work()
			{
				auto vectorFaces = model->Faces;
				std::vector<WORD> vectorIndices;
				vectorIndices.reserve(vectorFaces.size());
				for(std::size_t i = 0; i < vectorFaces.size(); ++i)
				{
					vectorIndices.push_back((WORD)vectorFaces[i]);
				}

				auto modelVertices = model->Vertices;
				std::vector<Vertex> vectorVertices;
				vectorVertices.reserve(modelVertices.size());

				for(std::size_t i = 0; i < modelVertices.size(); ++i)
				{
					Vertex v;
					auto ver = modelVertices[i];
					v.Pos = XMFLOAT4((float)ver.Point(0), (float)ver.Point(1), (float)ver.Point(2), 1.0);
					v.Normal = XMFLOAT4((float)ver.Normal(0), (float)ver.Normal(1), (float)ver.Normal(2), 1.0);
					v.Texture = XMFLOAT3((float)ver.Texture(0), (float)ver.Texture(1), (float)ver.Texture(2));

					vectorVertices.push_back(v);
				}

				std::lock_guard<std::mutex> lock(GraphicManager::GetInstance().mutex);

				std::shared_ptr<BasicDrawable> newObject =
					BasicDrawable::Spawn(this->ID,
					vectorVertices,
					vectorIndices,
					vertexFileName,
					pixelFileName,
					static_cast<D3D11_CULL_MODE>(this->cullMode),
					static_cast<D3D11_FILL_MODE>(this->fillMode));

				GraphicManager::GetInstance().InsertObjectDrawable(newObject);

				this->ID = newObject->ID;

				return Message::Status::Complete;
			}

			std::shared_ptr<CHL::Model> model;
			std::string	vertexFileName;
			std::string	pixelFileName;
			BasicDrawableConfig::CULL_MODE cullMode;
			BasicDrawableConfig::FILL_MODE fillMode;

			std::string	ID;
		};

		std::shared_ptr<AddBasicDrawableMessage> msg
			(new AddBasicDrawableMessage(model, vertexFileName, pixelFileName, cullMode, fillMode));
		GraphicManager::GetInstance().SubmitMessage(msg);
		return msg->ID;
	}
	std::string Create2D(std::shared_ptr<CHL::Model> model,
						 std::string	vertexFileName,
						 std::string	pixelFileName,
						 BasicDrawableConfig::CULL_MODE cullMode,
						 BasicDrawableConfig::FILL_MODE fillMode)
	{
		class  AddBasicDrawableMessage : public Message
		{
		public:
			AddBasicDrawableMessage(std::shared_ptr<CHL::Model> model,
									std::string	vertexFileName,
									std::string	pixelFileName,
									BasicDrawableConfig::CULL_MODE cullMode,
									BasicDrawableConfig::FILL_MODE fillMode)
			{
				this->ID = CHL::GenerateGUID();
				this->vertexFileName = vertexFileName;
				this->pixelFileName = pixelFileName;
				this->cullMode = cullMode;
				this->fillMode = fillMode;
				this->model = model;
			}

			virtual Message::Status Work()
			{
				auto vectorFaces = model->Faces;
				std::vector<WORD> vectorIndices;
				vectorIndices.reserve(vectorFaces.size());
				for(std::size_t i = 0; i < vectorFaces.size(); ++i)
				{
					vectorIndices.push_back((WORD)vectorFaces[i]);
				}

				auto modelVertices = model->Vertices;
				std::vector<Vertex> vectorVertices;
				vectorVertices.reserve(modelVertices.size());

				for(std::size_t i = 0; i < modelVertices.size(); ++i)
				{
					Vertex v;
					auto ver = modelVertices[i];
					v.Pos = XMFLOAT4((float)ver.Point(0), (float)ver.Point(1), (float)ver.Point(2), 1.0);
					v.Normal = XMFLOAT4((float)ver.Normal(0), (float)ver.Normal(1), (float)ver.Normal(2), 1.0);
					v.Texture = XMFLOAT3((float)ver.Texture(0), (float)ver.Texture(1), (float)ver.Texture(2));

					vectorVertices.push_back(v);
				}

				std::lock_guard<std::mutex> lock(GraphicManager::GetInstance().mutex);

				std::shared_ptr<Basic2DDrawable> newObject =
					Basic2DDrawable::Spawn( this->ID,
											vectorVertices,
											vectorIndices,
											vertexFileName,
											pixelFileName,
											static_cast<D3D11_CULL_MODE>(this->cullMode),
											static_cast<D3D11_FILL_MODE>(this->fillMode));

				GraphicManager::GetInstance().InsertObjectDrawable(newObject);

				return Message::Status::Complete;
			}

			std::shared_ptr<CHL::Model> model;
			std::string	vertexFileName;
			std::string	pixelFileName;
			BasicDrawableConfig::CULL_MODE cullMode;
			BasicDrawableConfig::FILL_MODE fillMode;

			std::string	ID;
		};

		std::shared_ptr<AddBasicDrawableMessage> msg
			(new AddBasicDrawableMessage(model, vertexFileName, pixelFileName, cullMode, fillMode));
		GraphicManager::GetInstance().SubmitMessage(msg);
		return msg->ID;
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
				auto vectorFaces = model->Faces;
				std::vector<WORD> vectorIndices;
				vectorIndices.reserve(vectorFaces.size());
				for(std::size_t i = 0; i < vectorFaces.size(); ++i)
				{
					vectorIndices.push_back((WORD)vectorFaces[i]);
				}

				auto modelVertices = model->Vertices;
				std::vector<Vertex> vectorVertices;
				vectorVertices.reserve(modelVertices.size());

				for(std::size_t i = 0; i < modelVertices.size(); ++i)
				{
					Vertex v;
					auto ver = modelVertices[i];
					v.Pos = XMFLOAT4((float)ver.Point(0), (float)ver.Point(1), (float)ver.Point(2), 1.0);
					v.Normal = XMFLOAT4((float)ver.Normal(0), (float)ver.Normal(1), (float)ver.Normal(2), 1.0);
					v.Texture = XMFLOAT3((float)ver.Texture(0), (float)ver.Texture(1), (float)ver.Texture(2));

					vectorVertices.push_back(v);
				}

				std::lock_guard<std::mutex> lock(GraphicManager::GetInstance().mutex);

				auto allObjects = GraphicManager::GetInstance().AllObjectDrawables();
				auto iterObjDrawable = allObjects.find(this->ID);

				if(iterObjDrawable != allObjects.end())
				{
					std::shared_ptr<BasicDrawable> bdObj = std::dynamic_pointer_cast<BasicDrawable>(iterObjDrawable->second);

					if(bdObj)
					{
						bdObj->ChangeModel(vectorVertices, vectorIndices);
					}
				}

				return Message::Status::Complete;
			}
		};
		std::shared_ptr<ChangeModel> msg(new ChangeModel(ID, model));
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

				auto allObjects = GraphicManager::GetInstance().AllObjectDrawables();
				auto iterObjDrawable = allObjects.find(this->ID);

				if(iterObjDrawable != allObjects.end())
				{
					std::shared_ptr<BasicDrawable> bdObj = std::dynamic_pointer_cast<BasicDrawable>(iterObjDrawable->second);

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

				GraphicManager::GetInstance().RemoveObjectDrawable(this->ID);

				return Message::Status::Complete;
			}
		};

		std::shared_ptr<ReleaseBasicDrawable> msg
			(new ReleaseBasicDrawable(ID));
		GraphicManager::GetInstance().SubmitMessage(msg);
	}
}