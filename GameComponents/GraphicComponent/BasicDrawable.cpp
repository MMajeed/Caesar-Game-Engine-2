#include "BasicDrawable.h"

#include <boost/numeric/ublas/io.hpp>
#include <boost/lexical_cast.hpp>
#include <Converter.h>

#include "GraphicManager.h"
#include "DX11Helper.h"
#include "Buffers.h"
#include <XNAConverter.h>
#include <Keys.h>
#include <3DMath.h>

BasicDrawable::BasicDrawable(const std::string& inputID)
	: Drawable(inputID)
{
	this->D3DInfo.pVertexBuffer = 0;
	this->D3DInfo.pIndexBuffer = 0;
	this->D3DInfo.pInputLayout = 0;
	this->D3DInfo.pVertexShader = 0;
	this->D3DInfo.pPixelShader = 0;
	this->D3DInfo.pRastersizerState = 0;
	this->D3DInfo.cullMode = D3D11_CULL_BACK;
	this->D3DInfo.fillMode = D3D11_FILL_SOLID;
}

void BasicDrawable::Init()
{
	ID3D11Device* device = GraphicManager::GetInstance().D3DStuff.pd3dDevice;
	this->InitVertexBuffer(device);
	this->InitIndexBuffer(device);
	this->InitInputLayout(device);
	this->InitVertexShader(device);
	this->InitPixelShader(device);
	this->InitRastersizerState(device);
	this->InitShadowRastersizerState(device);
}

void BasicDrawable::Destory()
{
	this->D3DInfo.pVertexBuffer->Release();
	this->D3DInfo.pIndexBuffer->Release();
	this->D3DInfo.pInputLayout->Release();
	this->D3DInfo.pVertexShader->Release();
	this->D3DInfo.pPixelShader->Release();
	this->D3DInfo.pRastersizerState->Release();
}

void BasicDrawable::Update(double realTime, double deltaTime)
{

}

void BasicDrawable::Draw(std::shared_ptr<ObjectINFO> object)
{
	this->SetupDepth(object);
	this->SetupTexture(object);
	this->SetupDrawConstantBuffer(object);
	this->SetupDrawVertexBuffer(object);
	this->SetupDrawInputVertexShader(object);
	this->SetupDrawPixelShader(object);
	this->SetupDrawRasterizeShader(object);
	this->DrawObject(object);
	this->CleanupTexture(object);
	this->CleanupAfterDraw(object);
}
void BasicDrawable::DrawShadow(std::shared_ptr<ObjectINFO> object)
{
	ID3D11DeviceContext* pImmediateContext = GraphicManager::GetInstance().D3DStuff.pImmediateContext;

	this->SetupDepth(object);
	this->SetupTexture(object);
	this->SetupDrawConstantBuffer(object);
	this->SetupDrawVertexBuffer(object);
	this->SetupDrawInputVertexShader(object);
	this->SetupDrawPixelShader(object);	
	pImmediateContext->RSSetState(this->D3DInfo.pShadowRastersizerState);	
	this->DrawObject(object);
	this->CleanupTexture(object);
	this->CleanupAfterDraw(object);
}

