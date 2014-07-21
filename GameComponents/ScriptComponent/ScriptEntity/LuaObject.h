#ifndef __LuaObject__
#define __LuaObject__

#include "Linker.h"

#include <Lua.hpp>
#include <luabind\luabind.hpp>
#include <LuaMath.h>
#include <ObjectEntity.h>
#include <GenericLuaObject.h>

class ScriptEntityDLL_API LuaObject
{
protected:
	std::weak_ptr<ObjectEntity> wp_Obj;
public:
	LuaObject();
	LuaObject(const luabind::object& table);

	LuaMath::Vector4 GetLocation();
	void SetLocation(const LuaMath::Vector4& v);

	LuaMath::Vector4 GetRotation();
	void SetRotation(const LuaMath::Vector4& v);

	LuaMath::Vector4 GetScale();
	void SetScale(const LuaMath::Vector4& v);

	bool GetDepth();
	void SetDepth(bool v);

	GenericLuaObject GetDrawObjID();
	void SetDrawObjID(const GenericLuaObject& v);
	void RemoveDrawObjID();

	GenericLuaObject GetAnimationID();
	void SetAnimationID(const GenericLuaObject& v);
	void RemoveAnimationID();

	GenericLuaObject GetJointName();
	void SetJointName(const GenericLuaObject& v);
	void RemoveJointName();

	GenericLuaObject GetRigidBodyID();
	void SetRigidBodyID(const GenericLuaObject& v);
	void RemoveRigidBodyID();

	luabind::object GetGroupList();
	void SetGroupList(const luabind::object& v);
	void AddGroupList(const GenericLuaObject& v);
	void DeleteGroupList(const GenericLuaObject& v);
	void EmptyGroupList();

	luabind::object GetTexture2D();
	void SetTexture2D(const luabind::object& v);
	void AddTexture2D(const GenericLuaObject& v);
	void DeleteTexture2D(const GenericLuaObject& v);
	void EmptyTexture2D();

	luabind::object GetTextureCube();
	void SetTextureCube(const luabind::object& v);
	void AddTextureCube(const GenericLuaObject& v);
	void DeleteTextureCube(const GenericLuaObject& v);
	void EmptyTextureCube();

	/*luabind::object GetUserData();
	void SetUserData(const luabind::object& v)
	bool FindUserData(const std::string& ID, std::vector<char>& v);
	void SetUserData(const std::string& ID, const std::vector<char>& data);
	void DeleteUserData(const std::string& ID);
	void EmptyUserData();*/

	void Release();

	static void Register(lua_State *lua);
	static inline void RegisterAllLuaFunction(lua_State *lua)
	{
		LuaObject::Register(lua);
	}
};

#endif //__LuaObject__