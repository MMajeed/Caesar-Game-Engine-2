#include "DX11Helper.h"

#include <sstream>
#include <d3dcompiler.h>
#include <D3DX11async.h>
#include <Converter.h>
#include <fstream>

void DX11Helper::CompileShaderFromFile(std::string shaderFileName, std::string vsEntryPoint, std::string vsModel, ID3DBlob** ppBlobOut)
{
	HRESULT hr = S_OK;

	DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
	// Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
	// Setting this flag improves the shader debugging experience, but still allows 
	// the shaders to be optimized and to run exactly the way they will run in 
	// the release configuration of this program.
	dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif

	ID3DBlob* pErrorBlob = NULL;
	std::string ASCIIentryPoint = vsEntryPoint;
	std::string ASCIIshaderModel = vsModel;
	hr = D3DX11CompileFromFile(CHL::ToWString(shaderFileName).c_str(), NULL, NULL,
		ASCIIentryPoint.c_str(),
		ASCIIshaderModel.c_str(),
		dwShaderFlags, 0, NULL, ppBlobOut, &pErrorBlob, NULL);

	if (FAILED(hr))
	{
		if (pErrorBlob != NULL)
		{
			std::string ASCIIerror((char*)pErrorBlob->GetBufferPointer());
			pErrorBlob->Release();
			throw std::exception(ASCIIerror.c_str());
		}
		throw std::exception((shaderFileName + " could not be found or complied").c_str());
	}
}
void DX11Helper::LoadShaderFile(std::string shaderFileName, std::string vsEntryPoint, std::string vsModel, std::vector<char>& fileBytes)
{
	if (shaderFileName.substr(shaderFileName.find_last_of(".") + 1) == "fx") {
		ID3DBlob* blob;
		DX11Helper::CompileShaderFromFile(shaderFileName, vsEntryPoint, vsModel, &blob);

		fileBytes.resize(blob->GetBufferSize());
		memcpy(fileBytes.data(), blob->GetBufferPointer(), blob->GetBufferSize());
	}
	else {
		std::ifstream fin(shaderFileName, std::ios::binary);

		fin.seekg(0, std::ios_base::end);
		int size = (int)fin.tellg();
		fin.seekg(0, std::ios_base::beg);
		fileBytes.resize(size);

		fin.read(fileBytes.data(), size);
		fin.close();
	}
}
void DX11Helper::LoadInputLayoutFile(std::string vsFileName, ID3D11Device* device, D3D11_INPUT_ELEMENT_DESC layout[], UINT numElements, ID3D11InputLayout** ilOut)
{
	std::vector<char> fileBytes;

	DX11Helper::LoadShaderFile(vsFileName, "VS", "vs_4_1", fileBytes);

	// Now pass this compiled vertex shader to the device so it can be used
	HRESULT hr = device->CreateInputLayout(layout, numElements, fileBytes.data(), fileBytes.size(), ilOut);

	// NOTE: DON'T Release the VSblob yet as it's needed for the vertex layout...
	if (FAILED(hr))
	{
		throw std::exception("ERROR: Could not assign compiled vertex shader to device.");
	}
}
void DX11Helper::LoadVertexShaderFile(std::string vsFileName, ID3D11Device* device, ID3D11VertexShader** vsOut)
{
	std::vector<char> fileBytes;

	DX11Helper::LoadShaderFile(vsFileName, "VS", "vs_4_1", fileBytes);

	// Now pass this compiled vertex shader to the device so it can be used
	HRESULT hr = device->CreateVertexShader(fileBytes.data(), fileBytes.size(), NULL, vsOut);

	// NOTE: DON'T Release the VSblob yet as it's needed for the vertex layout...
	if (FAILED(hr))
	{
		throw std::exception("ERROR: Could not assign compiled vertex shader to device.");
	}
}
void DX11Helper::LoadPixelShaderFile(std::string psFileName, ID3D11Device* device, ID3D11PixelShader** pxOut)
{
	std::vector<char> fileBytes;

	DX11Helper::LoadShaderFile(psFileName, "PS", "ps_4_1", fileBytes);

	// Now pass this compiled vertex shader to the device so it can be used
	HRESULT hr = device->CreatePixelShader(fileBytes.data(), fileBytes.size(), NULL, pxOut);

	// NOTE: DON'T Release the VSblob yet as it's needed for the vertex layout...
	if (FAILED(hr))
	{
		throw std::exception("ERROR: Could not assign compiled pixel shader to device.");
	}
}
void DX11Helper::LoadRasterizerState(D3D11_CULL_MODE cullMode, D3D11_FILL_MODE fillMode, bool bAntialiasedLine, bool bMultisampleEnable, ID3D11Device* device, ID3D11RasterizerState** rsOut)
{
	// Additional stuff...
	D3D11_RASTERIZER_DESC RSDesc;
	memset( &RSDesc, 0, sizeof(D3D11_RASTERIZER_DESC) );
	RSDesc.FillMode = fillMode; 
	RSDesc.AntialiasedLineEnable = bAntialiasedLine;	
	RSDesc.MultisampleEnable = bMultisampleEnable;
	RSDesc.CullMode = cullMode;	


	HRESULT hr = device->CreateRasterizerState( &RSDesc, rsOut );
	if(FAILED(hr))
	{
		throw std::exception("ERROR: Can't create rasterizer state");
	}
}
void DX11Helper::LoadTextureFile(std::wstring txFileName, ID3D11Device* device, ID3D11ShaderResourceView** pxOut)
{
	HRESULT hr  = D3DX11CreateShaderResourceViewFromFile( device,
					txFileName.c_str(),
					NULL,			// Returns image information about texture
					NULL,			// Used to load texture in other thread
					pxOut, 
					NULL );
	if(FAILED(hr))
	{
		throw std::exception(std::string("ERROR: Can't create texture " + CHL::ToString(txFileName)).c_str());
	}
}
void DX11Helper::LoadSamplerState(D3D11_FILTER filter, D3D11_TEXTURE_ADDRESS_MODE addresU, D3D11_TEXTURE_ADDRESS_MODE addressV, D3D11_TEXTURE_ADDRESS_MODE addressW, D3D11_COMPARISON_FUNC camparisonFunc, float minLOD, float maxLod, ID3D11Device* device, ID3D11SamplerState** ssOut)
{
	D3D11_SAMPLER_DESC sampDesc;
    ZeroMemory( &sampDesc, sizeof(sampDesc) );
    sampDesc.Filter = filter;
    sampDesc.AddressU = addresU;
    sampDesc.AddressV = addressV;
    sampDesc.AddressW = addressW;
    sampDesc.ComparisonFunc = camparisonFunc;
    sampDesc.MinLOD = minLOD;
    sampDesc.MaxLOD = maxLod;
    HRESULT hr = device->CreateSamplerState( &sampDesc, ssOut );
	if(FAILED(hr))
	{
		throw std::exception("ERROR: Can't create Sampler State");
	}
}
void DX11Helper::LoadTransparent(ID3D11Device* device, ID3D11BlendState** bsOut)
{
	D3D11_BLEND_DESC transparentDesc = {0};
	transparentDesc.AlphaToCoverageEnable = false;
	transparentDesc.IndependentBlendEnable = false;

	transparentDesc.RenderTarget[0].BlendEnable = true;
	transparentDesc.RenderTarget[0].SrcBlend       = D3D11_BLEND_SRC_ALPHA;
	transparentDesc.RenderTarget[0].DestBlend      = D3D11_BLEND_INV_SRC_ALPHA;
	transparentDesc.RenderTarget[0].BlendOp        = D3D11_BLEND_OP_ADD;
	transparentDesc.RenderTarget[0].SrcBlendAlpha  = D3D11_BLEND_ONE;
	transparentDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	transparentDesc.RenderTarget[0].BlendOpAlpha   = D3D11_BLEND_OP_ADD;
	transparentDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	HRESULT hr = device->CreateBlendState(&transparentDesc, bsOut );

	if(FAILED(hr))
	{
		throw std::exception("ERROR: Can't create Sampler State");
	}
}