void BasicDrawable::SetupDepth(const std::shared_ptr<ObjectINFO>& object)
{
	GraphicManager& graphic = GraphicManager::GetInstance();

	if(object->Depth == false)
	{
		graphic.D3DStuff.pImmediateContext->OMSetDepthStencilState(graphic.D3DStuff.pDepthDisabledStencilState, 1);
	}
}
void BasicDrawable::SetupTexture(const std::shared_ptr<ObjectINFO>& object)
{
	GraphicManager& graphic = GraphicManager::GetInstance();
	{
		ID3D11ShaderResourceView* pTexture[cBuffer::numOfTextures] = {0};

		unsigned int counter = 0;
		for(std::size_t i = 0; i < object->Texture2DVecs.size() && i < cBuffer::numOfTextures; ++i)
		{
			std::string textureID = object->Texture2DVecs[i];
			auto textureIter = graphic.textures.find(textureID);
			if(textureIter != graphic.textures.end()) 
			{ 
				pTexture[i] = textureIter->second->D3DInfo.pTexture;
			}
		}

		graphic.D3DStuff.pImmediateContext->PSSetShaderResources(0, cBuffer::numOfTextures, pTexture);
	}
	{
		ID3D11ShaderResourceView* pTexture[cBuffer::numOfTextures] = {0};

		unsigned int counter = 0;
		for(std::size_t i = 0; i < object->TextureCubeVecs.size() && i < cBuffer::numOfTextures; ++i)
		{
			std::string textureID = object->TextureCubeVecs[i];
			auto textureIter = graphic.textures.find(textureID);
			if(textureIter != graphic.textures.end())
			{
				pTexture[i] = textureIter->second->D3DInfo.pTexture;
			}
		}

		graphic.D3DStuff.pImmediateContext->PSSetShaderResources(10, cBuffer::numOfTextures, pTexture);
	}
}
void BasicDrawable::SetupDrawConstantBuffer(const std::shared_ptr<ObjectINFO>& object)
{
	CHL::Matrix4x4 mObjectFinal = CHL::ObjectCalculation(object->Location, object->Rotation, object->Scale);

	XMFLOAT4X4 worldMatrix = CHL::Convert4x4(mObjectFinal);
	XMFLOAT4X4 prespectiveMatrix = CHL::Convert4x4(GraphicManager::GetInstance().SceneInfo.PrespectiveMatrix);
	XMFLOAT4X4 viewMatrix = CHL::Convert4x4(GraphicManager::GetInstance().SceneInfo.CamerMatrix);
	
	XMMATRIX finalMatrix = XMLoadFloat4x4(&worldMatrix) * XMLoadFloat4x4(&viewMatrix) * XMLoadFloat4x4(&prespectiveMatrix);

	cBuffer::cbObject cbCEF;
	
	cbCEF.world = XMMatrixTranspose(XMLoadFloat4x4(&worldMatrix));
	cbCEF.worldViewProj = XMMatrixTranspose(finalMatrix);
	cbCEF.colour.diffuse = CHL::ConvertVec4(object->Diffuse);
	cbCEF.colour.ambient = CHL::ConvertVec4(object->Ambient);
	cbCEF.colour.specular = CHL::ConvertVec4(object->Specular);
	cbCEF.NumberOf2DTextures = object->Texture2DVecs.size();
	cbCEF.NumberOfCubeTextures = object->TextureCubeVecs.size();
	cbCEF.HasLight = object->Light;

	if(cbCEF.HasLight == false)
	{
		int breakpoint = 0;
	}

	auto d3dStuff = GraphicManager::GetInstance().D3DStuff;

	d3dStuff.pImmediateContext->UpdateSubresource(d3dStuff.pCBObject, 0, NULL, &cbCEF, 0, 0);
}
void BasicDrawable::SetupDrawVertexBuffer(const std::shared_ptr<ObjectINFO>& object)
{	
	ID3D11DeviceContext* pImmediateContext = GraphicManager::GetInstance().D3DStuff.pImmediateContext;

	UINT stride = sizeof( Vertex );
	UINT offset = 0;
	pImmediateContext->IASetVertexBuffers( 0, 1, &this->D3DInfo.pVertexBuffer, &stride, &offset );
	pImmediateContext->IASetIndexBuffer( this->D3DInfo.pIndexBuffer, DXGI_FORMAT_R16_UINT, 0 );
	pImmediateContext->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );	
}
void BasicDrawable::SetupDrawInputVertexShader(const std::shared_ptr<ObjectINFO>& object)
{
	ID3D11DeviceContext* pImmediateContext = GraphicManager::GetInstance().D3DStuff.pImmediateContext;

	// Set the input layout
	pImmediateContext->IASetInputLayout( this->D3DInfo.pInputLayout );
	pImmediateContext->VSSetShader( this->D3DInfo.pVertexShader, NULL, 0 );
}
void BasicDrawable::SetupDrawPixelShader(const std::shared_ptr<ObjectINFO>& object)
{
	ID3D11DeviceContext* pImmediateContext = GraphicManager::GetInstance().D3DStuff.pImmediateContext;
	
	pImmediateContext->PSSetShader( this->D3DInfo.pPixelShader, NULL, 0 );	
}
void BasicDrawable::SetupDrawRasterizeShader(const std::shared_ptr<ObjectINFO>& object)
{
	ID3D11DeviceContext* pImmediateContext = GraphicManager::GetInstance().D3DStuff.pImmediateContext;
	
	pImmediateContext->RSSetState(this->D3DInfo.pRastersizerState);
}
void BasicDrawable::DrawObject(const std::shared_ptr<ObjectINFO>& object)
{
	ID3D11DeviceContext* pImmediateContext = GraphicManager::GetInstance().D3DStuff.pImmediateContext;

	pImmediateContext->DrawIndexed( this->D3DInfo.indices.size(), 0, 0 );
}
void BasicDrawable::CleanupTexture(const std::shared_ptr<ObjectINFO>& object)
{
	GraphicManager& graphic = GraphicManager::GetInstance();

	ID3D11ShaderResourceView* pTexture[cBuffer::numOfTextures] = {0};

	graphic.D3DStuff.pImmediateContext->PSSetShaderResources(0, cBuffer::numOfTextures, pTexture);
}
void BasicDrawable::CleanupAfterDraw(const std::shared_ptr<ObjectINFO>& object)	
{
	GraphicManager& graphic = GraphicManager::GetInstance();

	if(object->Depth == false)
	{
		graphic.D3DStuff.pImmediateContext->OMSetDepthStencilState(graphic.D3DStuff.pDepthStencilState, 1);
	}
}

