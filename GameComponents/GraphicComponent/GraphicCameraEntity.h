#ifndef __GraphicCameraEntity__
#define __GraphicCameraEntity__

#include "Linker.h"

#include "BasicTexture.h"
#include <CameraEntity.h>
#include <ObjectEntity.h>
#include <string>
#include <Windows.h>
#include <xnamath.h>

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

private:	unsigned int Width;
public:		void UpdateWidth(unsigned int v);
			unsigned int GetWidth() const;

private:	unsigned int Height;
public:		void UpdateHeight(unsigned int v);
			unsigned int GetHeight() const;

private:	XMFLOAT4X4 View;
public:		void UpdateView(std::shared_ptr<CameraEntity> obj);
			XMFLOAT4X4 GetView() const;

private:	XMFLOAT4X4 View2D;
public:		void UpdateView2D(std::shared_ptr<CameraEntity> obj);
			XMFLOAT4X4 GetView2D() const;

private:	XMFLOAT4X4 Perspective;
public:		void UpdatePerspective(std::shared_ptr<CameraEntity> obj);
			XMFLOAT4X4 GetPerspective() const;

private:	XMFLOAT4X4 Orthogonal;
public:		void UpdateOrthogonal(std::shared_ptr<CameraEntity> obj);
			XMFLOAT4X4 GetOrthogonal() const;
};


#endif //__GraphicCameraEntity__