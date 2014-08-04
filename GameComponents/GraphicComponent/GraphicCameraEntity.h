#ifndef __GraphicCameraEntity__
#define __GraphicCameraEntity__

#include "Linker.h"

#include "BasicTexture.h"
#include <CameraEntity.h>
#include <Windows.h>
#include <xnamath.h>
#include <ObjectEntity.h>

class GraphicObjectEntity;

class GraphicComponentDLL_API GraphicCameraEntity
{
protected:
	std::weak_ptr<CameraEntity> wp_Obj;
public:
	GraphicCameraEntity();
	GraphicCameraEntity(std::weak_ptr<CameraEntity> v);

	XMFLOAT4 GetEye() const;
	XMFLOAT4 GetTargetMagnitude() const;
	XMFLOAT4 GetUp() const;
	float GetRoll() const;
	float GetPitch() const;
	float GetYaw() const;
	float GetFovAngleY() const;
	float GetNearZ() const;
	float GetFarZ() const;
	std::array<float, 4> GetClearColor() const;
	std::hash_set<std::shared_ptr<BasicTexture>> GetGlobalTexture2D() const;
	std::hash_set<std::shared_ptr<BasicTexture>> GetGlobalTextureCube() const;
	std::hash_map<std::string, std::vector<char>> GetUserData() const;
	CameraEntity::InclusionType GetInclusionState() const;
	std::vector<GraphicObjectEntity> FilterInclusionList(std::hash_map<std::string, GraphicObjectEntity> list) const;
protected:
	XMFLOAT4X4 view;
	XMFLOAT4X4 perspective;
	XMFLOAT4X4 orthogonal;
public:
	void UpdateView();
	void UpdatePerspective();
	void UpdateOrthogonal();
	XMFLOAT4X4 GetView() const;
	XMFLOAT4X4 GetPerspective() const;
	XMFLOAT4X4 GetOrthogonal() const;
};


#endif //__GraphicCameraEntity__