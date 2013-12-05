#include "BasicDrawableConfig.h"
#include <Vertex.h>
#include <BasicDrawable.h>
#include <GraphicManager.h>
#include <GenerateGUID.h>

BasicDrawableConfig::AddBasicDrawableMessage::AddBasicDrawableMessage(const CHL::Model& model,
	std::string	vertexFileName,
	std::string	pixelFileName,
	CULL_MODE cullMode,
	FILL_MODE fillMode)
	: model(model)
{
	this->ID = CHL::GenerateGUID();
	this->vertexFileName = vertexFileName;
	this->pixelFileName = pixelFileName;
	this->cullMode = cullMode;
	this->fillMode = fillMode;
}

Message::Status BasicDrawableConfig::AddBasicDrawableMessage::Work()
{
	auto vectorFaces = model.Faces;
	std::vector<WORD> vectorIndices;
	vectorIndices.reserve(vectorFaces.size());
	for(std::size_t i = 0; i < vectorFaces.size(); ++i)
	{
		vectorIndices.push_back((WORD)vectorFaces[i]);
	}

	auto modelVertices = model.Vertices;
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

BasicDrawableConfig::ChangeRastersizerState::ChangeRastersizerState(std::string ID, CULL_MODE cullMode, FILL_MODE fillMode)
{
	this->ID = ID;
	this->cullMode = cullMode;
	this->fillMode = fillMode;
}

Message::Status BasicDrawableConfig::ChangeRastersizerState::Work()
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