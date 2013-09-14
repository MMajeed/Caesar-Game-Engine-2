#include "AddBasicDrawableMessage.h"

#include "BasicDrawable.h"
#include "GraphicManager.h"

AddBasicDrawableMessage::AddBasicDrawableMessage(std::string newID,
												const Model& model,
												std::string	vertexFileName,
												std::string	vertexEntryPoint,
												std::string	vertexModel,
												std::string	pixelFileName,
												std::string	pixelEntryPoint,
												std::string	pixelModel,
												std::string texture)
{
	this->ID = newID;

	this->vertexFile.FileName		= vertexFileName;
	this->vertexFile.EntryPoint		= vertexEntryPoint;
	this->vertexFile.Model			= vertexModel;

	this->pixelFile.FileName		= pixelFileName;
	this->pixelFile.EntryPoint		= pixelEntryPoint;
	this->pixelFile.Model			= pixelModel;


	auto vectorFaces = model.Faces();
	this->vectorIndices.reserve(vectorFaces.size());
	for(std::size_t i = 0; i < vectorFaces.size(); ++i)
	{
		this->vectorIndices.push_back((short)vectorFaces[i]);
	}

	auto vectorPos = model.Pos();
	auto vectorNormal = model.Normal();
	auto vectorTexture = model.Texture();
	this->vectorVertices.resize(vectorPos.size());

	for(std::size_t i = 0; i < vectorPos.size(); ++i)
	{
		Vertex v;
		auto pos = vectorPos[i];
		v.Pos = XMFLOAT4((float)pos(0), (float)pos(1), (float)pos(2), (float)pos(3)) ;
		
		if(vectorNormal.size() < i)
		{
			auto normal = vectorNormal[i];
			v.Normal = XMFLOAT4((float)normal(0), (float)normal(1), (float)normal(2), (float)normal(3)) ;
		}
		else
		{
			v.Normal = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f) ;
		}

		if(vectorTexture.size() < i)
		{
			auto texture = vectorTexture[i];
			v.Texture = XMFLOAT2((float)texture(0), (float)texture(1));
		}
		else
		{
			v.Texture = XMFLOAT2(0.0f, 0.0f) ;
		}

		this->vectorVertices.push_back(v);
	}
}

void AddBasicDrawableMessage::Proccess()
{
	std::shared_ptr<BasicDrawable> newObject =
		BasicDrawable::Spawn(this->ID,
							this->vectorVertices,
							this->vectorIndices,
							this->vertexFile,
							this->pixelFile,
							this->textureFileName);

	GraphicManager::GetInstance().Insert(newObject);
}