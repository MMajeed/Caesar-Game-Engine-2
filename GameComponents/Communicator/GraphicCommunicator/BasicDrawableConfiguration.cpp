#include "BasicDrawableConfiguration.h"

#include <Vertex.h>
#include <D3DShaderInfo.h>
#include "BasicDrawable.h"
#include "GraphicManager.h"

BasicDrawableConfiguration::AddBasicDrawableMessage::AddBasicDrawableMessage(const Model& model,
												std::string	vertexFileName,
												std::string	vertexEntryPoint,
												std::string	vertexModel,
												std::string	pixelFileName,
												std::string	pixelEntryPoint,
												std::string	pixelModel)
	: model(model)
{
	this->vertexFileName = vertexFileName;
	this->vertexEntryPoint = vertexEntryPoint;
	this->vertexModel = vertexModel;
	this->vertexModel = vertexModel;
	this->pixelFileName = pixelFileName;
	this->pixelEntryPoint = pixelEntryPoint;
	this->pixelModel = pixelModel;
}

Message::Status BasicDrawableConfiguration::AddBasicDrawableMessage::Work()
{
	D3DShaderInfo vertexFile;
	vertexFile.FileName		= vertexFileName;
	vertexFile.EntryPoint	= vertexEntryPoint;
	vertexFile.Model		= vertexModel;

	D3DShaderInfo pixelFile;
	pixelFile.FileName		= pixelFileName;
	pixelFile.EntryPoint	= pixelEntryPoint;
	pixelFile.Model			= pixelModel;

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

	boost::mutex::scoped_lock lock(GraphicManager::GetInstance().mutex);

	std::shared_ptr<BasicDrawable> newObject =
		BasicDrawable::Spawn(vectorVertices,
							vectorIndices,
							vertexFile,
							pixelFile);

	GraphicManager::GetInstance().InsertObjectDrawable(newObject);

	this->ID = newObject->ID;

	return Message::Status::Complete;
}

BasicDrawableConfiguration::ChangeRastersizerState::ChangeRastersizerState
	(std::string ID, CULL_MODE cullMode, FILL_MODE fillMode, bool antialiasedLine, bool multisampleEnable)
{
	this->ID = ID;
	this->cullMode = cullMode;
	this->fillMode = fillMode;
	this->antialiasedLine = antialiasedLine;
	this->multisampleEnable = multisampleEnable;
}

Message::Status BasicDrawableConfiguration::ChangeRastersizerState::Work()
{
	boost::mutex::scoped_lock lock(GraphicManager::GetInstance().mutex);

	auto allObjects = GraphicManager::GetInstance().AllObjectDrawables();
	auto iterObjDrawable = allObjects.find(this->ID);

	if(iterObjDrawable != allObjects.end())
	{
		std::shared_ptr<BasicDrawable> bdObj = std::dynamic_pointer_cast<BasicDrawable>(iterObjDrawable->second);

		if(bdObj)
		{
			ID3D11Device* pDevice = GraphicManager::GetInstance().direct3d.pd3dDevice;
			bdObj->D3DInfo.pRastersizerState->Release();

			bdObj->InitRastersizerState(pDevice,
										static_cast<D3D11_CULL_MODE>(this->cullMode), 
										static_cast<D3D11_FILL_MODE>(this->fillMode), 
										this->antialiasedLine, 
										this->multisampleEnable);
		}
	}

	return Message::Status::Complete;
}