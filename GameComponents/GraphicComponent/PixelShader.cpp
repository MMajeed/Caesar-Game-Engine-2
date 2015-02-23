#include "PixelShader.h"

#include "GraphicManager.h"
#include "Resource.h"
#include "DX11Helper.h"
void PixelShader::Init()
{
	auto& graphicD3D = Resource::D3DStuff;

	ID3D11PixelShader* shader;
	HRESULT hr = graphicD3D.pd3dDevice->CreatePixelShader(this->CompiledShader.data(),
														  this->CompiledShader.size(),
														  NULL,
														  &shader);

	if(FAILED(hr))
		Logger::LogError("ErrorException: Could not assign compiled Pixel shader to device.");

	this->pPixelShader = shader;

	this->pCBSetup = CBSetup::Spawn(this->CompiledShader, 0);

	this->pTexture = TextureSetup::Spawn(this->CompiledShader);

	if(this->pCBSetup->GetCBSize() > 0)
	{
		HRESULT hr = S_OK;
		ID3D11Buffer* cbOut;
		// Create Pixel buffer
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = this->pCBSetup->GetCBSize();
		bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		bd.CPUAccessFlags = 0;
		hr = graphicD3D.pd3dDevice->CreateBuffer(&bd, NULL, &cbOut);
		if(FAILED(hr))
		{
			//Logger::LogError("Failed at creating constant buffer");
		}
		this->pConstantBuffer = cbOut;
	}
}

void PixelShader::Setup(std::shared_ptr<GraphicCameraEntity> camera, std::shared_ptr<GraphicDrawSettingsEntity> drawSettings, std::shared_ptr<GraphicObjectEntity> object)
{
	auto& graphicD3D = Resource::D3DStuff;

	graphicD3D.pImmediateContext->PSSetShader(this->pPixelShader, NULL, 0);

	if(this->pConstantBuffer)
	{
		this->pCBSetup->Run(camera, drawSettings, object);

		ID3D11Buffer* tempCB = this->pConstantBuffer;

		graphicD3D.pImmediateContext->UpdateSubresource(
			tempCB, 0, NULL, this->pCBSetup->GetCBData().data(), 0, 0);
		graphicD3D.pImmediateContext->PSSetConstantBuffers(0, 1, &tempCB);
	}
	else
	{
		graphicD3D.pImmediateContext->PSSetConstantBuffers(0, 0, nullptr);
	}

	std::vector<TextureInfo> textures = this->pTexture->Setup(camera, drawSettings, object);
	for(const TextureInfo& ti : textures)
	{
		if(ti.Texture)
		{
			ID3D11ShaderResourceView* pTexture = ti.Texture->pTexture;
			graphicD3D.pImmediateContext->PSSetShaderResources(ti.Slot, 1, &pTexture);
		}
		else
		{
			graphicD3D.pImmediateContext->PSSetShaderResources(ti.Slot, 0, nullptr);
		}
	}
}

std::shared_ptr<PixelShader> PixelShader::Spawn(const std::vector<char>& compiledPixelShader)
{
	std::shared_ptr<PixelShader> newObject(new PixelShader());
	newObject->CompiledShader = compiledPixelShader;
	newObject->Init();

	return newObject;
}
std::shared_ptr<PixelShader> PixelShader::Spawn(const std::string& fileName)
{
	std::vector<char> shaderBytes;
	DX11Helper::LoadShaderFile(fileName, "PS", "ps_4_0", shaderBytes);
	return PixelShader::Spawn(shaderBytes);
}