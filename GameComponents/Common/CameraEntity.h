#ifndef __CameraEntity__
#define __CameraEntity__

#include "Linker.h"

#include "Entity.h"
#include <Object.h>
#include <Vector.h>
#include <set>
#include <unordered_set>
#include <unordered_map>

class CommonDLL_API CameraEntity : public Entity
{
protected:
	CameraEntity();
	CameraEntity(const CameraEntity& c) = default;
	CameraEntity& operator=(const CameraEntity&) = delete;

public:
private:	CML::Vec4 Eye;
public:		CML::Vec4 GetEye();
			void SetEye(const CML::Vec4& v);

private:	CML::Vec4 TargetMagnitude;
public:		CML::Vec4 GetTargetMagnitude();
			void SetTargetMagnitude(const CML::Vec4& v);

private:	CML::Vec4 Up;
public:		CML::Vec4 GetUp();
			void SetUp(const CML::Vec4& v);

private:	double Roll;
public:		double GetRoll();
			void SetRoll(double v);

private:	double Pitch;
public:		double GetPitch();
			void SetPitch(double v);

private:	double Yaw;
public:		double GetYaw();
			void SetYaw(double v);
			
private:	double FovAngleY;
public:		double GetFovAngleY();
			void SetFovAngleY(double v);

private:	double NearZ;
public:		double GetNearZ();
			void SetNearZ(double v);

private:	double FarZ;
public:		double GetFarZ();
			void SetFarZ(double v);
	
public:
	static std::shared_ptr<CameraEntity> Spawn();
	virtual std::shared_ptr<Entity> Clone();
};

#endif //__CameraEntity__