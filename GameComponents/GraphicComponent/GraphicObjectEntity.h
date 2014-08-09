#ifndef __GraphicObjectEntity__
#define __GraphicObjectEntity__

#include "Linker.h"

#include "BasicTexture.h"
#include <ObjectEntity.h>
#include <Windows.h>
#include <xnamath.h>

class GraphicCameraEntity;
class GraphicModel;
class VertexShader;
class GeometryShader;
class PixelShader;

class GraphicComponentDLL_API GraphicObjectEntity
{
public:		
	GraphicObjectEntity();
	GraphicObjectEntity(std::shared_ptr<ObjectEntity> v);

	void Draw(const GraphicCameraEntity& camera) const;

public:		void Update(std::shared_ptr<ObjectEntity> v);

private:	unsigned int Tracker;
			void UpdateTracker(std::shared_ptr<ObjectEntity> obj);
public:		unsigned int GetTracker() const;

private:	XMFLOAT4 Location;
			void UpdateLocation(std::shared_ptr<ObjectEntity> obj);
public:		XMFLOAT4 GetLocation() const;

private:	XMFLOAT4 Rotation;
			void UpdateRotation(std::shared_ptr<ObjectEntity> obj);
public:		XMFLOAT4 GetRotation() const;

private:	XMFLOAT4 Scale;
			void UpdateScale(std::shared_ptr<ObjectEntity> obj);
public:		XMFLOAT4 GetScale() const;

private:	bool Depth;
			void UpdateDepth(std::shared_ptr<ObjectEntity> obj);
public:		bool GetDepth() const;

private:	float Priority;
			void UpdatePriority(std::shared_ptr<ObjectEntity> obj);
public:		float GetPriority() const;

private:	std::string GraphicModelID;
			void UpdateGraphicModelID(std::shared_ptr<ObjectEntity> obj);
public:		std::string GetGraphicModelID() const;
			std::shared_ptr<GraphicModel> GetGraphicModel() const;

private:	std::string VertexShaderID;
			void UpdateVertexShaderID(std::shared_ptr<ObjectEntity> obj);
public:		std::string GetVertexShaderID() const;
			std::shared_ptr<VertexShader> GetVertexShader() const;

private:	std::string GeometryShaderID;
			void UpdateGeometryShaderID(std::shared_ptr<ObjectEntity> obj);
public:		std::string GetGeometryShaderID() const;
			std::shared_ptr<GeometryShader> GetGeometryShader() const;

private:	std::string PixelShaderID;
			void UpdatePixelShaderID(std::shared_ptr<ObjectEntity> obj);
public:		std::string GetPixelShaderID() const;
			std::shared_ptr<PixelShader> GetPixelShader() const;

private:	std::string AnimationID;
			void UpdateAnimationID(std::shared_ptr<ObjectEntity> obj);
public:		std::string GetAnimationID() const;
			std::hash_map<std::string, XMFLOAT4X4> GetAnimation() const;

private:	std::string AnimationJointName;
			void UpdateAnimationJointName(std::shared_ptr<ObjectEntity> obj);
public:		std::string GetAnimationJointName() const;
			XMFLOAT4X4 GetAnimationJoint() const;

private:	std::string RigidBodyID;
			void UpdateRigidBodyID(std::shared_ptr<ObjectEntity> obj);
public:		std::string GetRigidBodyID() const;
			XMFLOAT4X4 GetRigidBody() const;

private:	std::hash_set<std::string> GroupList;
			void UpdateGroupList(std::shared_ptr<ObjectEntity> obj);
public:		std::hash_set<std::string> GetGroupList() const;

private:	std::hash_map<std::string, std::string> TextureList;
			void UpdateTextureList(std::shared_ptr<ObjectEntity> obj);
public:		std::hash_map<std::string, std::string> GetTextureList() const;
			std::hash_map<std::string, std::shared_ptr<BasicTexture>> GetTexture() const;
			std::shared_ptr<BasicTexture> FindTexture(const std::string& ID) const;

private:	std::hash_map<std::string, std::shared_ptr<Object>> UserData;
			void UpdateUserData(std::shared_ptr<ObjectEntity> obj);
public:		std::hash_map<std::string, std::shared_ptr<Object>> GetUserData() const;
			std::shared_ptr<Object> FindUserData(const std::string& ID) const;

private:	D3D11_FILL_MODE FillMode;
			void UpdateFillMode(std::shared_ptr<ObjectEntity> obj);
public:		D3D11_FILL_MODE GetFillMode() const;

private:	D3D11_CULL_MODE CullMode;
			void UpdateCullMode(std::shared_ptr<ObjectEntity> obj);
public:		D3D11_CULL_MODE GetCullMode() const;

private:	XMFLOAT4X4 LRS; // Location, Rotation, Scale
			void UpdateLRS(std::shared_ptr<ObjectEntity> obj);
public:		XMFLOAT4X4 GetLRS() const;

public:		XMFLOAT4X4 GetWorld() const;// Animation, LRS, RigidBody, st;
};



#endif //__GraphicObjectEntity__