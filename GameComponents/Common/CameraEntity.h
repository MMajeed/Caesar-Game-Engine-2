#ifndef __CameraEntity__
#define __CameraEntity__

#include "Linker.h"

#include "Entity.h"
#include <Object.h>
#include <Vector.h>
#include <hash_set>
#include <hash_map>

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

private:	CML::Vec4 ClearColor;
public:		CML::Vec4 GetClearColor();
			void SetClearColor(const CML::Vec4& v);

public:		enum class InclusionType { Exclude = 0, Include = 1 };
private:	InclusionType InclusionState;
public:		InclusionType GetInclusionState();
			void SetInclusionState(InclusionType v);

private:	std::hash_set<std::string> InclusionList;
public:		std::hash_set<std::string> GetInclusionList();
			void SetInclusionList(const std::hash_set<std::string>& v);
			void AddInclusionList(std::string ID);
			void DeleteInclusionList(std::string ID);
			void EmptyInclusionList(); 

private:	std::hash_map<std::string, std::shared_ptr<Object>> UserData;
public:		std::hash_map<std::string, std::shared_ptr<Object>> GetUserData();
			void SetUserData(std::hash_map<std::string, std::shared_ptr<Object>> v);
			std::shared_ptr<Object> FindUserData(const std::string& ID);
			void SetUserData(const std::string& ID, const std::shared_ptr<Object>& data);
			void DeleteUserData(const std::string& ID);
			void EmptyUserData();

private:	std::hash_map<std::string, std::string> Texture;
public:		std::hash_map<std::string, std::string> GetTexture();
			void SetTexture(std::hash_map<std::string, std::string> v);
			bool FindTexture(const std::string& ID, std::string& returnTextureID);
			void SetTexture(const std::string& ID, const std::string& v);
			void DeleteTexture(const std::string& ID);
			void EmptyTexture();

public:		enum class CAMERA_SHADER_TYPE { DEFAULT = 0, FORCE = 1 };

private:	std::string VertexShaderID;
public:		std::string GetVertexShaderID();
			void SetVertexShaderID(const std::string& v);

private:	CameraEntity::CAMERA_SHADER_TYPE VertexShaderState;
public:		CameraEntity::CAMERA_SHADER_TYPE GetVertexShaderState();
			void SetVertexShaderState(const CameraEntity::CAMERA_SHADER_TYPE& v);
			
private:	std::string PixelShaderID;
public:		std::string GetPixelShaderID();
			void SetPixelShaderID(const std::string& v);

private:	CameraEntity::CAMERA_SHADER_TYPE PixelShaderState;
public:		CameraEntity::CAMERA_SHADER_TYPE GetPixelShaderState();
			void SetPixelShaderState(const CameraEntity::CAMERA_SHADER_TYPE& v);


public:
	static std::shared_ptr<CameraEntity> Spawn();
	virtual std::shared_ptr<Entity> Clone();
};

#endif //__CameraEntity__