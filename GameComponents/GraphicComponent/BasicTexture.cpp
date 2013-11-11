#include "BasicTexture.h"

#include "GraphicManager.h"
#include "DX11Helper.h"
#include <Keys.h>

BasicTexture::BasicTexture(const std::string& inputID)
	: Texture(inputID)
{
	this->D3DInfo.pTexture = 0;
}
void BasicTexture::Init()
{
	ID3D11Device* device = GraphicManager::GetInstance().direct3d.pd3dDevice;

	if(!this->D3DInfo.textureFileName.empty())
	{
		std::wstring error;
		if(!DX11Helper::LoadTextureFile(CHL::ToWString(this->D3DInfo.textureFileName), device, &(this->D3DInfo.pTexture), error))
		{
			throw std::exception(CHL::ToString(error).c_str());
		}
	}
}
void BasicTexture::Destory()
{
	this->D3DInfo.pTexture->Release();
}
void BasicTexture::SettupTexture(TypedefObject::ObjectInfo& object)
{
	int slot = 0;

	TypedefObject::ObjectInfo::const_iterator iterKey;
	iterKey = object.find(Keys::ObjectInfo::TEXTURESLOT + this->ID);
	if (iterKey != object.end())
	{
		slot = GenericObject<int>::GetValue(iterKey->second);
	}

	ID3D11DeviceContext* pImmediateContext = GraphicManager::GetInstance().direct3d.pImmediateContext;
	
	pImmediateContext->PSSetShaderResources(slot, 1, &(this->D3DInfo.pTexture));
}
void BasicTexture::CleanupTexture(TypedefObject::ObjectInfo& object)
{
	int slot = 0;

	TypedefObject::ObjectInfo::const_iterator iterKey;
	iterKey = object.find(Keys::ObjectInfo::TEXTURESLOT + this->ID);
	if (iterKey != object.end())
	{
		slot = GenericObject<int>::GetValue(iterKey->second);
	}

	ID3D11DeviceContext* pImmediateContext = GraphicManager::GetInstance().direct3d.pImmediateContext;
	
	ID3D11ShaderResourceView* tab = NULL;
	
	pImmediateContext->PSSetShaderResources(slot, 1, &tab);
}
void BasicTexture::Update(double realTime, double deltaTime)
{

}
std::shared_ptr<BasicTexture> BasicTexture::Spawn(const std::string& inputID, const std::string& fileName)
{
	std::shared_ptr<BasicTexture> newTexture(new BasicTexture(inputID));
	newTexture->D3DInfo.textureFileName = fileName;

	newTexture->Init();

	return newTexture;
}