void BasicDrawable::InitVertexBuffer(ID3D11Device* device)
{
	DX11Helper::LoadVertexBuffer<Vertex>(device, &(this->D3DInfo.vertices.front()), this->D3DInfo.vertices.size(), &(this->D3DInfo.pVertexBuffer));
}
void BasicDrawable::InitIndexBuffer(ID3D11Device* device)
{
	DX11Helper::LoadIndexBuffer<WORD>(device, &(this->D3DInfo.indices.front()), this->D3DInfo.indices.size(), &(this->D3DInfo.pIndexBuffer));
}
void BasicDrawable::InitInputLayout(ID3D11Device* device)
{
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 16, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 32, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	UINT numElements = ARRAYSIZE( layout );

	DX11Helper::LoadInputLayoutFile(this->D3DInfo.VertexShaderInfo, 
									device, layout, numElements, &(this->D3DInfo.pInputLayout));
}
void BasicDrawable::InitVertexShader(ID3D11Device* device)
{
	DX11Helper::LoadVertexShaderFile(this->D3DInfo.VertexShaderInfo, 
										device, &(this->D3DInfo.pVertexShader));
}
void BasicDrawable::InitPixelShader(ID3D11Device* device)
{
	DX11Helper::LoadPixelShaderFile(this->D3DInfo.PixelShaderInfo, 
										device, &(this->D3DInfo.pPixelShader));
}
void BasicDrawable::InitRastersizerState(ID3D11Device* device)
{
	DX11Helper::LoadRasterizerState(this->D3DInfo.cullMode, 
									this->D3DInfo.fillMode,
									true,
									true,
									device, &(this->D3DInfo.pRastersizerState));
}
void BasicDrawable::InitShadowRastersizerState(ID3D11Device* device)
{
	DX11Helper::LoadRasterizerState(D3D11_CULL_FRONT,
									D3D11_FILL_SOLID,
									true,
									true,
									device, &(this->D3DInfo.pShadowRastersizerState));
}

void BasicDrawable::ChangeRasterizerState(D3D11_CULL_MODE cullMode, D3D11_FILL_MODE fillMode)
{
	this->D3DInfo.cullMode           = cullMode;
	this->D3DInfo.fillMode           = fillMode;

	if (this->D3DInfo.pRastersizerState)
	{
		this->D3DInfo.pRastersizerState->Release();
	}

	ID3D11Device* pDevice = GraphicManager::GetInstance().D3DStuff.pd3dDevice;
	this->InitRastersizerState(pDevice);
}

std::shared_ptr<BasicDrawable> BasicDrawable::Spawn(const std::string& inputID,
													const std::vector<Vertex>&	vectorVertices,
													const std::vector<WORD>&	vectorIndices,
													const std::string&			vertexFile,
													const std::string&			pixelFile,
													D3D11_CULL_MODE				cullMode,
													D3D11_FILL_MODE				fillMode)
{
	std::shared_ptr<BasicDrawable> newObject(new BasicDrawable(inputID));

	newObject->D3DInfo.vertices = vectorVertices;
	newObject->D3DInfo.indices = vectorIndices;
	newObject->D3DInfo.VertexShaderInfo = vertexFile;
	newObject->D3DInfo.PixelShaderInfo = pixelFile;
	newObject->D3DInfo.cullMode = cullMode;
	newObject->D3DInfo.fillMode = fillMode;

	newObject->Init();

	return newObject;
}

std::shared_ptr<Drawable> BasicDrawable::clone() const
{
	std::shared_ptr<BasicDrawable> newObject(new BasicDrawable(""));

	return std::dynamic_pointer_cast<Drawable>(newObject);
}
