#ifndef __GraphicCameraEntity__
#define __GraphicCameraEntity__

#include "Linker.h"

#include "BasicTexture.h"
#include <CameraEntity.h>
#include <Windows.h>
#include <xnamath.h>
#include <ObjectEntity.h>

class GraphicObjectEntity;
class GraphicModel;
class VertexShader;
class GeometryShader;
class PixelShader;

class GraphicComponentDLL_API GraphicCameraEntity
{
public:
	GraphicCameraEntity();
	GraphicCameraEntity(std::shared_ptr<CameraEntity> v, unsigned int width, unsigned int height);

	void Update(std::shared_ptr<CameraEntity> v, unsigned int width, unsigned int height);
public:
	std::vector<std::shared_ptr<GraphicObjectEntity>> 
		FilterInclusionList(std::hash_map<std::string, std::shared_ptr<GraphicObjectEntity>> list) const;

private:	XMFLOAT4 Eye;
			void UpdateEye(std::shared_ptr<CameraEntity> obj);
public:		XMFLOAT4 GetEye() const;

private:	XMFLOAT4 TargetMagnitude;
			void UpdateTargetMagnitude(std::shared_ptr<CameraEntity> obj);
public:		XMFLOAT4 GetTargetMagnitude() const;

private:	XMFLOAT4 Up;
			void UpdateUp(std::shared_ptr<CameraEntity> obj);
public:		XMFLOAT4 GetUp() const;

private:	float Roll;
			void UpdateRoll(std::shared_ptr<CameraEntity> obj);
public:		float GetRoll() const;

private:	float Pitch;
			void UpdatePitch(std::shared_ptr<CameraEntity> obj);
public:		float GetPitch() const;

private:	float Yaw;
			void UpdateYaw(std::shared_ptr<CameraEntity> obj);
public:		float GetYaw() const;

private:	float FovAngleY;
			void UpdateFovAngleY(std::shared_ptr<CameraEntity> obj);
public:		float GetFovAngleY() const;

private:	float NearZ;
			void UpdateNearZ(std::shared_ptr<CameraEntity> obj);
public:		float GetNearZ() const;

private:	float FarZ;
			void UpdateFarZ(std::shared_ptr<CameraEntity> obj);
public:		float GetFarZ() const;

private:	std::array<float, 4> ClearColor;
			void UpdateClearColor(std::shared_ptr<CameraEntity> obj);
public:		std::array<float, 4> GetClearColor() const;

private:	CameraEntity::InclusionType InclusionState;
			void UpdateInclusionState(std::shared_ptr<CameraEntity> obj);
public:		CameraEntity::InclusionType GetInclusionState() const;

private:	std::hash_set<std::string> InclusionList;
			void UpdateInclusionList(std::shared_ptr<CameraEntity> obj);
public:		std::hash_set<std::string> GetInclusionList() const; 

private:	std::hash_map<std::string, std::shared_ptr<Object>> UserData;
			void UpdateUserData(std::shared_ptr<CameraEntity> obj);
public:		std::hash_map<std::string, std::shared_ptr<Object>> GetUserData() const;
			std::shared_ptr<Object> FindUserData(const std::string& ID) const;

private:	std::hash_map<std::string, std::string> TextureList;
			void UpdateTextureList(std::shared_ptr<CameraEntity> obj);
public:		std::hash_map<std::string, std::string> GetTextureList() const;
			std::hash_map<std::string, std::shared_ptr<BasicTexture>> GetTexture() const;
			std::shared_ptr<BasicTexture> FindTexture(const std::string& ID) const;

private:	std::string VertexShaderID;
			void UpdateVertexShaderID(std::shared_ptr<CameraEntity> obj);
public:		std::string GetVertexShaderID() const;
			std::shared_ptr<VertexShader> GetVertexShader() const;

private:	CameraEntity::CAMERA_SHADER_TYPE VertexShaderState;
			void UpdateVertexShaderState(std::shared_ptr<CameraEntity> obj);
public:		CameraEntity::CAMERA_SHADER_TYPE GetVertexShaderState() const;

private:	std::string PixelShaderID;
			void UpdatePixelShaderID(std::shared_ptr<CameraEntity> obj);
public:		std::string GetPixelShaderID() const;
			std::shared_ptr<PixelShader> GetPixelShader() const;

private:	CameraEntity::CAMERA_SHADER_TYPE PixelShaderState;
			void UpdatePixelShaderState(std::shared_ptr<CameraEntity> obj);
public:		CameraEntity::CAMERA_SHADER_TYPE GetPixelShaderState() const;

private:	unsigned int Width;
			void UpdateWidth(unsigned int v);
public:		unsigned int GetWidth() const;

private:	unsigned int Height;
			void UpdateHeight(unsigned int v);
public:		unsigned int GetHeight() const;

private:	XMFLOAT4X4 View;
			void UpdateView(std::shared_ptr<CameraEntity> obj);
public:		XMFLOAT4X4 GetView() const;

private:	XMFLOAT4X4 View2D;
			void UpdateView2D(std::shared_ptr<CameraEntity> obj);
public:		XMFLOAT4X4 GetView2D() const;

private:	XMFLOAT4X4 Perspective;
			void UpdatePerspective(std::shared_ptr<CameraEntity> obj);
public:		XMFLOAT4X4 GetPerspective() const;

private:	XMFLOAT4X4 Orthogonal;
			void UpdateOrthogonal(std::shared_ptr<CameraEntity> obj);
public:		XMFLOAT4X4 GetOrthogonal() const;
};


#endif //__GraphicCameraEntity__