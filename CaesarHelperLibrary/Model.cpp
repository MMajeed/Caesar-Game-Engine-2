#include "Model.h"
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "VecMath.h"

namespace CHL
{

	Model::Model()
	{
		this->NumberOfFaces = 3;
	}

	void Model::NormalizeTheModel()
	{
		for(std::size_t i = 0; i < this->Faces.size(); i += this->NumberOfFaces)
		{
			unsigned int faceA = this->Faces[i + 0];
			unsigned int faceB = this->Faces[i + 1];
			unsigned int faceC = this->Faces[i + 2];

			CHL::Vec3 vecA{this->Vertices[faceA].Point(0), this->Vertices[faceA].Point(1), this->Vertices[faceA].Point(2)};
			CHL::Vec3 vecB{this->Vertices[faceB].Point(0), this->Vertices[faceB].Point(1), this->Vertices[faceB].Point(2)};
			CHL::Vec3 vecC{this->Vertices[faceC].Point(0), this->Vertices[faceC].Point(1), this->Vertices[faceC].Point(2)};

			CHL::Vec3 vecAB = vecB - vecA;
			CHL::Vec3 vecBC = vecC - vecB;

			CHL::Vec3 cross = CHL::CrossProduct(vecAB, vecBC);
			CHL::Vec3 normal = CHL::Normalize(cross);

			this->Vertices[faceA].Normal = this->Vertices[faceA].Normal + normal;
			this->Vertices[faceB].Normal = this->Vertices[faceA].Normal + normal;
			this->Vertices[faceC].Normal = this->Vertices[faceA].Normal + normal;
		}
		for(unsigned int i = 0; i < this->Vertices.size(); ++i)
		{
			this->Vertices[i].Normal = CHL::Normalize(this->Vertices[i].Normal);
		}
	}
	void Model::TexturizeTheModel()
	{
		for(std::size_t i = 0; i < this->Vertices.size(); ++i)
		{
			CHL::Vec4 tex = this->Vertices[i].Normal;

			this->Vertices[i].Texture = CHL::Normalize(tex);

			this->Vertices[i].Texture(0) = ((std::asin(tex(0)) / 3.14) + 0.5f) * 2.0f;
			this->Vertices[i].Texture(1) = ((std::asin(tex(1)) / 3.14) + 0.5f) * 2.0f;
			this->Vertices[i].Texture(2) = ((std::asin(tex(2)) / 3.14) + 0.5f) * 2.0f;
		}
	}

	std::vector<Model> LoadModels(std::string fileName)
	{
		const aiScene* scene = aiImportFile(fileName.c_str(), aiProcessPreset_TargetRealtime_MaxQuality | aiProcess_TransformUVCoords );

		if(scene == 0){	throw std::invalid_argument("Error with loading model " + fileName);	}

		std::vector<Model> models(scene->mNumMeshes);

		for(unsigned int iModel = 0; iModel < models.size(); ++iModel)
		{
			aiMesh* mesh = scene->mMeshes[iModel];

			models[iModel].NumberOfFaces = mesh->mFaces[0].mNumIndices;
			models[iModel].Faces.reserve(mesh->mNumFaces * models[iModel].NumberOfFaces);
			for(std::size_t i = 0; i < mesh->mNumFaces; ++i)
			{
				for(std::size_t x = 0; x < models[iModel].NumberOfFaces; ++x)
				{
					models[iModel].Faces.push_back(mesh->mFaces[i].mIndices[x]);
				}
			}

			models[iModel].Vertices.resize(mesh->mNumVertices);
			for(std::size_t i = 0; i < mesh->mNumVertices; ++i)
			{
				aiVector3D vec;

				vec = mesh->mVertices[i];
				models[iModel].Vertices[i].Point = CHL::Vec3{vec.x, vec.y, vec.z};

				if(mesh->HasNormals())
				{
					vec = mesh->mNormals[i];
					models[iModel].Vertices[i].Normal = CHL::Vec3{vec.x, vec.y, vec.z};
				}

				if(mesh->HasTextureCoords(0))
				{
					vec = mesh->mTextureCoords[0][i];
					models[iModel].Vertices[i].Texture = CHL::Vec3{vec.x, vec.y, vec.z};
				}
			}
		}
		return models;
	}
}