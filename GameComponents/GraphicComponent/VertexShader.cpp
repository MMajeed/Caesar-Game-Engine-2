#include "VertexShader.h"

#include <D3DCompiler.h>
#include "GraphicManager.h"
#include "DX11Helper.h"
#include "GraphicModel.h"
#include "ResourceManager.h"

void VertexShader::Init()
{
	auto& graphicD3D = GraphicManager::GetInstance().D3DStuff;

	ID3D11VertexShader* shader;
	HRESULT hr = graphicD3D.pd3dDevice->CreateVertexShader(this->CompiledShader.data(),
														   this->CompiledShader.size(),
														   NULL,
														   &shader);

	if(FAILED(hr)){ Logger::LogError("ErrorException: Could not assign compiled Vertex shader to device."); }

	this->pVertexShader = shader;

	this->pCBSetup = CBSetup::Spawn(this->CompiledShader, 0);

	this->pTexture = TextureSetup::Spawn(this->CompiledShader);

	if(this->pCBSetup->GetCBSize() > 0)
	{
		HRESULT hr = S_OK;
		ID3D11Buffer* cbOut;
		// Create vertex buffer
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = this->pCBSetup->GetCBSize();
		bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		bd.CPUAccessFlags = 0;
		hr = graphicD3D.pd3dDevice->CreateBuffer(&bd, NULL, &cbOut);
		if(FAILED(hr))
		{
			Logger::LogError("Failed at creating constant buffer");
		}
		this->pConstantBuffer = cbOut;
	}
}

void VertexShader::Setup(std::shared_ptr<GraphicCameraEntity> camera, std::shared_ptr<GraphicObjectEntity> object)
{
	auto& graphicD3D = GraphicManager::GetInstance().D3DStuff;

	graphicD3D.pImmediateContext->VSSetShader(this->pVertexShader, NULL, 0);

	if(this->pConstantBuffer)
	{
		this->pCBSetup->Run(camera, object);

		ID3D11Buffer* tempCB = this->pConstantBuffer;
		graphicD3D.pImmediateContext->UpdateSubresource(
			tempCB, 0, NULL, this->pCBSetup->GetCBData().data(), 0, 0);
		graphicD3D.pImmediateContext->VSSetConstantBuffers(0, 1, &tempCB);
	}
	else
	{
		graphicD3D.pImmediateContext->VSSetConstantBuffers(0, 0, nullptr);
	}

	std::vector<TextureInfo> textures = this->pTexture->Setup(camera, object);
	for(const TextureInfo& ti : textures)
	{
		if(ti.Texture)
		{
			ID3D11ShaderResourceView* pTexture = ti.Texture->pTexture;
			graphicD3D.pImmediateContext->VSSetShaderResources(ti.Slot, 1, &pTexture);
		}
		else
		{
			graphicD3D.pImmediateContext->VSSetShaderResources(ti.Slot, 0, nullptr);
		}
	}
}

std::shared_ptr<VertexShader> VertexShader::Spawn(const std::vector<char>& compiledVertexShader)
{
	std::shared_ptr<VertexShader> newObject(new VertexShader());

	newObject->CompiledShader = compiledVertexShader;
	newObject->Init();

	return newObject;
}
std::shared_ptr<VertexShader> VertexShader::Spawn(const std::string& fileName)
{
	std::vector<char> shaderBytes;
	DX11Helper::LoadShaderFile(fileName, "VS", "vs_4_0", shaderBytes);
	return VertexShader::Spawn(shaderBytes);
}

COMSharedPtr<ID3D11InputLayout> VertexShader::GenerateInputLayout(std::shared_ptr<GraphicModel> model)
{
	auto& graphicD3D = GraphicManager::GetInstance().D3DStuff;

	std::shared_ptr<GraphicModel> gm = model;
	if(gm == false){ Logger::LogError("ErrorException: Could not locate graphic model while creating the Input Layout"); }

	std::vector<VertexLayout> vertexLayoutList = gm->GetVertexLayout();

	ID3D11ShaderReflection* pReflector = nullptr;
	D3DReflect(this->CompiledShader.data(), this->CompiledShader.size(),
			   IID_ID3D11ShaderReflection, (void**)&pReflector);

	if(pReflector == nullptr){ Logger::LogError("ErrorException: Could not create ID3D11ShaderReflection out of the shader"); }

	D3D11_SHADER_DESC pDesc;
	HRESULT hr = pReflector->GetDesc(&pDesc);
	if(hr != S_OK){ Logger::LogError("ErrorException: Could not create ID3D11ShaderReflection out of the shader"); }
	

	std::vector<D3D11_INPUT_ELEMENT_DESC> layout;

	for(unsigned int i = 0; i < pDesc.InputParameters; ++i)
	{
		D3D11_SIGNATURE_PARAMETER_DESC pDesc;
		HRESULT hr = pReflector->GetInputParameterDesc(i, &pDesc);
		if(hr != S_OK){ Logger::LogError("ErrorException: Could not create ID3D11ShaderReflection out of the shader"); }

		auto iter =	std::find_if(vertexLayoutList.cbegin(),
								 vertexLayoutList.cend(),
								 [&pDesc](const VertexLayout& vl){ return vl.Name == pDesc.SemanticName; });

		if(iter != vertexLayoutList.cend())
		{
			const VertexLayout& vl = *iter;
			D3D11_INPUT_ELEMENT_DESC dl{vl.Name.c_str(), 0, vl.Format, 0, vl.Offset, D3D11_INPUT_PER_VERTEX_DATA, 0};
			layout.push_back(dl);
		}
		else
		{
			D3D11_INPUT_ELEMENT_DESC dl{pDesc.SemanticName, 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0};
			layout.push_back(dl);
		}
	}

	ID3D11InputLayout* pVertexLayout;
	// Create the input layout
	hr = graphicD3D.pd3dDevice->CreateInputLayout(layout.data(), layout.size(),
												  this->CompiledShader.data(), this->CompiledShader.size(),
												  &pVertexLayout);
	if(FAILED(hr)){ Logger::LogError("ErrorException: Could not assign compiled Vertex shader to device."); }

	return pVertexLayout;
}