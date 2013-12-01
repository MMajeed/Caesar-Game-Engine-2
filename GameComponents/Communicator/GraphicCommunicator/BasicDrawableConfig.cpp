#include "BasicDrawableConfig.h"
#include <Vertex.h>
#include <BasicDrawable.h>
#include <GraphicManager.h>
#include <GenerateGUID.h>

BasicDrawableConfig::AddBasicDrawableMessage::AddBasicDrawableMessage(const Model& model,
													std::string	vertexFileName,
													std::string	pixelFileName,
													CULL_MODE cullMode,
													FILL_MODE fillMode)
	: model(model)
{
	this->ID = CHL::GenerateGUID();
	this->vertexFileName    = vertexFileName;
	this->pixelFileName     = pixelFileName;
	this->cullMode          = cullMode;
	this->fillMode          = fillMode;
}

Message::Status BasicDrawableConfig::AddBasicDrawableMessage::Work()
{
	auto vectorFaces = model.Faces();
	std::vector<WORD> vectorIndices;
	vectorIndices.reserve(vectorFaces.size());
	for(std::size_t i = 0; i < vectorFaces.size(); ++i)
	{
		vectorIndices.push_back((short)vectorFaces[i]);
	}

	auto vectorPos = model.Pos();
	auto vectorNormal = model.Normal();
	auto vectorTexture = model.Texture();
	std::vector<Vertex> vectorVertices;
	vectorVertices.reserve(vectorPos.size());

	for(std::size_t i = 0; i < vectorPos.size(); ++i)
	{
		Vertex v;
		auto pos = vectorPos[i];
		v.Pos = XMFLOAT4((float)pos(0), (float)pos(1), (float)pos(2), 1.0f) ;
		
		if(vectorNormal.size() > i)
		{
			auto normal = vectorNormal[i];
			v.Normal = XMFLOAT4((float)normal(0), (float)normal(1), (float)normal(2), 1.0f) ;
		}
		else
		{
			v.Normal = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f) ;
		}

		if(vectorTexture.size() > i)
		{
			auto texture = vectorTexture[i];
			v.Texture = XMFLOAT2((float)texture(0), (float)texture(1));
		}
		else
		{
			v.Texture = XMFLOAT2(0.0f, 0.0f) ;
		}

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