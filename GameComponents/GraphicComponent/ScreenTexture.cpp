#include "ScreenTexture.h"

#include "GraphicManager.h"
#include "DX11Helper.h"

#include "ScreenTextureShaderVS.h"
#include "ScreenTextureShaderPS.h"
#include "3DMath.h"

ScreenTexture::ScreenTexture(){}
ScreenTexture::~ScreenTexture(){}

void ScreenTexture::Init()
{
	ID3D11Device* device = GraphicManager::GetInstance().D3DStuff.pd3dDevice;
	this->InitVertexBuffer(device);
	this->InitIndexBuffer(device);
	this->InitInputLayout(device);
	this->InitVertexShader(device);
	this->InitPixelShader(device);
	this->InitRastersizerState(device);
	this->InitConstantBuffer(device);
}
void ScreenTexture::Destory()
{
	this->D3DInfo.pVertexBuffer->Release();
	this->D3DInfo.pIndexBuffer->Release();
	this->D3DInfo.pInputLayout->Release();
	this->D3DInfo.pVertexShader->Release();
	this->D3DInfo.pPixelShader->Release();
	this->D3DInfo.pRastersizerState->Release();
	this->D3DInfo.pConstantBuffer->Release();
}
void ScreenTexture::Draw(unsigned int width, unsigned int height, std::shared_ptr<BasicTexture> texture)
{
	if(this->CheckIfValid(width, height, texture))
	{
		this->SetupDepth(width, height, texture);
		this->SetupTexture(width, height, texture);
		this->SetupDrawConstantBuffer(width, height, texture);
		this->SetupDrawVertexBuffer(width, height, texture);
		this->SetupDrawInputVertexShader(width, height, texture);
		this->SetupDrawPixelShader(width, height, texture);
		this->SetupDrawGeometryShader(width, height, texture);
		this->SetupDrawRasterizeShader(width, height, texture);
		this->DrawObject(width, height, texture);
		this->CleanupAfterDraw(width, height, texture);
	}
}

std::shared_ptr<ScreenTexture> ScreenTexture::Spawn()
{
	std::shared_ptr<ScreenTexture> newObject(new ScreenTexture());

	newObject->Init();
	
	return newObject;
}

bool ScreenTexture::CheckIfValid(unsigned int width, unsigned int height, std::shared_ptr<BasicTexture> texture)
{

	if(this->D3DInfo.pVertexBuffer == 0) { return false; }
	if(this->D3DInfo.pIndexBuffer == 0) { return false; }
	if(this->D3DInfo.pInputLayout == 0) { return false; }
	if(this->D3DInfo.pVertexShader == 0) { return false; }
	if(this->D3DInfo.pPixelShader == 0) { return false; }
	if(this->D3DInfo.pRastersizerState == 0) { return false; }
	if(this->D3DInfo.pConstantBuffer == 0) { return false; }
	return true;
}
void ScreenTexture::SetupDepth(unsigned int width, unsigned int height, std::shared_ptr<BasicTexture> texture)
{
	GraphicManager& graphic = GraphicManager::GetInstance();

	graphic.D3DStuff.pImmediateContext->OMSetDepthStencilState(graphic.D3DStuff.pDepthStencilState, 1);
}
void ScreenTexture::SetupTexture(unsigned int width, unsigned int height, std::shared_ptr<BasicTexture> texture)
{
	GraphicManager& graphic = GraphicManager::GetInstance();

	graphic.D3DStuff.pImmediateContext->PSSetShaderResources(0, 1, &texture->D3DInfo.pTexture);
}
void ScreenTexture::SetupDrawConstantBuffer(unsigned int width, unsigned int height, std::shared_ptr<BasicTexture> texture)
{
	GraphicManager& graphic = GraphicManager::GetInstance();
	
	XMMATRIX xmTranslate = XMMatrixTranslation(width * -0.5f, height * -0.5f, 0.0);;
	XMMATRIX xmScaling = XMMatrixScaling((float)width, (float)height, 0);
	XMMATRIX world = XMMatrixMultiply(xmScaling, xmTranslate);

	XMVECTOR Eye = XMVectorSet(0.0f, 0.0f, 10.0f, 0.0f);
	XMVECTOR At = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	XMVECTOR Up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	XMMATRIX view = XMMatrixLookAtLH(Eye, At, Up);

	XMMATRIX proj = XMMatrixOrthographicLH((float)width, (float)height, 0.1f, 1000.0f);
	
	ScreenTexture::ScreenTextureConstantBuffer cb;
	cb.WVP = XMMatrixTranspose(world * view * proj);
	 
	graphic.D3DStuff.pImmediateContext->UpdateSubresource(this->D3DInfo.pConstantBuffer, 0, NULL, &cb, 0, 0);

	graphic.D3DStuff.pImmediateContext->VSSetConstantBuffers(0, 1, &(this->D3DInfo.pConstantBuffer));
	graphic.D3DStuff.pImmediateContext->PSSetConstantBuffers(0, 1, &(this->D3DInfo.pConstantBuffer));
}
void ScreenTexture::SetupDrawVertexBuffer(unsigned int width, unsigned int height, std::shared_ptr<BasicTexture> texture)
{
	ID3D11DeviceContext* pImmediateContext = GraphicManager::GetInstance().D3DStuff.pImmediateContext;

	UINT stride = sizeof(ScreenTexture::ScreenTextureVertex);
	UINT offset = 0;
	pImmediateContext->IASetVertexBuffers(0, 1, &this->D3DInfo.pVertexBuffer, &stride, &offset);
	pImmediateContext->IASetIndexBuffer(this->D3DInfo.pIndexBuffer, DXGI_FORMAT_R16_UINT, 0);
	pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}
