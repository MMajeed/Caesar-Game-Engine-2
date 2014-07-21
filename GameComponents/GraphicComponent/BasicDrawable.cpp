#include "BasicDrawable.h"

#include "GraphicManager.h"
#include "DX11Helper.h"
#include "Buffers.h"
#include "XNAConverter.h"
#include "3DMath.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "GeometryShader.h"
#include "ResourceManager.h"
#include "ShaderSetup.h"
#include <Keys.h>
#include <VecOperators.h>
#include <MathFunctions.h>
#include <AnimationCommunicator\AnimationControllerConfig.h>
#include <PhysicsCommunicator\RigidBodyConfig.h>

BasicDrawable::BasicDrawable()
{
	this->D3DInfo.pVertexBuffer = 0;
	this->D3DInfo.pIndexBuffer = 0;
	this->D3DInfo.pInputLayout = 0;
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
	this->InitGeometryShader(device);
	this->InitPixelShader(device);
	this->InitRastersizerState(device);
	this->InitShadowRastersizerState(device);
}

void BasicDrawable::Destory()
{
	this->D3DInfo.pVertexBuffer->Release();
	this->D3DInfo.pIndexBuffer->Release();
	this->D3DInfo.pInputLayout->Release();
	this->D3DInfo.pRastersizerState->Release();
}

void BasicDrawable::Update(double realTime, double deltaTime)
{

}

void BasicDrawable::Draw(std::shared_ptr<ObjectEntity> object, const SceneInfo& si)
{
	if(this->CheckIfValid(object, si))
	{
		this->SetupDepth(object, si);
		this->SetupTexture(object, si);
		this->SetupDrawVertexBuffer(object, si);
		this->SetupDrawInputVertexShader(object, si);
		this->SetupDrawPixelShader(object, si);
		this->SetupDrawGeometryShader(object, si);
		this->SetupDrawRasterizeShader(object, si);
		this->DrawObject(object, si);
		this->CleanupAfterDraw(object, si);
	}
}
void BasicDrawable::DrawShadow(std::shared_ptr<ObjectEntity> object, const SceneInfo& si)
{
	ID3D11DeviceContext* pImmediateContext = GraphicManager::GetInstance().D3DStuff.pImmediateContext;
	
	if(this->CheckIfValid(object, si))
	{
		this->SetupDrawVertexBuffer(object, si);
		this->SetupDrawInputVertexShader(object, si);
		this->SetupDrawPixelShader(object, si);
		this->SetupDrawGeometryShader(object, si);
		pImmediateContext->RSSetState(this->D3DInfo.pShadowRastersizerState);
		this->DrawObject(object, si);
		this->CleanupAfterDraw(object, si);
	}
}

