#include "VertexShader.h"

#include "GraphicManager.h"

void VertexShader::Init(const std::vector<char>& compiledShader)
{
	auto& graphicD3D = GraphicManager::GetInstance().D3DStuff;

	ID3D11VertexShader* shader;
	HRESULT hr = graphicD3D.pd3dDevice->CreateVertexShader(compiledShader.data(),
														  compiledShader.size(),
														  NULL,
														  &shader);

	if(FAILED(hr))
		Logger::LogError("ErrorException: Could not assign compiled Vertex shader to device.");

	this->pVertexShader = shader;

	this->pCBufferSetup = CBufferSetup::Spawn(compiledShader, 0);

	if(this->pCBufferSetup->GetCBSize() > 0)
	{
		HRESULT hr = S_OK;
		ID3D11Buffer* cbOut;
		// Create vertex buffer
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

void VertexShader::Setup(std::shared_ptr<ObjectEntity> object, const SceneInfo& si)
{
	auto& graphicD3D = GraphicManager::GetInstance().D3DStuff;

	graphicD3D.pImmediateContext->VSSetShader(this->pVertexShader, NULL, 0);

	if(this->pConstantBuffer)
	{
		this->pCBufferSetup->Run(object, si);

		ID3D11Buffer* tempCB = this->pConstantBuffer;

		graphicD3D.pImmediateContext->UpdateSubresource(
			tempCB, 0, NULL, this->pCBufferSetup->GetCBData().data(), 0, 0);
		graphicD3D.pImmediateContext->VSSetConstantBuffers(0, 1, &tempCB);
	}
}

std::shared_ptr<VertexShader> VertexShader::Spawn(const std::vector<char>& compiledVertexShader)
{
	std::shared_ptr<VertexShader> newObject(new VertexShader());

	newObject->Init(compiledVertexShader);

	return newObject;
}