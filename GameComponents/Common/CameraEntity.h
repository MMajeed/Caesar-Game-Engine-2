#ifndef __CameraEntity__
#define __CameraEntity__

#include "Linker.h"

#include "Entity.h"
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

private:	std::hash_set<std::string> GlobalTexture2D;
public:		std::hash_set<std::string> GetGlobalTexture2D();
			void SetGlobalTexture2D(const std::hash_set<std::string>& v);
			void AddGlobalTexture2D(std::string ID);
			void DeleteGlobalTexture2D(std::string ID);
			void EmptyGlobalTexture2D();

private:	std::hash_set<std::string> GlobalTextureCube;
public:		std::hash_set<std::string> GetGlobalTextureCube();
			void SetGlobalTextureCube(const std::hash_set<std::string>& v);
			void AddGlobalTextureCube(std::string ID);
			void DeleteGlobalTextureCube(std::string ID);
			void EmptyGlobalTextureCube();

private:	std::hash_map<std::string, std::vector<char>> UserData;
public:		std::hash_map<std::string, std::vector<char>> GetUserData();
			void SetUserData(std::hash_map<std::string, std::vector<char>> v);
			bool FindUserData(const std::string& ID, std::vector<char>& v);
			void SetUserData(const std::string& ID, const std::vector<char>& data);
			void DeleteUserData(const std::string& ID);
			void EmptyUserData();

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
public:
	static std::shared_ptr<CameraEntity> Spawn();
	virtual std::shared_ptr<Entity> Clone();
};

#endif //__CameraEntity__