bool BasicDrawable::CheckIfValid(const std::shared_ptr<ObjectEntity>& object, const SceneInfo& si)
{
	if(this->D3DInfo.pVertexBuffer == 0) { return false; }
	if(this->D3DInfo.pIndexBuffer == 0) { return false; }
	if(this->D3DInfo.pInputLayout == 0) { return false; }
	if(this->D3DInfo.pRastersizerState == 0) { return false; }
	return true;
}
void BasicDrawable::SetupDepth(const std::shared_ptr<ObjectEntity>& object, const SceneInfo& si)
{
	GraphicManager& graphic = GraphicManager::GetInstance();

	if(object->GetDepth() == false)
	{
		graphic.D3DStuff.pImmediateContext->OMSetDepthStencilState(graphic.D3DStuff.pDepthDisabledStencilState, 1);
	}
}
void BasicDrawable::SetupTexture(const std::shared_ptr<ObjectEntity>& object, const SceneInfo& si)
{
	GraphicManager& graphic = GraphicManager::GetInstance();
	std::hash_set<std::string> texture2D = object->GetTexture2D();
	if(texture2D.size() > 0)
	{
		ID3D11ShaderResourceView* pTexture[cBuffer::numOfTextures] = {0};

		std::size_t limit = texture2D.size() < cBuffer::numOfTextures ? texture2D.size() : cBuffer::numOfTextures;
		unsigned int i = 0;
		for(auto iter = texture2D.begin();
			iter != texture2D.end();
			++iter)
		{
			std::string textureID = *iter;
			auto texture = ResourceManager::TextureList.Find(textureID);
			if(texture)
			{ 
				pTexture[i] = texture->D3DInfo.pTexture;
				++i;
			}
		}

		graphic.D3DStuff.pImmediateContext->VSSetShaderResources(50, limit, pTexture);
		graphic.D3DStuff.pImmediateContext->GSSetShaderResources(50, limit, pTexture);
		graphic.D3DStuff.pImmediateContext->PSSetShaderResources(50, limit, pTexture);
	}

	std::hash_set<std::string> textureCube = object->GetTextureCube();
	if(textureCube.size() > 0)
	{
		ID3D11ShaderResourceView* pTexture[cBuffer::numOfTextures] = {0};

		std::size_t limit = textureCube.size() < cBuffer::numOfTextures ? textureCube.size() : cBuffer::numOfTextures;
		unsigned int i = 0;
		for(auto iter = texture2D.begin();
			iter != texture2D.end();
			++iter)
		{
			std::string textureID = *iter;
			auto texture = ResourceManager::TextureList.Find(textureID);
			if(texture)
			{
				pTexture[i] = texture->D3DInfo.pTexture;
				++i;
			}
		}
		graphic.D3DStuff.pImmediateContext->VSSetShaderResources(55, limit, pTexture);
		graphic.D3DStuff.pImmediateContext->GSSetShaderResources(55, limit, pTexture);
		graphic.D3DStuff.pImmediateContext->PSSetShaderResources(55, limit, pTexture);
	}
}
void BasicDrawable::SetupDrawVertexBuffer(const std::shared_ptr<ObjectEntity>& object, const SceneInfo& si)
{	
	ID3D11DeviceContext* pImmediateContext = GraphicManager::GetInstance().D3DStuff.pImmediateContext;

	UINT stride = sizeof( Vertex );
	UINT offset = 0;
	pImmediateContext->IASetVertexBuffers( 0, 1, &this->D3DInfo.pVertexBuffer, &stride, &offset );
	pImmediateContext->IASetIndexBuffer( this->D3DInfo.pIndexBuffer, DXGI_FORMAT_R16_UINT, 0 );
	pImmediateContext->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );	
}
void BasicDrawable::SetupDrawInputVertexShader(const std::shared_ptr<ObjectEntity>& object, const SceneInfo& si)
{
	ID3D11DeviceContext* pImmediateContext = GraphicManager::GetInstance().D3DStuff.pImmediateContext;

	// Set the input layout
	pImmediateContext->IASetInputLayout( this->D3DInfo.pInputLayout );
	
	ShaderSetup::SetupVertexShader(this->D3DInfo.vertexShaderID, object, si);
}
void BasicDrawable::SetupDrawPixelShader(const std::shared_ptr<ObjectEntity>& object, const SceneInfo& si)
{
	ShaderSetup::SetupPixelShader(this->D3DInfo.pixelShaderID, object, si);
}
void BasicDrawable::SetupDrawGeometryShader(const std::shared_ptr<ObjectEntity>& object, const SceneInfo& si)
{
	ShaderSetup::SetupGeometryShader(this->D3DInfo.geometryShaderID, object, si);
}
void BasicDrawable::SetupDrawRasterizeShader(const std::shared_ptr<ObjectEntity>& object, const SceneInfo& si)
{
	ID3D11DeviceContext* pImmediateContext = GraphicManager::GetInstance().D3DStuff.pImmediateContext;
	
	pImmediateContext->RSSetState(this->D3DInfo.pRastersizerState);
}
void BasicDrawable::DrawObject(const std::shared_ptr<ObjectEntity>& object, const SceneInfo& si)
{
	ID3D11DeviceContext* pImmediateContext = GraphicManager::GetInstance().D3DStuff.pImmediateContext;

	pImmediateContext->DrawIndexed( this->D3DInfo.indices.size(), 0, 0 );
}
void BasicDrawable::CleanupAfterDraw(const std::shared_ptr<ObjectEntity>& object, const SceneInfo& si)
{
	GraphicManager& graphic = GraphicManager::GetInstance();

	if(object->GetDepth() == false)
	{
		graphic.D3DStuff.pImmediateContext->OMSetDepthStencilState(graphic.D3DStuff.pDepthStencilState, 1);
	}
}

void BasicDrawable::InitVertexBuffer(ID3D11Device* device)
{
	if(this->D3DInfo.vertices.size() > 0)
	{
		DX11Helper::LoadVertexBuffer<Vertex>(device, this->D3DInfo.vertices.data(), this->D3DInfo.vertices.size(), &(this->D3DInfo.pVertexBuffer));
	}
}
void BasicDrawable::InitIndexBuffer(ID3D11Device* device)
{
	if(this->D3DInfo.indices.size() > 0)
	{
		DX11Helper::LoadIndexBuffer<WORD>(device, this->D3DInfo.indices.data(), this->D3DInfo.indices.size(), &(this->D3DInfo.pIndexBuffer));
	}
}
void BasicDrawable::InitInputLayout(ID3D11Device* device)
{
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"NORMAL", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 16, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 32, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};
	UINT numElements = ARRAYSIZE(layout);

	// Now pass this compiled vertex shader to the device so it can be used
	HRESULT hr = device->CreateInputLayout(layout, numElements, 
										   this->D3DInfo.vertexShaderBytes.data(), this->D3DInfo.vertexShaderBytes.size(),
										   &(this->D3DInfo.pInputLayout));

	// NOTE: DON'T Release the VSblob yet as it's needed for the vertex layout...
	if(FAILED(hr))
	{
		Logger::LogError("ErrorException: Could not assign compiled vertex shader to device.");
	}	
}
void BasicDrawable::InitVertexShader(ID3D11Device* device)
{
	//this->D3DInfo.vertexShader = VertexShader::Spawn(this->D3DInfo.vertexShaderBytes);
}
void BasicDrawable::InitGeometryShader(ID3D11Device* device)
{
	//this->D3DInfo.geometryShader = GeometryShader::Spawn(this->D3DInfo.geometryShaderBytes);
}
void BasicDrawable::InitPixelShader(ID3D11Device* device)
{
	//this->D3DInfo.pixelShader = PixelShader::Spawn(this->D3DInfo.pixelShaderBytes);
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

	if (this->D3DInfo.pRastersizerState != 0)
	{
		this->D3DInfo.pRastersizerState->Release();
	}

	ID3D11Device* pDevice = GraphicManager::GetInstance().D3DStuff.pd3dDevice;
	this->InitRastersizerState(pDevice);
}

