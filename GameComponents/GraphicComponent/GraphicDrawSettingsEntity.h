#ifndef __GraphicDrawSettingsEntity__
#define __GraphicDrawSettingsEntity__

#include "Linker.h"

#include "BasicTexture.h"
#include <DrawSettingsEntity.h>
#include <ObjectEntity.h>
#include <string>
#include <Windows.h>
#include <xnamath.h>

class GraphicObjectEntity;
class GraphicModel;
class VertexShader;
class GeometryShader;
class PixelShader;

class GraphicComponentDLL_API GraphicDrawSettingsEntity
{
public:
	GraphicDrawSettingsEntity();
	GraphicDrawSettingsEntity(std::shared_ptr<DrawSettingsEntity> v);

	void Update(std::shared_ptr<DrawSettingsEntity> v);
public:
		std::vector<std::shared_ptr<GraphicObjectEntity>>
		FilterInclusionList(std::unordered_map<std::string, std::shared_ptr<GraphicObjectEntity>> list) const;

private:	bool ClearScreen;
			void UpdateClearScreen(std::shared_ptr<DrawSettingsEntity> obj);
public:		bool GetClearScreen() const;

private:	std::array<float, 4> ClearColor;
			void UpdateClearColor(std::shared_ptr<DrawSettingsEntity> obj);
public:		std::array<float, 4> GetClearColor() const;

private:	DrawSettingsEntity::InclusionType InclusionState;
			void UpdateInclusionState(std::shared_ptr<DrawSettingsEntity> obj);
public:		DrawSettingsEntity::InclusionType GetInclusionState() const;

private:	std::set<std::string> InclusionList;
			void UpdateInclusionList(std::shared_ptr<DrawSettingsEntity> obj);
public:		std::set<std::string> GetInclusionList() const;

private:	std::unordered_map<std::string, std::shared_ptr<Object>> UserData;
			void UpdateUserData(std::shared_ptr<DrawSettingsEntity> obj);
public:		std::unordered_map<std::string, std::shared_ptr<Object>> GetUserData() const;
			std::shared_ptr<Object> findUserData(const std::string& ID) const;

private:	std::unordered_map<std::string, std::string> TextureList;
			void UpdateTextureList(std::shared_ptr<DrawSettingsEntity> obj);
public:		std::unordered_map<std::string, std::string> GetTextureList() const;
			std::unordered_map<std::string, std::shared_ptr<BasicTexture>> GetTexture() const;
			std::shared_ptr<BasicTexture> findTexture(const std::string& ID) const;

private:	std::string VertexShaderID;
			void UpdateVertexShaderID(std::shared_ptr<DrawSettingsEntity> obj);
public:		std::string GetVertexShaderID() const;
			std::shared_ptr<VertexShader> GetVertexShader() const;

private:	DrawSettingsEntity::DRAWSETTINGS_TYPE VertexShaderState;
			void UpdateVertexShaderState(std::shared_ptr<DrawSettingsEntity> obj);
public:		DrawSettingsEntity::DRAWSETTINGS_TYPE GetVertexShaderState() const;

private:	std::string PixelShaderID;
			void UpdatePixelShaderID(std::shared_ptr<DrawSettingsEntity> obj);
public:		std::string GetPixelShaderID() const;
			std::shared_ptr<PixelShader> GetPixelShader() const;

private:	DrawSettingsEntity::DRAWSETTINGS_TYPE PixelShaderState;
			void UpdatePixelShaderState(std::shared_ptr<DrawSettingsEntity> obj);
public:		DrawSettingsEntity::DRAWSETTINGS_TYPE GetPixelShaderState() const;
			
};


#endif //__GraphicDrawSettingsEntity__