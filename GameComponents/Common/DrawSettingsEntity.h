#ifndef __DrawSettingsEntity__
#define __DrawSettingsEntity__

#include "Linker.h"

#include "Entity.h"
#include <Object.h>
#include <Vector.h>
#include <set>
#include <unordered_set>
#include <unordered_map>

class CommonDLL_API DrawSettingsEntity : public Entity
{
protected:
	DrawSettingsEntity();
	DrawSettingsEntity(const DrawSettingsEntity& c) = default;
	DrawSettingsEntity& operator=(const DrawSettingsEntity&) = delete;

private:	bool ClearScreen;
public:		bool GetClearScreen();
			void SetClearScreen(const bool& v);

private:	CML::Vec4 ClearColor;
public:		CML::Vec4 GetClearColor();
			void SetClearColor(const CML::Vec4& v);

public:		enum class InclusionType { Exclude = 0, Include = 1 };
private:	InclusionType InclusionState;
public:		InclusionType GetInclusionState();
			void SetInclusionState(InclusionType v);

private:	std::set<std::string> InclusionList;
public:		std::set<std::string> GetInclusionList();
			void SetInclusionList(const std::set<std::string>& v);
			void AddInclusionList(std::string ID);
			void DeleteInclusionList(std::string ID);
			void EmptyInclusionList();

private:	std::unordered_map<std::string, std::shared_ptr<Object>> UserData;
public:		std::unordered_map<std::string, std::shared_ptr<Object>> GetUserData();
			void SetUserData(std::unordered_map<std::string, std::shared_ptr<Object>> v);
			std::shared_ptr<Object> FindUserData(const std::string& ID);
			void SetUserData(const std::string& ID, const std::shared_ptr<Object>& data);
			void DeleteUserData(const std::string& ID);
			void EmptyUserData();

private:	std::unordered_map<std::string, std::string> Texture;
public:		std::unordered_map<std::string, std::string> GetTexture();
			void SetTexture(std::unordered_map<std::string, std::string> v);
			bool FindTexture(const std::string& ID, std::string& returnTextureID);
			void SetTexture(const std::string& ID, const std::string& v);
			void DeleteTexture(const std::string& ID);
			void EmptyTexture();

public:		enum class DRAWSETTINGS_TYPE { DEFAULT = 0, FORCE = 1 };

private:	std::string VertexShaderID;
public:		std::string GetVertexShaderID();
			void SetVertexShaderID(const std::string& v);

private:	DrawSettingsEntity::DRAWSETTINGS_TYPE VertexShaderState;
public:		DrawSettingsEntity::DRAWSETTINGS_TYPE GetVertexShaderState();
			void SetVertexShaderState(const DrawSettingsEntity::DRAWSETTINGS_TYPE& v);

private:	std::string PixelShaderID;
public:		std::string GetPixelShaderID();
			void SetPixelShaderID(const std::string& v);

private:	DrawSettingsEntity::DRAWSETTINGS_TYPE PixelShaderState;
public:		DrawSettingsEntity::DRAWSETTINGS_TYPE GetPixelShaderState();
			void SetPixelShaderState(const DrawSettingsEntity::DRAWSETTINGS_TYPE& v);


public:
	static std::shared_ptr<DrawSettingsEntity> Spawn();
	virtual std::shared_ptr<Entity> Clone();
};

#endif //__DrawSettingsEntity__