void BasicDrawable::ProcessModel(std::shared_ptr<CHL::Model> model)
{
	std::vector<unsigned int>& vectorFaces = model->Faces;
	this->D3DInfo.indices.clear();
	this->D3DInfo.indices.reserve(vectorFaces.size());
	for(std::size_t i = 0; i < vectorFaces.size(); ++i)
	{
		this->D3DInfo.indices.push_back((WORD)vectorFaces[i]);
	}

	std::vector<CHL::Model::VerticesInfo>& modelVertices = model->Vertices;
	this->D3DInfo.vertices.clear();
	this->D3DInfo.vertices.reserve(modelVertices.size());

	for(std::size_t i = 0; i < modelVertices.size(); ++i)
	{
		Vertex v;
		auto ver = modelVertices[i];
		v.Pos = XMFLOAT4((float)ver.Point(0), (float)ver.Point(1), (float)ver.Point(2), 1.0);
		v.Normal = XMFLOAT4((float)ver.Normal(0), (float)ver.Normal(1), (float)ver.Normal(2), 1.0);
		v.Texture = XMFLOAT3((float)ver.Texture(0), (float)ver.Texture(1), (float)ver.Texture(2));

		this->D3DInfo.vertices.push_back(v);
	}
}

void BasicDrawable::ChangeModel(std::shared_ptr<CHL::Model> model)
{
	this->ProcessModel(model);
	if(this->D3DInfo.pVertexBuffer != 0)
	{
		this->D3DInfo.pVertexBuffer->Release();
	}
	if(this->D3DInfo.pIndexBuffer != 0)
	{
		this->D3DInfo.pIndexBuffer->Release();
	}

	ID3D11Device* pDevice = GraphicManager::GetInstance().D3DStuff.pd3dDevice;
	this->InitVertexBuffer(pDevice);
	this->InitIndexBuffer(pDevice);
}

void BasicDrawable::ChangeVS(std::string fileName)
{
	/*GraphicManager& graphic = GraphicManager::GetInstance();

	if(this->D3DInfo.pVertexShader != 0)
	{
		this->D3DInfo.pVertexShader->Release();
	}
	this->D3DInfo.VertexShaderFileName = fileName;
	this->InitVertexShader(graphic.D3DStuff.pd3dDevice);*/
}
void BasicDrawable::ChangePS(std::string fileName)
{
	/*GraphicManager& graphic = GraphicManager::GetInstance();

	if(this->D3DInfo.pPixelShader != 0)
	{
		this->D3DInfo.pPixelShader->Release();
	}
	this->D3DInfo.PixelShaderFileName = fileName;
	this->InitPixelShader(graphic.D3DStuff.pd3dDevice);*/
}
void BasicDrawable::ChangeGS(std::string fileName)
{
	/*GraphicManager& graphic = GraphicManager::GetInstance();

	if(this->D3DInfo.pGeometryShader != 0)
	{
		this->D3DInfo.pGeometryShader->Release();
	}
	this->D3DInfo.GeometryShaderFileName = fileName;
	this->InitGeometryShader(graphic.D3DStuff.pd3dDevice);*/
}

std::shared_ptr<BasicDrawable> BasicDrawable::Spawn(std::shared_ptr<CHL::Model>	model,
													const std::string&			vertexFile,
													const std::string&			pixelFile,
													const std::string&			geometryFile,
													D3D11_CULL_MODE				cullMode,
													D3D11_FILL_MODE				fillMode)
{
	std::shared_ptr<BasicDrawable> newObject(new BasicDrawable());

	newObject->ProcessModel(model);

	if(vertexFile.empty() == false)
		DX11Helper::LoadShaderFile(vertexFile, "VS", "vs_4_0", newObject->D3DInfo.vertexShaderBytes);
	if(pixelFile.empty() == false)
		DX11Helper::LoadShaderFile(pixelFile, "PS", "ps_4_0", newObject->D3DInfo.pixelShaderBytes);
	if(geometryFile.empty() == false)
		DX11Helper::LoadShaderFile(geometryFile, "GS", "gs_4_0", newObject->D3DInfo.geometryShaderBytes);

	newObject->D3DInfo.cullMode = cullMode;
	newObject->D3DInfo.fillMode = fillMode;

	newObject->Init();

	return newObject;
}

std::shared_ptr<Drawable> BasicDrawable::clone() const
{
	std::shared_ptr<BasicDrawable> newObject(new BasicDrawable());

	return std::dynamic_pointer_cast<Drawable>(newObject);
}
