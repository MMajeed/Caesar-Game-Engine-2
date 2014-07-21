#include "PixelShader.h"

#include "GraphicManager.h"

void PixelShader::Init(const std::vector<char>& compiledShader)
{
	auto& graphicD3D = GraphicManager::GetInstance().D3DStuff;

	ID3D11PixelShader* shader;
	HRESULT hr = graphicD3D.pd3dDevice->CreatePixelShader(compiledShader.data(),
														   compiledShader.size(),
														   NULL,
														   &shader);

	if(FAILED(hr))
		Logger::LogError("ErrorException: Could not assign compiled Pixel shader to device.");

	this->pPixelShader = shader;

	this->pCBufferSetup = CBufferSetup::Spawn(compiledShader, 0);

	if(this->pCBufferSetup->GetCBSize() > 0)
	{
		HRESULT hr = S_OK;
		ID3D11Buffer* cbOut;
		// Create Pixel buffer
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = this->pCBufferSetup->GetCBSize();
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

void PixelShader::Setup(std::shared_ptr<ObjectEntity> object, const SceneInfo& si)
{
	auto& graphicD3D = GraphicManager::GetInstance().D3DStuff;

	graphicD3D.pImmediateContext->PSSetShader(this->pPixelShader, NULL, 0);

	if(this->pConstantBuffer)
	{
		this->pCBufferSetup->Run(object, si);

		ID3D11Buffer* tempCB = this->pConstantBuffer;

		graphicD3D.pImmediateContext->UpdateSubresource(
			tempCB, 0, NULL, this->pCBufferSetup->GetCBData().data(), 0, 0);
		graphicD3D.pImmediateContext->PSSetConstantBuffers(0, 1, &tempCB);
	}
}

std::shared_ptr<PixelShader> PixelShader::Spawn(const std::vector<char>& compiledPixelShader)
{
	std::shared_ptr<PixelShader> newObject(new PixelShader());

	newObject->Init(compiledPixelShader);

	return newObject;
}