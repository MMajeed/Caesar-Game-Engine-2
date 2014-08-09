#ifndef __OBJECTINFO__
#define __OBJECTINFO__

#include "Linker.h"
#include "Entity.h"
#include <Vector.h>
#include <Matrix.h>
#include <vector>
#include <hash_set>
#include <hash_map>
#include <Object.h>

class CommonDLL_API ObjectEntity : public Entity
{
protected:
	ObjectEntity();
	ObjectEntity(const ObjectEntity& c) = default;
	ObjectEntity& operator=(const ObjectEntity&) = delete;

private:	unsigned int Tracker;
			void PrivateUpdateTracker(); // Call this from within the class
public:		unsigned int GetTracker();
			void UpdateTracker(); // Call this from outside the class

private:	CML::Vec4 Location;
public:		CML::Vec4 GetLocation();
			void SetLocation(const CML::Vec4& v);

private:	CML::Vec4 Rotation;
public:		CML::Vec4 GetRotation();
			void SetRotation(const CML::Vec4& v);

private:	CML::Vec4 Scale;
public:		CML::Vec4 GetScale();
			void SetScale(const CML::Vec4& v);

private:	bool Depth;
public:		bool GetDepth();
			void SetDepth(bool v);

private:	std::string GraphicModelID;
public:		std::string GetGraphicModelID();
			void SetGraphicModelID(const std::string& v);

private:	std::string VertexShaderID;
public:		std::string GetVertexShaderID();
			void SetVertexShaderID(const std::string& v);

private:	std::string GeometryShaderID;
public:		std::string GetGeometryShaderID();
			void SetGeometryShaderID(const std::string& v);

private:	std::string PixelShaderID;
public:		std::string GetPixelShaderID();
			void SetPixelShaderID(const std::string& v);

private:	std::string AnimationID;
public:		std::string GetAnimationID();
			void SetAnimationID(const std::string& v);

private:	std::string JointName;
public:		std::string GetJointName();
			void SetJointName(const std::string& v);

private:	std::string RigidBodyID;
public:		std::string GetRigidBodyID();
			void SetRigidBodyID(const std::string& v);

private:	std::hash_set<std::string> GroupList;
public:		std::hash_set<std::string> GetGroupList();
			void SetGroupList(const std::hash_set<std::string>& v);
			void AddGroupList(std::string ID);
			void DeleteGroupList(std::string ID);
			void EmptyGroupList();

private:	std::hash_map<std::string, std::string> Texture;
public:		std::hash_map<std::string, std::string> GetTexture();
			void SetTexture(std::hash_map<std::string, std::string> v);
			bool FindTexture(const std::string& ID, std::string& returnTextureID);
			void SetTexture(const std::string& ID, const std::string& v);
			void DeleteTexture(const std::string& ID);
			void EmptyTexture();

private:	std::hash_map<std::string, std::shared_ptr<Object>> UserData;
public:		std::hash_map<std::string, std::shared_ptr<Object>> GetUserData();
			void SetUserData(std::hash_map<std::string, std::shared_ptr<Object>> v);
			std::shared_ptr<Object> FindUserData(const std::string& ID);
			void SetUserData(const std::string& ID, const std::shared_ptr<Object>& data);
			void DeleteUserData(const std::string& ID);
			void EmptyUserData();

public:		enum class FILL_MODE { FILL_WIREFRAME = 2, FILL_SOLID = 3 };
private:	FILL_MODE FillMode;
public:		FILL_MODE GetFillMode();
			void SetFillMode(const FILL_MODE& v);

public:		enum class CULL_MODE { CULL_NONE = 1, CULL_FRONT = 2, CULL_BACK = 3 };
private:	CULL_MODE CullMode;
public:		CULL_MODE GetCullMode();
			void SetCullMode(const CULL_MODE& v);

public:
	static std::shared_ptr<ObjectEntity> Spawn();
	virtual std::shared_ptr<Entity> Clone();
};

#endif //__OBJECTINFO__