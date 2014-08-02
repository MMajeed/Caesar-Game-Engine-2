#include "BasicTexture.h"

#include "GraphicManager.h"
#include "DX11Helper.h"
#include <Converter.h>

BasicTexture::BasicTexture()
{
}
void BasicTexture::Init(const std::string& fileName)
{
	ID3D11Device* device = GraphicManager::GetInstance().D3DStuff.pd3dDevice;

	if(!fileName.empty())
	{
		ID3D11ShaderResourceView* texture;
		DX11Helper::LoadTextureFile(CHL::ToWString(fileName), device, &texture);
		this->pTexture = texture;
	}
}
std::shared_ptr<BasicTexture> BasicTexture::Spawn(const std::string& fileName)
{
	std::shared_ptr<BasicTexture> newTexture(new BasicTexture());

	newTexture->Init(fileName);

	return newTexture;
}
std::shared_ptr<BasicTexture> BasicTexture::Spawn(ID3D11ShaderResourceView* texture)
{
	std::shared_ptr<BasicTexture> newTexture(new BasicTexture());
	newTexture->pTexture = texture;

	return newTexture;
}
std::shared_ptr<BasicTexture> BasicTexture::Spawn()
{
	std::shared_ptr<BasicTexture> newTexture(new BasicTexture());
	return newTexture;
}