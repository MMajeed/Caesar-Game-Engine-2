#include "Model.h"

// assimp include files. These three are usually needed.
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


Model::Model(std::string file)
{
	this->scene = aiImportFile(file.c_str(), aiProcessPreset_TargetRealtime_MaxQuality | aiProcess_TransformUVCoords);
}

std::vector<CHL::Vec4> Model::Pos() const
{
	std::vector<CHL::Vec4> vectorPos;

	aiMesh* mesh = *(this->scene->mMeshes);

	vectorPos.reserve(mesh->mNumVertices);

	for(std::size_t i = 0; i <  mesh->mNumVertices; ++i)
	{
		CHL::Vec4 pos;

		pos(0) = mesh->mVertices[i].x;
		pos(1) = mesh->mVertices[i].y;
		pos(2) = mesh->mVertices[i].z;
		pos(3) = 1.0;

		vectorPos.push_back(pos);
	}

	return vectorPos;
}
std::vector<CHL::Vec4> Model::Normal() const
{
	std::vector<CHL::Vec4> vectorNormal;

	aiMesh* mesh = *(this->scene->mMeshes);

	vectorNormal.reserve(mesh->mNumVertices);

	for(std::size_t i = 0; i <  mesh->mNumVertices; ++i)
	{
		CHL::Vec4 normal;

		if(mesh->HasNormals())
		{
			normal(0) = mesh->mNormals[i].x;
			normal(1) = mesh->mNormals[i].y;
			normal(2) = mesh->mNormals[i].z;
			normal(3) = 1.0;
		}
		else
		{
			normal(0) = 0.0;
			normal(1) = 0.0;
			normal(2) = 0.0;
			normal(3) = 1.0;
		}

		vectorNormal.push_back(normal);
	}

	return vectorNormal;
}
std::vector<CHL::Vec2> Model::Texture() const
{
	std::vector<CHL::Vec2> vectorTexture;

	aiMesh* mesh = *(this->scene->mMeshes);

	vectorTexture.reserve(mesh->mNumVertices);

	for(std::size_t i = 0; i <  mesh->mNumVertices; ++i)
	{
		CHL::Vec2 texture;
		if(mesh->HasTextureCoords(0))
		{
			texture(0) = mesh->mTextureCoords[0][i].x;
			texture(1) = mesh->mTextureCoords[0][i].y;
		}
		else
		{
			texture(0) = 0.0;
			texture(1) = 0.0;
		}
		vectorTexture.push_back(texture);
	}

	return vectorTexture;
}

std::vector<unsigned int> Model::Faces() const
{
	std::vector<unsigned int> vectorFaces;

	aiMesh* mesh = *(this->scene->mMeshes);

	for(std::size_t i = 0; i <  mesh->mNumFaces; ++i)
	{
		for(std::size_t x = 0; x < mesh->mFaces[i].mNumIndices; ++x)
		{
			vectorFaces.push_back(mesh->mFaces[i].mIndices[x]);
		}
	}

	return vectorFaces;
}