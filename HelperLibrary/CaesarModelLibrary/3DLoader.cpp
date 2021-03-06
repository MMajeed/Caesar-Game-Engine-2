#include "3DLoader.h"
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Logger.h"
#include <MathFunctions.h>


namespace CHL
{
	void AssimpLoadModels(const aiScene* scene, std::vector<std::shared_ptr<CHL::Model>>& modelVec)
	{
		modelVec.reserve(scene->mNumMeshes);
		for(unsigned int iModel = 0; iModel < scene->mNumMeshes; ++iModel)
		{
			std::shared_ptr<CHL::Model> spCHLModel(new CHL::Model);
			aiMesh* aiSceneModel = scene->mMeshes[iModel];

			spCHLModel->name = aiSceneModel->mName.C_Str();
			spCHLModel->NumberOfFaces = aiSceneModel->mFaces[0].mNumIndices;
			spCHLModel->Faces.reserve(aiSceneModel->mNumFaces * spCHLModel->NumberOfFaces);
			for(std::size_t i = 0; i < aiSceneModel->mNumFaces; ++i)
			{
				for(std::size_t x = 0; x < spCHLModel->NumberOfFaces; ++x)
				{
					spCHLModel->Faces.push_back(aiSceneModel->mFaces[i].mIndices[x]);
				}
			}

			spCHLModel->Vertices.resize(aiSceneModel->mNumVertices);
			for(std::size_t i = 0; i < aiSceneModel->mNumVertices; ++i)
			{
				aiVector3D vec = aiSceneModel->mVertices[i];
				spCHLModel->Vertices[i] = {vec.x, vec.y, vec.z};
			}
			if(aiSceneModel->HasNormals())
			{
				spCHLModel->Normal.resize(aiSceneModel->mNumVertices);
				for(std::size_t i = 0; i < aiSceneModel->mNumVertices; ++i)
				{
					aiVector3D vec = aiSceneModel->mNormals[i];
					spCHLModel->Normal[i] = {vec.x, vec.y, vec.z};
				}
			}
			if(aiSceneModel->HasTangentsAndBitangents())
			{
				spCHLModel->Tangents.resize(aiSceneModel->mNumVertices);
				spCHLModel->Bitangents.resize(aiSceneModel->mNumVertices);
				for(std::size_t i = 0; i < aiSceneModel->mNumVertices; ++i)
				{
					aiVector3D vec1 = aiSceneModel->mTangents[i];
					spCHLModel->Tangents[i] = {vec1.x, vec1.y, vec1.z};
					aiVector3D vec2 = aiSceneModel->mBitangents[i];
					spCHLModel->Bitangents[i] = {vec2.x, vec2.y, vec2.z};
				}
			}
			if(aiSceneModel->HasVertexColors(0))
			{
				spCHLModel->Color.resize(aiSceneModel->mNumVertices);
				for(std::size_t i = 0; i < aiSceneModel->mNumVertices; ++i)
				{
					aiColor4D vec = aiSceneModel->mColors[0][i];
					spCHLModel->Color[i] = {vec.r, vec.g, vec.b, vec.a};
				}
			}
			if(aiSceneModel->HasTextureCoords(0))
			{
				spCHLModel->Texture.resize(aiSceneModel->mNumVertices);
				for(std::size_t i = 0; i < aiSceneModel->mNumVertices; ++i)
				{
					aiVector3D vec = aiSceneModel->mTextureCoords[0][i];
					spCHLModel->Texture[i] = CML::Vec3{vec.x, vec.y, vec.z};
				}
			}
			modelVec.push_back(spCHLModel);
		}
	}
	void AssimpLoadAnimation(const aiScene* scene, std::vector<std::shared_ptr<CHL::Animation>>& animVec)
	{
		animVec.reserve(scene->mNumAnimations);
		for(unsigned int iAnim = 0; iAnim < scene->mNumAnimations; ++iAnim)
		{
			std::shared_ptr<CHL::Animation> spCHLAnimation(new CHL::Animation);
			aiAnimation* aiImportedAnimation = scene->mAnimations[iAnim];
			
			double ticksPerSecond = aiImportedAnimation->mTicksPerSecond;

			spCHLAnimation->duration = aiImportedAnimation->mDuration / ticksPerSecond;
			spCHLAnimation->name = aiImportedAnimation->mName.C_Str();
			for(std::size_t iJoint = 0; iJoint < aiImportedAnimation->mNumChannels; ++iJoint)
			{
				aiNodeAnim* aiImportedJoint = aiImportedAnimation->mChannels[iJoint];
				Animation::Joint newJoint;
				
				newJoint.name = aiImportedJoint->mNodeName.C_Str();

				newJoint.Translation.reserve(aiImportedJoint->mNumPositionKeys);
				for(std::size_t iKey = 0; iKey < aiImportedJoint->mNumPositionKeys; ++iKey)
				{
					aiVectorKey& jointKey = aiImportedJoint->mPositionKeys[iKey];
					Animation::Joint::Key newKey;
					newKey.time = jointKey.mTime / ticksPerSecond;
					newKey.value = {jointKey.mValue.x, jointKey.mValue.y, jointKey.mValue.z};
					newJoint.Translation.push_back(newKey);
				}

				newJoint.Rotation.reserve(aiImportedJoint->mNumRotationKeys);
				for(std::size_t iKey = 0; iKey < aiImportedJoint->mNumRotationKeys; ++iKey)
				{
					aiQuatKey& jointKey = aiImportedJoint->mRotationKeys[iKey];
					Animation::Joint::QuaKey newKey;
					newKey.time = jointKey.mTime / ticksPerSecond;
					newKey.value = {jointKey.mValue.x, jointKey.mValue.y, jointKey.mValue.z, jointKey.mValue.w};
					newJoint.Rotation.push_back(newKey);
				}

				newJoint.Scale.reserve(aiImportedJoint->mNumScalingKeys);
				for(std::size_t iKey = 0; iKey < aiImportedJoint->mNumScalingKeys; ++iKey)
				{
					aiVectorKey& jointKey = aiImportedJoint->mScalingKeys[iKey];
					Animation::Joint::Key newKey;
					newKey.time = jointKey.mTime / ticksPerSecond;
					newKey.value = {jointKey.mValue.x, jointKey.mValue.y, jointKey.mValue.z};
					newJoint.Scale.push_back(newKey);
				}

 				spCHLAnimation->vecJoints[newJoint.name] = newJoint;
			}

			animVec.push_back(spCHLAnimation);
		}
	}
	void AssimpLoadNodes(const aiScene* scene, std::shared_ptr<CHL::Node>& rootNode)
	{
		struct AssimpLoadNodesRecursive
		{
			static void Run(const aiScene* scene, 
							std::shared_ptr<CHL::Node>& CHLNode,
							const aiNode* aiImportedNode)
			{
				CHLNode->Name = aiImportedNode->mName.C_Str();
				for(unsigned int i = 0; i < aiImportedNode->mNumMeshes; ++i)
				{
					CHLNode->meshes.push_back(aiImportedNode->mMeshes[0]);
				}
				const aiMatrix4x4& t = aiImportedNode->mTransformation;
				CHLNode->Transformation = {	{t.a1, t.b1, t.c1, t.d1}, 
											{t.a2, t.b2, t.c2, t.d2},
											{t.a3, t.b3, t.c3, t.d3},
											{t.a4, t.b4, t.c4, t.d4}, };
				for(unsigned int i = 0; i < aiImportedNode->mNumChildren; ++i)
				{
					std::shared_ptr<CHL::Node> CHLChildNode(new CHL::Node);
					const aiNode* aiImportedChildNode = aiImportedNode->mChildren[i];

					CHLChildNode->Parent = CHLNode;
					AssimpLoadNodesRecursive::Run(scene, CHLChildNode, aiImportedChildNode);
					CHLNode->Childern.push_back(CHLChildNode);
				}
			}
		};
		rootNode = std::shared_ptr<CHL::Node>(new CHL::Node);
		AssimpLoadNodesRecursive::Run(scene, rootNode, scene->mRootNode);
	}

	void Load3DFile(std::string fileName, 
					std::vector<std::shared_ptr<CHL::Model>>& modelVec, 
					std::vector<std::shared_ptr<CHL::Animation>>& animVec,
					std::shared_ptr<CHL::Node>& rootNode)
	{
		int i = 4 + 5;
		unsigned int pFlags = aiProcessPreset_TargetRealtime_MaxQuality  & (~aiProcess_SplitLargeMeshes);
		const aiScene* scene = aiImportFile(fileName.c_str(), pFlags);

		if(scene == 0){ Logger::LogError("ErrorException with loading model " + fileName + "\n" + aiGetErrorString()); }

		AssimpLoadModels(scene, modelVec);
		AssimpLoadAnimation(scene, animVec);
		AssimpLoadNodes(scene, rootNode);

		aiReleaseImport(scene);
	}
}