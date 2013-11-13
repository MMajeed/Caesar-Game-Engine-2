#ifndef __DX11Helper__
#define __DX11Helper__

#include "Linker.h"

#include <string>
#include <D3D11.h>
#include <xnamath.h>
#include <vector>

namespace DX11Helper 
{
	void CompileShaderFromFile(std::string shaderFileName, std::string vsEntryPoint, std::string vsModel, ID3DBlob** ppBlobOut);
	void LoadShaderFile(std::string shaderFileName, std::string vsEntryPoint, std::string vsModel, std::vector<char>& fileBytes);
	void LoadInputLayoutFile(std::string vsFileName, ID3D11Device* device, D3D11_INPUT_ELEMENT_DESC layout[], UINT numElements, ID3D11InputLayout** ilOut);
	void LoadVertexShaderFile(std::string vsFileName, ID3D11Device* device, ID3D11VertexShader** vsOut);
	void LoadPixelShaderFile(std::string psFileName, ID3D11Device* device, ID3D11PixelShader** pxOut);

	HRESULT LoadRasterizerState( D3D11_CULL_MODE cullMode, D3D11_FILL_MODE fillMode, bool bAntialiasedLine, bool bMultisampleEnable, ID3D11Device* device, ID3D11RasterizerState** rsOut, std::wstring &error );
	HRESULT LoadTextureFile( std::wstring txFileName, ID3D11Device* device, ID3D11ShaderResourceView** pxOut, std::wstring &error  );	
	HRESULT LoadSamplerState( D3D11_FILTER filter, D3D11_TEXTURE_ADDRESS_MODE addresU,D3D11_TEXTURE_ADDRESS_MODE addressV,  D3D11_TEXTURE_ADDRESS_MODE addressw, D3D11_COMPARISON_FUNC camparisonFunc, float minLOD, float maxLod, ID3D11Device* device, ID3D11SamplerState** ssOut, std::wstring &error  );	
	HRESULT LoadTransparent( ID3D11Device* device, ID3D11BlendState** bsOut, std::wstring &error  );	

	template<typename T>
	HRESULT LoadVertexBuffer(ID3D11Device* device, T* pVertex, std::size_t numElements, ID3D11Buffer** bOut, std::wstring& error)
	{
		HRESULT hr = S_OK ;

		// Create vertex buffer
		D3D11_BUFFER_DESC bd;
		ZeroMemory( &bd, sizeof(bd) );
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof( T ) * numElements;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = 0;
		D3D11_SUBRESOURCE_DATA InitData;
		ZeroMemory( &InitData, sizeof(InitData) );
		InitData.pSysMem = pVertex;
		hr = device->CreateBuffer( &bd, &InitData, bOut );
		if( FAILED( hr ) )
		{
			error = L"Failed at creating vertex buffer";
			return false;
		}
		return true;
	}

	template<typename T>
	HRESULT LoadIndexBuffer(ID3D11Device* device, T* pIndice, std::size_t numElements, ID3D11Buffer** bOut, std::wstring& error)
	{	
		HRESULT hr = S_OK ;

		// Create index buffer
		D3D11_BUFFER_DESC bd;
		ZeroMemory( &bd, sizeof(bd) );
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof( T ) * numElements;
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.CPUAccessFlags = 0;
		D3D11_SUBRESOURCE_DATA InitData;
		ZeroMemory( &InitData, sizeof(InitData) );
		InitData.pSysMem = pIndice;
		hr = device->CreateBuffer( &bd, &InitData, bOut );
		if( FAILED( hr ) )
		{
			error = L"Failed at creating vertex buffer";
			return false;
		}

		return true;
	}

	template<typename T>
	HRESULT LoadBuffer( ID3D11Device* device, ID3D11Buffer** cbOut, std::wstring &error )
	{
		HRESULT hr = S_OK ;

		// Create vertex buffer
		D3D11_BUFFER_DESC bd;
		ZeroMemory( &bd, sizeof(bd) );
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(T);
		bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		bd.CPUAccessFlags = 0;
		hr = device->CreateBuffer( &bd, NULL, cbOut );
		if( FAILED( hr ) )
		{
			error = L"Failed at creating constant buffer buffer";
			return false;
		}
		return true;
	}
};

#endif //__DX11Helper__