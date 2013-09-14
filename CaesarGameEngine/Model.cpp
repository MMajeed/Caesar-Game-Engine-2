#include "Model.h"

Model::Model(std::string file)
{
	this->scene = aiImportFile(file.c_str(), aiProcessPreset_TargetRealtime_MaxQuality);
}

std::vector<boost::numeric::ublas::vector<double>> Model::Pos() const
{
	std::vector<boost::numeric::ublas::vector<double>> vectorPos;

	aiMesh* mesh = *(this->scene->mMeshes);

	vectorPos.reserve(mesh->mNumVertices);

	for(std::size_t i = 0; i <  mesh->mNumVertices; ++i)
	{
		boost::numeric::ublas::vector<double> pos(4);

		pos(0) = mesh->mVertices[i].x;
		pos(1) = mesh->mVertices[i].y;
		pos(2) = mesh->mVertices[i].z;
		pos(3) = 1.0;

		vectorPos.push_back(pos);
	}

	return vectorPos;
}
std::vector<boost::numeric::ublas::vector<double>> Model::Normal() const
{
	std::vector<boost::numeric::ublas::vector<double>> vectorNormal;

	aiMesh* mesh = *(this->scene->mMeshes);

	vectorNormal.reserve(mesh->mNumVertices);

	for(std::size_t i = 0; i <  mesh->mNumVertices; ++i)
	{
		boost::numeric::ublas::vector<double> normal(4);

		normal(0) = mesh->mNormals[i].x;
		normal(1) = mesh->mNormals[i].y;
		normal(2) = mesh->mNormals[i].z;
		normal(3) = 1.0;

		vectorNormal.push_back(normal);
	}

	return vectorNormal;
}
std::vector<boost::numeric::ublas::vector<double>> Model::Texture() const
{
	std::vector<boost::numeric::ublas::vector<double>> vectorTexture;

	aiMesh* mesh = *(this->scene->mMeshes);

	vectorTexture.reserve(mesh->mNumVertices);

	for(std::size_t i = 0; i <  mesh->mNumVertices; ++i)
	{
		boost::numeric::ublas::vector<double> texture(2);
		if(mesh->mTextureCoords[i] != 0)
		{

			texture(0) = mesh->mTextureCoords[i]->x;
			texture(1) = mesh->mTextureCoords[i]->y;

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