void ScreenTexture::SetupDrawInputVertexShader(unsigned int width, unsigned int height, std::shared_ptr<BasicTexture> texture)
{
	ID3D11DeviceContext* pImmediateContext = GraphicManager::GetInstance().D3DStuff.pImmediateContext;

	// Set the input layout
	pImmediateContext->IASetInputLayout(this->D3DInfo.pInputLayout);
	pImmediateContext->VSSetShader(this->D3DInfo.pVertexShader, NULL, 0);
}
void ScreenTexture::SetupDrawPixelShader(unsigned int width, unsigned int height, std::shared_ptr<BasicTexture> texture)
{
	ID3D11DeviceContext* pImmediateContext = GraphicManager::GetInstance().D3DStuff.pImmediateContext;

	pImmediateContext->PSSetShader(this->D3DInfo.pPixelShader, NULL, 0);
}
void ScreenTexture::SetupDrawGeometryShader(unsigned int width, unsigned int height, std::shared_ptr<BasicTexture> texture)
{
	ID3D11DeviceContext* pImmediateContext = GraphicManager::GetInstance().D3DStuff.pImmediateContext;
	
	pImmediateContext->GSSetShader(NULL, NULL, 0);
}
void ScreenTexture::SetupDrawRasterizeShader(unsigned int width, unsigned int height, std::shared_ptr<BasicTexture> texture)
{
	ID3D11DeviceContext* pImmediateContext = GraphicManager::GetInstance().D3DStuff.pImmediateContext;

	pImmediateContext->RSSetState(this->D3DInfo.pRastersizerState);
}
void ScreenTexture::DrawObject(unsigned int width, unsigned int height, std::shared_ptr<BasicTexture> texture)
{
	ID3D11DeviceContext* pImmediateContext = GraphicManager::GetInstance().D3DStuff.pImmediateContext;

	pImmediateContext->DrawIndexed(this->D3DInfo.indices.size(), 0, 0);
}
void ScreenTexture::CleanupAfterDraw(unsigned int width, unsigned int height, std::shared_ptr<BasicTexture> texture)
{
}

void ScreenTexture::InitVertexBuffer(ID3D11Device* device)
{
	this->D3DInfo.vertices = {
		{XMFLOAT3(0.0, 0.0, 0.0), XMFLOAT2(0.0, 0.0)},
		{XMFLOAT3(1.0, 1.0, 0.0), XMFLOAT2(1.0, 1.0)},
		{XMFLOAT3(0.0, 1.0, 0.0), XMFLOAT2(0.0, 1.0)},
		{XMFLOAT3(1.0, 0.0, 0.0), XMFLOAT2(1.0, 0.0)},
	};

	DX11Helper::LoadVertexBuffer<ScreenTexture::ScreenTextureVertex>
		(device, this->D3DInfo.vertices.data(), this->D3DInfo.vertices.size(), &(this->D3DInfo.pVertexBuffer));
}
void ScreenTexture::InitIndexBuffer(ID3D11Device* device)
{
	this->D3DInfo.indices = {
        0, 1, 2,
        0, 3, 1
    };

	DX11Helper::LoadIndexBuffer<WORD>(device, this->D3DInfo.indices.data(), this->D3DInfo.indices.size(), &(this->D3DInfo.pIndexBuffer));
}
void ScreenTexture::InitInputLayout(ID3D11Device* device)
{
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};
	UINT numElements = ARRAYSIZE(layout);

	HRESULT hr = device->CreateInputLayout(
						layout, 
						numElements, 
						ScreenTextureShaderVS.data(), 
						ScreenTextureShaderVS.size(), 
						&this->D3DInfo.pInputLayout);

	if(FAILED(hr))
	{
		Logger::LogError("ErrorException: Could not assign compiled vertex shader to device.");
	}
}
void ScreenTexture::InitVertexShader(ID3D11Device* device)
{
	HRESULT hr = device->CreateVertexShader(ScreenTextureShaderVS.data(), 
											ScreenTextureShaderVS.size(), 
											NULL, 
											&this->D3DInfo.pVertexShader);

	if(FAILED(hr))
	{
		Logger::LogError("ErrorException: Could not assign compiled vertex shader to device.");
	}
}
void ScreenTexture::InitPixelShader(ID3D11Device* device)
{
	HRESULT hr = device->CreatePixelShader(ScreenTextureShaderPS.data(),
										   ScreenTextureShaderPS.size(),
										   NULL,
										   &this->D3DInfo.pPixelShader);

	if(FAILED(hr))
	{
		Logger::LogError("ErrorException: Could not assign compiled vertex shader to device.");
	}
}
void ScreenTexture::InitRastersizerState(ID3D11Device* device)
{
	DX11Helper::LoadRasterizerState(D3D11_CULL_BACK,
									D3D11_FILL_SOLID,
									true,
									true,
									device, &(this->D3DInfo.pRastersizerState));
}
void ScreenTexture::InitConstantBuffer(ID3D11Device* device)
{
	DX11Helper::LoadBuffer<ScreenTexture::ScreenTextureConstantBuffer>(device, &(this->D3DInfo.pConstantBuffer));
}