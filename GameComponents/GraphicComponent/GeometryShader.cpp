#include "GeometryShader.h"

#include "GraphicManager.h"
#include "DX11Helper.h"

void GeometryShader::Init()
{
	auto& graphicD3D = GraphicManager::GetInstance().D3DStuff;

	ID3D11GeometryShader* shader;
	HRESULT hr = graphicD3D.pd3dDevice->CreateGeometryShader(this->CompiledShader.data(),
															 this->CompiledShader.size(),
															 NULL,
															 &shader);

	if(FAILED(hr))
		Logger::LogError("ErrorException: Could not assign compiled Geometry shader to device.");

	this->pGeometryShader = shader;

	this->pCBSetup = CBSetup::Spawn(this->CompiledShader, 0);

	this->pTexture = TextureSetup::Spawn(this->CompiledShader);

	if(this->pCBSetup->GetCBSize() > 0)
	{
		HRESULT hr = S_OK;
		ID3D11Buffer* cbOut;
		// Create Geometry buffer
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

void GeometryShader::Setup(const GraphicCameraEntity& camera, const GraphicObjectEntity& object)
{
	auto& graphicD3D = GraphicManager::GetInstance().D3DStuff;

	graphicD3D.pImmediateContext->GSSetShader(this->pGeometryShader, NULL, 0);

	if(this->pConstantBuffer)
	{
		this->pCBSetup->Run(camera, object);

		ID3D11Buffer* tempCB = this->pConstantBuffer;

		graphicD3D.pImmediateContext->UpdateSubresource(
			tempCB, 0, NULL, this->pCBSetup->GetCBData().data(), 0, 0);
		graphicD3D.pImmediateContext->GSSetConstantBuffers(0, 1, &tempCB);
	}

	std::vector<TextureInfo> textures = this->pTexture->Setup(camera, object);
	for(const TextureInfo& ti : textures)
	{
		auto pTexture = ti.Texture->D3DInfo.pTexture;
		graphicD3D.pImmediateContext->GSSetShaderResources(ti.Slot, 1, &pTexture);
	}
}

std::shared_ptr<GeometryShader> GeometryShader::Spawn(const std::vector<char>& compiledGeometryShader)
{
	std::shared_ptr<GeometryShader> newObject(new GeometryShader());
	newObject->CompiledShader = compiledGeometryShader;
	newObject->Init();

	return newObject;
}
std::shared_ptr<GeometryShader> GeometryShader::Spawn(const std::string& fileName)
{
	std::vector<char> shaderBytes;
	DX11Helper::LoadShaderFile(fileName, "GS", "gs_4_0", shaderBytes);
	return GeometryShader::Spawn(shaderBytes);
}