#include <Converter.h>

#include "BasicDrawable.h"
#include "GraphicManager.h"
#include "DX11Helper.h"
#include "Buffers.h"
#include "BasicObject.h"
#include "ObjectManager.h"
#include "MatrixConverter.h"

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

void BasicDrawable::Draw(std::shared_ptr<Object> object)
{
	this->SetupDrawConstantBuffer(object);
	this->SetupDrawVertexBuffer(object);
	this->SetupDrawInputVertexShader(object);
	this->SetupDrawPixelShader(object);
	this->SetupDrawRasterizeShader(object);
	this->SetupDrawTexture(object);
}

void BasicDrawable::SetupDrawConstantBuffer(std::shared_ptr<Object> object)
{
	std::shared_ptr<BasicObject> basicObject = BasicObject::ConvertObjectPtr(object);

	auto m = basicObject->GetWorldLocation(GraphicManager::GetInstance().GetCameraView(), GraphicManager::GetInstance().GetPrespective() );
	XMFLOAT4X4 finalMatrix = MatrixConverter::Convert4x4(m);

	cBuffer::cbObjectConstantBuffer cbCEF;

	cbCEF.finalMatrix = XMLoadFloat4x4(&finalMatrix);
	cbCEF.colour.diffuse = MatrixConverter::ConvertVec4(basicObject->Colour());
	cbCEF.colour.ambient = MatrixConverter::ConvertVec4(basicObject->Colour());
	cbCEF.colour.spec = MatrixConverter::ConvertVec4(basicObject->Colour());

	ID3D11DeviceContext* pImmediateContext = GraphicManager::GetInstance().direct3d.pImmediateContext;

	pImmediateContext->UpdateSubresource( this->D3DInfo.pConstantBuffer, 0, NULL, &cbCEF, 0, 0 );
	pImmediateContext->VSSetConstantBuffers( 2, 1, &(this->D3DInfo.pConstantBuffer) );
	pImmediateContext->PSSetConstantBuffers( 2, 1, &(this->D3DInfo.pConstantBuffer) );
}
void BasicDrawable::SetupDrawVertexBuffer(std::shared_ptr<Object> object)
{	
	ID3D11DeviceContext* pImmediateContext = GraphicManager::GetInstance().direct3d.pImmediateContext;

	UINT stride = sizeof( Vertex );
	UINT offset = 0;
	pImmediateContext->IASetVertexBuffers( 0, 1, &this->D3DInfo.pVertexBuffer, &stride, &offset );
	pImmediateContext->IASetIndexBuffer( this->D3DInfo.pIndexBuffer, DXGI_FORMAT_R16_UINT, 0 );
	pImmediateContext->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );	
}
void BasicDrawable::SetupDrawInputVertexShader(std::shared_ptr<Object> object)
{
	ID3D11DeviceContext* pImmediateContext = GraphicManager::GetInstance().direct3d.pImmediateContext;

	// Set the input layout
	pImmediateContext->IASetInputLayout( this->D3DInfo.pInputLayout );
	pImmediateContext->VSSetShader( this->D3DInfo.pVertexShader, NULL, 0 );
}
void BasicDrawable::SetupDrawPixelShader(std::shared_ptr<Object> object)
{
	ID3D11DeviceContext* pImmediateContext = GraphicManager::GetInstance().direct3d.pImmediateContext;
	
	pImmediateContext->PSSetShader( this->D3DInfo.pPixelShader, NULL, 0 );	
}
void BasicDrawable::SetupDrawRasterizeShader(std::shared_ptr<Object> object)
{
	ID3D11DeviceContext* pImmediateContext = GraphicManager::GetInstance().direct3d.pImmediateContext;
	
	pImmediateContext->RSSetState(this->D3DInfo.pRastersizerState);
}
void BasicDrawable::SetupDrawTexture(std::shared_ptr<Object> object)
{
	ID3D11DeviceContext* pImmediateContext = GraphicManager::GetInstance().direct3d.pImmediateContext;

	pImmediateContext->PSSetShaderResources( 0, 1, &(this->D3DInfo.pTexture) );
}
void BasicDrawable::DrawObject(std::shared_ptr<Object> object)
{
	ID3D11DeviceContext* pImmediateContext = GraphicManager::GetInstance().direct3d.pImmediateContext;

	pImmediateContext->DrawIndexed( this->D3DInfo.indices.size(), 0, 0 );
}
void BasicDrawable::CleanupAfterDraw(std::shared_ptr<Object> object)	
{
	ID3D11DeviceContext* pImmediateContext = GraphicManager::GetInstance().direct3d.pImmediateContext;

	ID3D11ShaderResourceView* tab = NULL;

	pImmediateContext->PSSetShaderResources(0,1,&tab);
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