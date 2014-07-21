#ifndef __OBJECTINFO__
#define __OBJECTINFO__

#include "Linker.h"
#include "Entity.h"
#include <Vector.h>
#include <Matrix.h>
#include <vector>
#include <hash_set>
#include <hash_map>

class CommonDLL_API ObjectEntity : public Entity
{
protected:
	ObjectEntity();
	ObjectEntity(const ObjectEntity& c) = default;
	ObjectEntity& operator=(const ObjectEntity&) = delete;

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

private:	std::string DrawObjID;
public:		std::string GetDrawObjID();
			void SetDrawObjID(const std::string& v);

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

private:	std::hash_set<std::string> Texture2D;
public:		std::hash_set<std::string> GetTexture2D();
			void SetTexture2D(const std::hash_set<std::string>& v);
			void AddTexture2D(std::string ID);
			void DeleteTexture2D(std::string ID);
			void EmptyTexture2D();

private:	std::hash_set<std::string> TextureCube;
public:		std::hash_set<std::string> GetTextureCube();
			void SetTextureCube(const std::hash_set<std::string>& v);
			void AddTextureCube(const std::string& ID);
			void DeleteTextureCube(const std::string& ID);
			void EmptyTextureCube();

private:	std::hash_map<std::string, std::vector<char>> UserData;
public:		std::hash_map<std::string, std::vector<char>> GetUserData();
			void SetUserData(std::hash_map<std::string, std::vector<char>> v);
			bool FindUserData(const std::string& ID, std::vector<char>& v);
			void SetUserData(const std::string& ID, const std::vector<char>& data);
			void DeleteUserData(const std::string& ID);
			void EmptyUserData();
public:
	static std::shared_ptr<ObjectEntity> Spawn();
	virtual std::shared_ptr<Entity> Clone();
};

#endif //__OBJECTINFO__