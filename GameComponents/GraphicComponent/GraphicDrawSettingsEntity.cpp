#include "GraphicDrawSettingsEntity.h"

#include "GraphicObjectEntity.h"
#include "XNAConverter.h"
#include "ResourceManager.h"
#include "GraphicManager.h"
#include "3DMath.h"

GraphicDrawSettingsEntity::GraphicDrawSettingsEntity()
{
	this->Update(nullptr);
}
GraphicDrawSettingsEntity::GraphicDrawSettingsEntity(std::shared_ptr<DrawSettingsEntity> v)
{
	this->Update(v);
}

void GraphicDrawSettingsEntity::Update(std::shared_ptr<DrawSettingsEntity> v)
{
	this->UpdateClearScreen(v);
	this->UpdateClearColor(v);
	this->UpdateInclusionState(v);
	this->UpdateInclusionList(v);
	this->UpdateTextureList(v);
	this->UpdateUserData(v);
	this->UpdateVertexShaderID(v);
	this->UpdateVertexShaderState(v);
	this->UpdatePixelShaderID(v);
	this->UpdatePixelShaderState(v);
}

std::vector<std::shared_ptr<GraphicObjectEntity>>
GraphicDrawSettingsEntity::FilterInclusionList(std::unordered_map<std::string, std::shared_ptr<GraphicObjectEntity>> list) const
{
	std::vector<std::shared_ptr<GraphicObjectEntity>> returnValue;
	returnValue.reserve(list.size());

	const DrawSettingsEntity::InclusionType& inclusionState = this->InclusionState;
	const std::set<std::string>& DrawSettingsInclusionList = this->InclusionList;
	for(auto iter = list.begin(); iter != list.end(); ++iter)
	{
		std::set<std::string> objGroup = iter->second->GetGroupList();

		std::vector<std::string> groupDifference;
		std::set_intersection(objGroup.cbegin(), objGroup.cend(),
							  DrawSettingsInclusionList.cbegin(), DrawSettingsInclusionList.cend(),
							  std::back_inserter(groupDifference));

		if(inclusionState == DrawSettingsEntity::InclusionType::Exclude)
		{// if CANT be on the list
			if(groupDifference.size() > 0){ continue; }
		}
		else if(inclusionState == DrawSettingsEntity::InclusionType::Include)
		{ // It has to be on the list for it to be added
			if(groupDifference.size() == 0){ continue; }
		}
		returnValue.push_back(iter->second);
	}

	/*XMFLOAT4 eye = this->GetEye();
	std::sort(returnValue.begin(), returnValue.end(),
			  [&eye](const std::shared_ptr<GraphicObjectEntity>& a, const std::shared_ptr<GraphicObjectEntity>& b) -> bool
	{
		float rankA = Length(eye, a->GetLocation());
		float rankB = Length(eye, b->GetLocation());

		rankA += a->GetPriority();
		rankB += b->GetPriority();

		return rankA > rankB;
	});*/

	return returnValue;
}

void GraphicDrawSettingsEntity::UpdateClearScreen(std::shared_ptr<DrawSettingsEntity> obj)
{
	if(obj) { this->ClearScreen = obj->GetClearScreen(); }
	else	{ this->ClearScreen = true; }
}
bool GraphicDrawSettingsEntity::GetClearScreen() const
{
	return this->ClearScreen;
}

void GraphicDrawSettingsEntity::UpdateClearColor(std::shared_ptr<DrawSettingsEntity> obj)
{
	if(obj)
	{
		auto clearValue = obj->GetClearColor();
		this->ClearColor = {{(float)clearValue(0), (float)clearValue(1), (float)clearValue(2), (float)clearValue(3)}};
	}
	else	{ this->ClearColor = {{0.0f, 0.0f, 0.0f, 1.0f}}; }
}
std::array<float, 4> GraphicDrawSettingsEntity::GetClearColor() const
{
	return this->ClearColor;
}

void GraphicDrawSettingsEntity::UpdateInclusionState(std::shared_ptr<DrawSettingsEntity> obj)
{
	if(obj)	{ this->InclusionState = obj->GetInclusionState(); }
	else	{ this->InclusionState = DrawSettingsEntity::InclusionType::Exclude; }
}
DrawSettingsEntity::InclusionType GraphicDrawSettingsEntity::GetInclusionState() const
{
	return this->InclusionState;
}

