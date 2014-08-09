#ifndef __LuaObject__
#define __LuaObject__

#include "Linker.h"

#include <Lua.hpp>
#include <luabind\luabind.hpp>
#include <LuaMath.h>
#include <ObjectEntity.h>
#include <GenericLuaObject.h>

class ScriptEntityDLL_API LuaObject : public GenericLuaObject
{
protected:
	std::weak_ptr<ObjectEntity> wp_Obj;
public:
	LuaObject();
	LuaObject(const luabind::object& table);

	LuaMath::Vector4 GetLocation();
	void SetLocation(const luabind::object& v);

	LuaMath::Vector4 GetRotation();
	void SetRotation(const luabind::object& v);

	LuaMath::Vector4 GetScale();
	void SetScale(const luabind::object& v);

	bool GetDepth();
	void SetDepth(const luabind::object& v);
	
	double GetPriority();
	void SetPriority(const luabind::object& v);

	void GetGraphicModelID();
	void SetGraphicModelID(const luabind::object& v);
	void RemoveGraphicModelID();

	void GetVertexShaderID();
	void SetVertexShaderID(const luabind::object& v);
	void RemoveVertexShaderID();

	void GetGeometryShaderID();
	void SetGeometryShaderID(const luabind::object& v);
	void RemoveGeometryShaderID();

	void GetPixelShaderID();
	void SetPixelShaderID(const luabind::object& v);
	void RemovePixelShaderID();

	void GetAnimationID();
	void SetAnimationID(const luabind::object& v);
	void RemoveAnimationID();

	std::string GetJointName();
	void SetJointName(const luabind::object& v);
	void RemoveJointName();

	void GetRigidBodyID();
	void SetRigidBodyID(const luabind::object& v);
	void RemoveRigidBodyID();
	
	luabind::object GetGroupList();
	void SetGroupList(const luabind::object& v);
	void AddGroupList(const luabind::object& v);
	void DeleteGroupList(const luabind::object& v);
	void EmptyGroupList();

	luabind::object GetAllTexture();
	void SetAllTexture(const luabind::object& v);
	luabind::object FindTexture(const std::string& ID);
	void SetTexture(const std::string& ID, const luabind::object& v);
	void DeleteTexture(const std::string& ID);
	void EmptyTexture();

	luabind::object GetAllUserData();
	void SetAllUserData(const luabind::object& v);
	luabind::object FindUserData(const std::string& ID);
	void SetUserData(const std::string& ID, const luabind::object& data);
	void DeleteUserData(const std::string& ID);
	void EmptyUserData(); 
	
	int GetFillMode();
	void SetFillMode(const luabind::object& v);

	int GetCullMode();
	void SetCullMode(const luabind::object& v);

	void Release();

	static void Register(lua_State *lua);
	static inline void RegisterAllLuaFunction(lua_State *lua)
	{
		LuaObject::Register(lua);
	}
};

#endif //__LuaObject__