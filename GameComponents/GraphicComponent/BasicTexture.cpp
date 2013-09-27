#include "BasicTexture.h"

#include "GraphicManager.h"
#include "DX11Helper.h"

BasicTexture::BasicTexture()
{
	this->D3DInfo.pTexture = 0;
	this->D3DInfo.slot = 0;
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
void BasicTexture::SettupTexture()
{
	ID3D11DeviceContext* pImmediateContext = GraphicManager::GetInstance().direct3d.pImmediateContext;
	
	pImmediateContext->PSSetShaderResources( this->D3DInfo.slot, 1, &(this->D3DInfo.pTexture) );
}
void BasicTexture::CleanupTexture()
{
	ID3D11DeviceContext* pImmediateContext = GraphicManager::GetInstance().direct3d.pImmediateContext;
	
	ID3D11ShaderResourceView* tab = NULL;
	
	pImmediateContext->PSSetShaderResources(this->D3DInfo.slot,1,&tab);
}
	
std::shared_ptr<BasicTexture> BasicTexture::Spawn(int slot, std::string fileName)
{
	std::shared_ptr<BasicTexture> newTexture(new BasicTexture);
	newTexture->D3DInfo.textureFileName = fileName;
	newTexture->D3DInfo.slot = slot;

	newTexture->Init();

	return newTexture;
}