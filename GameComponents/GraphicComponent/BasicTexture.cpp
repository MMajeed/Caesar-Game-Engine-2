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
	ID3D11Device* device = GraphicManager::GetInstance().D3DStuff.pd3dDevice;

	if(!this->D3DInfo.textureFileName.empty())
	{
		DX11Helper::LoadTextureFile(CHL::ToWString(this->D3DInfo.textureFileName), device, &(this->D3DInfo.pTexture));
	}
}
void BasicTexture::Destory()
{
	this->D3DInfo.pTexture->Release();
}
void BasicTexture::SettupTexture(int slot)
{
	ID3D11DeviceContext* pImmediateContext = GraphicManager::GetInstance().D3DStuff.pImmediateContext;
	
	pImmediateContext->PSSetShaderResources(slot, 1, &(this->D3DInfo.pTexture));
}
void BasicTexture::CleanupTexture(int slot)
{
	ID3D11DeviceContext* pImmediateContext = GraphicManager::GetInstance().D3DStuff.pImmediateContext;
	
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
std::shared_ptr<BasicTexture> BasicTexture::Spawn(const std::string& inputID, ID3D11ShaderResourceView*& texture)
{
	std::shared_ptr<BasicTexture> newTexture(new BasicTexture(inputID));
	newTexture->D3DInfo.pTexture = texture;
	newTexture->Init();

	return newTexture;
}