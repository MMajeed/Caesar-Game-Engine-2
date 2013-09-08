#include "BasicDrawable.h"
#include "GraphicManager.h"
#include "DX11Helper.h"
#include "Buffers.h"

#include <Converter.h>

BasicDrawable::BasicDrawable()
{
	this->D3DInfo.pVertexBuffer = 0;
	this->D3DInfo.pIndexBuffer = 0;
	this->D3DInfo.pConstantBuffer = 0;
	this->D3DInfo.pInputLayout = 0;
	this->D3DInfo.pVertexShader = 0;
	this->D3DInfo.pPixelShader = 0;
	this->D3DInfo.pRastersizerState = 0;
	this->D3DInfo.pTexture = 0;
}

void BasicDrawable::Init()
{
	ID3D11Device* device = GraphicManager::GetInstance().direct3d.pd3dDevice;
	this->InitVertexBuffer(device);
	this->InitIndexBuffer(device);
	this->InitInputLayout(device);
	this->InitVertexShader(device);
	this->InitPixelShader(device);
	this->InitRastersizerState(device);
	this->InitConstantBuffer(device);
	this->InitTexture(device);
}

void BasicDrawable::Clean()
{
	this->D3DInfo.pVertexBuffer->Release();
	this->D3DInfo.pIndexBuffer->Release();
	this->D3DInfo.pConstantBuffer->Release();
	this->D3DInfo.pInputLayout->Release();
	this->D3DInfo.pVertexShader->Release();
	this->D3DInfo.pPixelShader->Release();
	this->D3DInfo.pRastersizerState->Release();
	this->D3DInfo.pTexture->Release();
}

void BasicDrawable::Update(float delta)
{

}

void BasicDrawable::Draw()
{
	this->SetupDrawConstantBuffer();
	this->SetupDrawVertexBuffer();
	this->SetupDrawInputVertexShader();
	this->SetupDrawPixelShader();
	this->SetupDrawRasterizeShader();
	this->SetupDrawTexture();
}

void BasicDrawable::SetupDrawConstantBuffer()
{

}

void BasicDrawable::SetupDrawVertexBuffer()
{

}

void BasicDrawable::SetupDrawInputVertexShader()
{

}

void BasicDrawable::SetupDrawPixelShader()
{

}

void BasicDrawable::SetupDrawRasterizeShader()
{

}

void BasicDrawable::SetupDrawTexture()
{

}

void BasicDrawable::DrawObject()
{

}

void BasicDrawable::CleanupAfterDraw()	
{

}

void BasicDrawable::InitVertexBuffer(ID3D11Device* device)
{
	std::wstring error;

	if(!DX11Helper::LoadVertexBuffer<Vertex>(device, &(this->D3DInfo.vertices.front()), this->D3DInfo.vertices.size(), &(this->D3DInfo.pVertexBuffer), error ))
	{
		throw std::exception(CHL::ToString(error).c_str());
	}
}

void BasicDrawable::InitIndexBuffer(ID3D11Device* device)
{
	std::wstring error;

	if(!DX11Helper::LoadVertexBuffer<WORD>(device, &(this->D3DInfo.indices.front()), this->D3DInfo.indices.size(), &(this->D3DInfo.pIndexBuffer), error ))
	{
		throw std::exception(CHL::ToString(error).c_str());
	}
}

void BasicDrawable::InitInputLayout(ID3D11Device* device)
{
	std::wstring error;
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 16, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 32, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	UINT numElements = ARRAYSIZE( layout );

	if(!DX11Helper::LoadInputLayoutFile(this->D3DInfo.VertexShaderInfo.FileName, 
										this->D3DInfo.VertexShaderInfo.EntryPoint,
										this->D3DInfo.VertexShaderInfo.Model, 
										device, layout, numElements, &(this->D3DInfo.pInputLayout), error))
	{
		throw std::exception(CHL::ToString(error).c_str());
	}
}

void BasicDrawable::InitVertexShader(ID3D11Device* device)
{
	std::wstring error;
	if(!DX11Helper::LoadVertexShaderFile(this->D3DInfo.VertexShaderInfo.FileName, 
										this->D3DInfo.VertexShaderInfo.EntryPoint,
										this->D3DInfo.VertexShaderInfo.Model, 
										device, &(this->D3DInfo.pVertexShader), error))
	{
		throw std::exception(CHL::ToString(error).c_str());
	}
}

void BasicDrawable::InitPixelShader(ID3D11Device* device)
{
	std::wstring error;
	if(!DX11Helper::LoadPixelShaderFile(this->D3DInfo.PixelShaderInfo.FileName, 
										this->D3DInfo.PixelShaderInfo.EntryPoint,
										this->D3DInfo.PixelShaderInfo.Model, 
										device, &(this->D3DInfo.pPixelShader), error))
	{
		throw std::exception(CHL::ToString(error).c_str());
	}
}

void BasicDrawable::InitRastersizerState(ID3D11Device* device)
{
	std::wstring error;
	if(!DX11Helper::LoadRasterizerState(D3D11_CULL_BACK, D3D11_FILL_SOLID, true, true, device, &(this->D3DInfo.pRastersizerState), error))
	{
		throw std::exception(CHL::ToString(error).c_str());
	}
}

void BasicDrawable::InitConstantBuffer(ID3D11Device* device)
{
	std::wstring error;
	if(!DX11Helper::LoadBuffer<cBuffer::cbObjectConstantBuffer>(device, &(this->D3DInfo.pConstantBuffer), error))
	{
		throw std::exception(CHL::ToString(error).c_str());
	}
}

void BasicDrawable::InitTexture(ID3D11Device* device)
{
	std::wstring error;
	if(!DX11Helper::LoadTextureFile(CHL::ToWString(this->D3DInfo.textureFileName), device, &(this->D3DInfo.pTexture), error))
	{
		throw std::exception(CHL::ToString(error).c_str());
	}
}

Drawable* BasicDrawable::clone() const
{
	Drawable* pNewCopy = 0;

	return pNewCopy;
}