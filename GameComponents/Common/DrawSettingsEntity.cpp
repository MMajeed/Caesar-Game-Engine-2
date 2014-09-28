#include "DrawSettingsEntity.h"

DrawSettingsEntity::DrawSettingsEntity()
{
	this->ClearScreen = true;
	this->ClearColor = {0.5, 0.5, 0.5, 1.0};
	this->VertexShaderState = DrawSettingsEntity::DRAWSETTINGS_TYPE::DEFAULT;
	this->PixelShaderState = DrawSettingsEntity::DRAWSETTINGS_TYPE::DEFAULT;
}

bool DrawSettingsEntity::GetClearScreen()
{
	std::lock_guard<std::mutex> lock(this->metux);
	return this->ClearScreen;
}
void DrawSettingsEntity::SetClearScreen(const bool& v)
{
	std::lock_guard<std::mutex> lock(this->metux);
	this->ClearScreen = v;
}

CML::Vec4 DrawSettingsEntity::GetClearColor()
{
	std::lock_guard<std::mutex> lock(this->metux);
	return this->ClearColor;
}
void DrawSettingsEntity::SetClearColor(const CML::Vec4& v)
{
	std::lock_guard<std::mutex> lock(this->metux);
	this->ClearColor = v;
}

DrawSettingsEntity::InclusionType DrawSettingsEntity::GetInclusionState()
{
	std::lock_guard<std::mutex> lock(this->metux);
	return this->InclusionState;
}
void DrawSettingsEntity::SetInclusionState(InclusionType v)
{
	std::lock_guard<std::mutex> lock(this->metux);
	this->InclusionState = v;
}

std::set<std::string> DrawSettingsEntity::GetInclusionList()
{
	std::lock_guard<std::mutex> lock(this->metux);
	return this->InclusionList;
}
void DrawSettingsEntity::SetInclusionList(const std::set<std::string>& v)
{
	std::lock_guard<std::mutex> lock(this->metux);
	this->InclusionList = v;
}
void DrawSettingsEntity::AddInclusionList(std::string ID)
{
	std::lock_guard<std::mutex> lock(this->metux);
	this->InclusionList.insert(ID);
}
void DrawSettingsEntity::DeleteInclusionList(std::string ID)
{
	std::lock_guard<std::mutex> lock(this->metux);
	this->InclusionList.erase(ID);
}
void DrawSettingsEntity::EmptyInclusionList()
{
	std::lock_guard<std::mutex> lock(this->metux);
	this->InclusionList.clear();
}

std::unordered_map<std::string, std::shared_ptr<Object>> DrawSettingsEntity::GetUserData()
{
	std::lock_guard<std::mutex> lock(this->metux);
	return this->UserData;
}
void DrawSettingsEntity::SetUserData(std::unordered_map<std::string, std::shared_ptr<Object>> v)
{
	std::lock_guard<std::mutex> lock(this->metux);
	this->UserData = v;
}
std::shared_ptr<Object> DrawSettingsEntity::FindUserData(const std::string& ID)
{
	std::lock_guard<std::mutex> lock(this->metux);

	std::shared_ptr<Object> returnValue;
	auto iter = this->UserData.find(ID);
	if(iter != this->UserData.end())
	{
		returnValue = iter->second;
	}
	return returnValue;
}
void DrawSettingsEntity::SetUserData(const std::string& ID, const std::shared_ptr<Object>& data)
{
	std::lock_guard<std::mutex> lock(this->metux);
	this->UserData[ID] = data;
}
void DrawSettingsEntity::DeleteUserData(const std::string& ID)
{
	std::lock_guard<std::mutex> lock(this->metux);
	this->UserData.erase(ID);
}
void DrawSettingsEntity::EmptyUserData()
{
	std::lock_guard<std::mutex> lock(this->metux);
	this->UserData.clear();
}

std::unordered_map<std::string, std::string> DrawSettingsEntity::GetTexture()
{
	std::lock_guard<std::mutex> lock(this->metux);
	return this->Texture;
}
void DrawSettingsEntity::SetTexture(std::unordered_map<std::string, std::string> v)
{
	std::lock_guard<std::mutex> lock(this->metux);
	this->Texture = v;
}
bool DrawSettingsEntity::FindTexture(const std::string& ID, std::string& returnTextureID)
{
	std::lock_guard<std::mutex> lock(this->metux);
	bool returnValue = false;
	auto iter = this->Texture.find(ID);
	if(iter != this->Texture.end())
	{
		returnTextureID = iter->second;
		returnValue = true;
	}
	return returnValue;
}
void DrawSettingsEntity::SetTexture(const std::string& ID, const std::string& v)
{
	std::lock_guard<std::mutex> lock(this->metux);
	this->Texture[ID] = v;
}
void DrawSettingsEntity::DeleteTexture(const std::string& ID)
{
	std::lock_guard<std::mutex> lock(this->metux);
	this->Texture.erase(ID);
}
void DrawSettingsEntity::EmptyTexture()
{
	std::lock_guard<std::mutex> lock(this->metux);
	this->Texture.clear();
}

std::string DrawSettingsEntity::GetVertexShaderID()
{
	std::lock_guard<std::mutex> lock(this->metux);
	return this->VertexShaderID;
}
void DrawSettingsEntity::SetVertexShaderID(const std::string& v)
{
	std::lock_guard<std::mutex> lock(this->metux);
	this->VertexShaderID = v;
}

DrawSettingsEntity::DRAWSETTINGS_TYPE DrawSettingsEntity::GetVertexShaderState()
{
	std::lock_guard<std::mutex> lock(this->metux);
	return this->VertexShaderState;
}
void DrawSettingsEntity::SetVertexShaderState(const DrawSettingsEntity::DRAWSETTINGS_TYPE& v)
{
	std::lock_guard<std::mutex> lock(this->metux);
	this->VertexShaderState = v;
}

std::string DrawSettingsEntity::GetPixelShaderID()
{
	std::lock_guard<std::mutex> lock(this->metux);
	return this->PixelShaderID;
}
void DrawSettingsEntity::SetPixelShaderID(const std::string& v)
{
	std::lock_guard<std::mutex> lock(this->metux);
	this->PixelShaderID = v;
}

DrawSettingsEntity::DRAWSETTINGS_TYPE DrawSettingsEntity::GetPixelShaderState()
{
	std::lock_guard<std::mutex> lock(this->metux);
	return this->PixelShaderState;
}
void DrawSettingsEntity::SetPixelShaderState(const DRAWSETTINGS_TYPE& v)
{
	std::lock_guard<std::mutex> lock(this->metux);
	this->PixelShaderState = v;
}

std::shared_ptr<DrawSettingsEntity> DrawSettingsEntity::Spawn()
{
	std::shared_ptr<DrawSettingsEntity> returnValue(new DrawSettingsEntity);
	return returnValue;
}
std::shared_ptr<Entity> DrawSettingsEntity::Clone()
{
	DrawSettingsEntity* temp = new DrawSettingsEntity(*this);
	std::shared_ptr<DrawSettingsEntity> returnValue(temp);
	return returnValue;
}