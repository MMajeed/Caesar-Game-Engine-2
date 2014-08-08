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
protected:
	std::shared_ptr<ObjectEntity> obj;
public:
	GraphicObjectEntity();
	GraphicObjectEntity(std::weak_ptr<ObjectEntity> v);

	bool IsValidToDraw(const GraphicCameraEntity& camera) const;
	void Draw(const GraphicCameraEntity& camera) const;
	void SetupVertexShader(const GraphicCameraEntity& camera) const;
	void SetupGeometryShader(const GraphicCameraEntity& camera) const;
	void SetupPixelShader(const GraphicCameraEntity& camera) const;
	void SetupModel(const GraphicCameraEntity& camera) const;

	XMFLOAT4 GetLocation() const;
	XMFLOAT4 GetRotation() const;
	XMFLOAT4 GetScale() const;
	bool HasDepth() const;
	std::string GetVertexShaderID() const;
	std::shared_ptr<GraphicModel> GetGraphicModel() const;
	std::shared_ptr<VertexShader> GetVertexShader() const;
	std::shared_ptr<GeometryShader> GetGeometryShader() const;
	std::shared_ptr<PixelShader> GetPixelShader() const;
	std::hash_map<std::string, XMFLOAT4X4> GetAnimation() const;
	XMFLOAT4X4 GetJointAnimation() const;
	XMFLOAT4X4 GetRigidBody() const;
	std::hash_set<std::string> GetGroupList() const;
	std::shared_ptr<BasicTexture> FindTexture(std::string ID) const;
	std::hash_map<std::string, std::shared_ptr<Object>> GetUserData() const;
	std::shared_ptr<Object> FindUserData(std::string ID) const;
	D3D11_FILL_MODE GetFillMode() const;
	D3D11_CULL_MODE GetCullMode() const;

	XMFLOAT4X4 GetLRS() const;
	XMFLOAT4X4 GetWorldTransformation() const;
};



#endif //__GraphicObjectEntity__