void GraphicDrawSettingsEntity::UpdateInclusionList(std::shared_ptr<DrawSettingsEntity> obj)
{
	if(obj)	{ this->InclusionList = obj->GetInclusionList(); }
}
std::set<std::string> GraphicDrawSettingsEntity::GetInclusionList() const
{
	return this->InclusionList;
}

void GraphicDrawSettingsEntity::UpdateTextureList(std::shared_ptr<DrawSettingsEntity> obj)
{
	if(obj)	{ this->TextureList = obj->GetTexture(); }
}
std::unordered_map<std::string, std::string> GraphicDrawSettingsEntity::GetTextureList() const
{
	return this->TextureList;
}
std::unordered_map<std::string, std::shared_ptr<BasicTexture>> GraphicDrawSettingsEntity::GetTexture() const
{
	std::unordered_map<std::string, std::shared_ptr<BasicTexture>> returnValue;

	for(const auto& iter : this->TextureList)
	{
		returnValue[iter.first] = this->FindTexture(iter.second);
	}

	return returnValue;
}
std::shared_ptr<BasicTexture> GraphicDrawSettingsEntity::FindTexture(const std::string& ID) const
{
	std::shared_ptr<BasicTexture> returnValue;

	auto iter = this->TextureList.find(ID);
	if(iter != this->TextureList.end())
	{
		returnValue = ResourceManager::TextureList.Find(iter->second);
	}
	return returnValue;
}

void GraphicDrawSettingsEntity::UpdateUserData(std::shared_ptr<DrawSettingsEntity> obj)
{
	if(obj)	{ this->UserData = obj->GetUserData(); }
}
std::unordered_map<std::string, std::shared_ptr<Object>> GraphicDrawSettingsEntity::GetUserData() const
{
	return this->UserData;
}
std::shared_ptr<Object> GraphicDrawSettingsEntity::FindUserData(const std::string& ID) const
{
	std::shared_ptr<Object> returnValue;
	auto iter = this->UserData.find(ID);
	if(iter != this->UserData.cend())
	{
		returnValue = iter->second;
	}
	return returnValue;
}

void GraphicDrawSettingsEntity::UpdateVertexShaderID(std::shared_ptr<DrawSettingsEntity> obj)
{
	if(obj)	{ this->VertexShaderID = obj->GetVertexShaderID(); }
}
std::string GraphicDrawSettingsEntity::GetVertexShaderID() const
{
	return this->VertexShaderID;
}
std::shared_ptr<VertexShader> GraphicDrawSettingsEntity::GetVertexShader() const
{
	const std::string& id = this->VertexShaderID;
	std::shared_ptr<VertexShader> returnValue = ResourceManager::VertexShaderList.Find(id);
	return returnValue;
}

void GraphicDrawSettingsEntity::UpdateVertexShaderState(std::shared_ptr<DrawSettingsEntity> obj)
{
	if(obj)	{ this->VertexShaderState = obj->GetVertexShaderState(); }
	else { this->VertexShaderState = DrawSettingsEntity::DRAWSETTINGS_TYPE::DEFAULT; }
}
DrawSettingsEntity::DRAWSETTINGS_TYPE GraphicDrawSettingsEntity::GetVertexShaderState() const
{
	return this->VertexShaderState;
}

void GraphicDrawSettingsEntity::UpdatePixelShaderID(std::shared_ptr<DrawSettingsEntity> obj)
{
	if(obj)	{ this->PixelShaderID = obj->GetPixelShaderID(); }
}
std::string GraphicDrawSettingsEntity::GetPixelShaderID() const
{
	return this->PixelShaderID;
}
std::shared_ptr<PixelShader> GraphicDrawSettingsEntity::GetPixelShader() const
{
	const std::string& id = this->PixelShaderID;
	std::shared_ptr<PixelShader> returnValue = ResourceManager::PixelShaderList.Find(id);
	return returnValue;
}

void GraphicDrawSettingsEntity::UpdatePixelShaderState(std::shared_ptr<DrawSettingsEntity> obj)
{
	if(obj)	{ this->PixelShaderState = obj->GetPixelShaderState(); }
	else { this->PixelShaderState = DrawSettingsEntity::DRAWSETTINGS_TYPE::DEFAULT; }
}
DrawSettingsEntity::DRAWSETTINGS_TYPE GraphicDrawSettingsEntity::GetPixelShaderState() const
{
	return this->PixelShaderState;
}
