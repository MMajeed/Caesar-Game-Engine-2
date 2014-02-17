#include "BasicDrawable.h"

#include "GraphicManager.h"
#include "DX11Helper.h"
#include "Buffers.h"
#include "XNAConverter.h"
#include <Keys.h>
#include "3DMath.h"
#include <VecOperators.h>
#include <MathFunctions.h>
#include <AnimationCommunicator\AnimationControllerConfig.h>
#include <PhysicsCommunicator\RigidBodyConfig.h>

BasicDrawable::BasicDrawable()
{
	this->D3DInfo.pVertexBuffer = 0;
	this->D3DInfo.pIndexBuffer = 0;
	this->D3DInfo.pInputLayout = 0;
	this->D3DInfo.pVertexShader = 0;
	this->D3DInfo.pPixelShader = 0;
	this->D3DInfo.pGeometryShader = 0;
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
	this->D3DInfo.pVertexShader->Release();
	this->D3DInfo.pPixelShader->Release();
	this->D3DInfo.pRastersizerState->Release();
}

void BasicDrawable::Update(double realTime, double deltaTime)
{

}

void BasicDrawable::Draw(std::shared_ptr<ObjectINFO> object, const SceneInfo& si)
{
	if(this->CheckIfValid(object, si))
	{
		this->SetupDepth(object, si);
		this->SetupTexture(object, si);
		this->SetupDrawConstantBuffer(object, si);
		this->SetupDrawVertexBuffer(object, si);
		this->SetupDrawInputVertexShader(object, si);
		this->SetupDrawPixelShader(object, si);
		this->SetupDrawGeometryShader(object, si);
		this->SetupDrawRasterizeShader(object, si);
		this->DrawObject(object, si);
		this->CleanupAfterDraw(object, si);
	}
}
void BasicDrawable::DrawShadow(std::shared_ptr<ObjectINFO> object, const SceneInfo& si)
{
	ID3D11DeviceContext* pImmediateContext = GraphicManager::GetInstance().D3DStuff.pImmediateContext;
	
	if(this->CheckIfValid(object, si))
	{
		this->SetupDrawConstantBuffer(object, si);
		this->SetupDrawVertexBuffer(object, si);
		this->SetupDrawInputVertexShader(object, si);
		this->SetupDrawPixelShader(object, si);
		this->SetupDrawGeometryShader(object, si);
		pImmediateContext->RSSetState(this->D3DInfo.pShadowRastersizerState);
		this->DrawObject(object, si);
		this->CleanupAfterDraw(object, si);
	}
}

bool BasicDrawable::CheckIfValid(const std::shared_ptr<ObjectINFO>& object, const SceneInfo& si)
{
	if(this->D3DInfo.pVertexBuffer == 0) { return false; }
	if(this->D3DInfo.pIndexBuffer == 0) { return false; }
	if(this->D3DInfo.pInputLayout == 0) { return false; }
	if(this->D3DInfo.pVertexShader == 0) { return false; }
	if(this->D3DInfo.pPixelShader == 0) { return false; }
	if(this->D3DInfo.pRastersizerState == 0) { return false; }
	return true;
}
void BasicDrawable::SetupDepth(const std::shared_ptr<ObjectINFO>& object, const SceneInfo& si)
{
	GraphicManager& graphic = GraphicManager::GetInstance();

	if(object->Depth == false)
	{
		graphic.D3DStuff.pImmediateContext->OMSetDepthStencilState(graphic.D3DStuff.pDepthDisabledStencilState, 1);
	}
}
void BasicDrawable::SetupTexture(const std::shared_ptr<ObjectINFO>& object, const SceneInfo& si)
{
	GraphicManager& graphic = GraphicManager::GetInstance();
	if(object->Texture2DVecs.size() > 0)
	{
		ID3D11ShaderResourceView* pTexture[cBuffer::numOfTextures] = {0};

		std::size_t limit = object->Texture2DVecs.size() < cBuffer::numOfTextures ? object->Texture2DVecs.size() : cBuffer::numOfTextures;
		for(std::size_t i = 0; i < limit; ++i)
		{
			std::string textureID = object->Texture2DVecs[i];
			auto textureIter = graphic.textures.find(textureID);
			if(textureIter != graphic.textures.end()) 
			{ 
				pTexture[i] = textureIter->second->D3DInfo.pTexture;
			}
		}

		graphic.D3DStuff.pImmediateContext->VSSetShaderResources(50, limit, pTexture);
		graphic.D3DStuff.pImmediateContext->GSSetShaderResources(50, limit, pTexture);
		graphic.D3DStuff.pImmediateContext->PSSetShaderResources(50, limit, pTexture);
	}
	if(object->TextureCubeVecs.size() > 0)
	{
		ID3D11ShaderResourceView* pTexture[cBuffer::numOfTextures] = {0};

		std::size_t limit = object->TextureCubeVecs.size() < cBuffer::numOfTextures ? object->TextureCubeVecs.size() : cBuffer::numOfTextures;
		for(std::size_t i = 0; i < limit; ++i)
		{
			std::string textureID = object->TextureCubeVecs[i];
			auto textureIter = graphic.textures.find(textureID);
			if(textureIter != graphic.textures.end())
			{
				pTexture[i] = textureIter->second->D3DInfo.pTexture;
			}
		}
		graphic.D3DStuff.pImmediateContext->VSSetShaderResources(55, limit, pTexture);
		graphic.D3DStuff.pImmediateContext->GSSetShaderResources(55, limit, pTexture);
		graphic.D3DStuff.pImmediateContext->PSSetShaderResources(55, limit, pTexture);
	}
}
void BasicDrawable::SetupDrawConstantBuffer(const std::shared_ptr<ObjectINFO>& object, const SceneInfo& si)
{
	XMFLOAT4X4 worldFloat4x4; XMFLOAT4X4 finalFloat4x4;
	this->CalculateWVP(object, si, worldFloat4x4, finalFloat4x4);
	cBuffer::cbObject cbCEF;
	
	cbCEF.world = XMMatrixTranspose(XMLoadFloat4x4(&worldFloat4x4));
	cbCEF.worldViewProj = XMMatrixTranspose(XMLoadFloat4x4(&finalFloat4x4));
	cbCEF.colour.diffuse = ConvertVec4(object->Diffuse);
	cbCEF.colour.ambient = ConvertVec4(object->Ambient);
	cbCEF.colour.specular = ConvertVec4(object->Specular);
	cbCEF.NumberOf2DTextures = object->Texture2DVecs.size() < cBuffer::numOfTextures ? object->Texture2DVecs.size() : cBuffer::numOfTextures;
	cbCEF.NumberOfCubeTextures = object->TextureCubeVecs.size() < cBuffer::numOfTextures ? object->TextureCubeVecs.size() : cBuffer::numOfTextures;
	cbCEF.HasLight = object->Light;

	if(cbCEF.HasLight == false)
	{
		int breakpoint = 0;
	}

	for(unsigned int i = 0; i < 4; ++i)
	{
		int row = i * 4;
		cbCEF.userData(i, 0) = object->UserData[row + 0];
		cbCEF.userData(i, 1) = object->UserData[row + 1];
		cbCEF.userData(i, 2) = object->UserData[row + 2];
		cbCEF.userData(i, 3) = object->UserData[row + 3];
	}

	auto& d3dStuff = GraphicManager::GetInstance().D3DStuff;

	d3dStuff.pImmediateContext->UpdateSubresource(d3dStuff.pCBObject, 0, NULL, &cbCEF, 0, 0);
}
void BasicDrawable::SetupDrawVertexBuffer(const std::shared_ptr<ObjectINFO>& object, const SceneInfo& si)
{	
	ID3D11DeviceContext* pImmediateContext = GraphicManager::GetInstance().D3DStuff.pImmediateContext;

	UINT stride = sizeof( Vertex );
	UINT offset = 0;
	pImmediateContext->IASetVertexBuffers( 0, 1, &this->D3DInfo.pVertexBuffer, &stride, &offset );
	pImmediateContext->IASetIndexBuffer( this->D3DInfo.pIndexBuffer, DXGI_FORMAT_R16_UINT, 0 );
	pImmediateContext->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );	
}
void BasicDrawable::SetupDrawInputVertexShader(const std::shared_ptr<ObjectINFO>& object, const SceneInfo& si)
{
	ID3D11DeviceContext* pImmediateContext = GraphicManager::GetInstance().D3DStuff.pImmediateContext;

	// Set the input layout
	pImmediateContext->IASetInputLayout( this->D3DInfo.pInputLayout );
	pImmediateContext->VSSetShader( this->D3DInfo.pVertexShader, NULL, 0 );
}
void BasicDrawable::SetupDrawPixelShader(const std::shared_ptr<ObjectINFO>& object, const SceneInfo& si)
{
	ID3D11DeviceContext* pImmediateContext = GraphicManager::GetInstance().D3DStuff.pImmediateContext;

	pImmediateContext->PSSetShader(this->D3DInfo.pPixelShader, NULL, 0);
}
void BasicDrawable::SetupDrawGeometryShader(const std::shared_ptr<ObjectINFO>& object, const SceneInfo& si)
{
	ID3D11DeviceContext* pImmediateContext = GraphicManager::GetInstance().D3DStuff.pImmediateContext;

	if(this->D3DInfo.pGeometryShader != 0)
	{
		pImmediateContext->GSSetShader(this->D3DInfo.pGeometryShader, NULL, 0);
	}
	else
	{
		pImmediateContext->GSSetShader(NULL, NULL, 0);
	}
}
void BasicDrawable::SetupDrawRasterizeShader(const std::shared_ptr<ObjectINFO>& object, const SceneInfo& si)
{
	ID3D11DeviceContext* pImmediateContext = GraphicManager::GetInstance().D3DStuff.pImmediateContext;
	
	pImmediateContext->RSSetState(this->D3DInfo.pRastersizerState);
}
void BasicDrawable::DrawObject(const std::shared_ptr<ObjectINFO>& object, const SceneInfo& si)
{
	ID3D11DeviceContext* pImmediateContext = GraphicManager::GetInstance().D3DStuff.pImmediateContext;

	pImmediateContext->DrawIndexed( this->D3DInfo.indices.size(), 0, 0 );
}
void BasicDrawable::CleanupAfterDraw(const std::shared_ptr<ObjectINFO>& object, const SceneInfo& si)
{
	GraphicManager& graphic = GraphicManager::GetInstance();

	if(object->Depth == false)
	{
		graphic.D3DStuff.pImmediateContext->OMSetDepthStencilState(graphic.D3DStuff.pDepthStencilState, 1);
	}
}

void BasicDrawable::CalculateWVP(const std::shared_ptr<ObjectINFO>& object, const SceneInfo& si, XMFLOAT4X4& worldFloat4x4, XMFLOAT4X4& finalFloat4x4)
{
	CML::Matrix4x4 animation; // Identity by default
	if(!object->AnimationJoint.AnimationID.empty() && !object->AnimationJoint.JointName.empty())
	{
		animation = AnimationControllerConfig::GetSingleJoint(object->AnimationJoint.AnimationID, object->AnimationJoint.JointName);
	}

	CML::Matrix4x4 physics; // Identity by default
	if(!object->PhysicsRigidBodyID.empty())
	{
		physics = RigidBodyConfig::GetTranslation(object->PhysicsRigidBodyID);
	}

	CML::Matrix4x4 mObjectFinal = ObjectCalculation(object->Location, object->Rotation, object->Scale);

	XMFLOAT4X4 animation4x4 = Convert4x4(animation);
	XMFLOAT4X4 physics4x4 = Convert4x4(physics);
	worldFloat4x4 = Convert4x4(mObjectFinal);
	XMFLOAT4X4 prespectiveMatrix = Convert4x4(si.ProjectionMatrix);
	XMFLOAT4X4 viewMatrix = Convert4x4(si.CamerMatrix);

	XMMATRIX finalMatrix = XMLoadFloat4x4(&animation4x4) * XMLoadFloat4x4(&worldFloat4x4) * XMLoadFloat4x4(&physics4x4) * XMLoadFloat4x4(&viewMatrix) * XMLoadFloat4x4(&prespectiveMatrix);

	XMStoreFloat4x4(&finalFloat4x4, finalMatrix);
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
	if(this->D3DInfo.VertexShaderFileName.empty() == false)
	{
		D3D11_INPUT_ELEMENT_DESC layout[] =
		{
			{"POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{"NORMAL", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 16, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{"TEXCOORD", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 32, D3D11_INPUT_PER_VERTEX_DATA, 0},
		};
		UINT numElements = ARRAYSIZE(layout);

		DX11Helper::LoadInputLayoutFile(this->D3DInfo.VertexShaderFileName,
										device, layout, numElements, &(this->D3DInfo.pInputLayout));
	}
}
void BasicDrawable::InitVertexShader(ID3D11Device* device)
{
	if(this->D3DInfo.VertexShaderFileName.empty() == false)
	{
		DX11Helper::LoadVertexShaderFile(this->D3DInfo.VertexShaderFileName,
										 device, &(this->D3DInfo.pVertexShader));
	}
}
void BasicDrawable::InitGeometryShader(ID3D11Device* device)
{
	if(this->D3DInfo.GeometryShaderFileName.empty() == false)
	{
		DX11Helper::LoadGeometryShaderFile(this->D3DInfo.GeometryShaderFileName,
										   device, &(this->D3DInfo.pGeometryShader));
	}
}
void BasicDrawable::InitPixelShader(ID3D11Device* device)
{
	if(this->D3DInfo.VertexShaderFileName.empty() == false)
	{
		DX11Helper::LoadPixelShaderFile(this->D3DInfo.PixelShaderFileName,
										device, &(this->D3DInfo.pPixelShader));
	}
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
	GraphicManager& graphic = GraphicManager::GetInstance();

	if(this->D3DInfo.pVertexShader != 0)
	{
		this->D3DInfo.pVertexShader->Release();
	}
	this->D3DInfo.VertexShaderFileName = fileName;
	this->InitVertexShader(graphic.D3DStuff.pd3dDevice);
}
void BasicDrawable::ChangePS(std::string fileName)
{
	GraphicManager& graphic = GraphicManager::GetInstance();

	if(this->D3DInfo.pPixelShader != 0)
	{
		this->D3DInfo.pPixelShader->Release();
	}
	this->D3DInfo.PixelShaderFileName = fileName;
	this->InitPixelShader(graphic.D3DStuff.pd3dDevice);
}
void BasicDrawable::ChangeGS(std::string fileName)
{
	GraphicManager& graphic = GraphicManager::GetInstance();

	if(this->D3DInfo.pGeometryShader != 0)
	{
		this->D3DInfo.pGeometryShader->Release();
	}
	this->D3DInfo.GeometryShaderFileName = fileName;
	this->InitGeometryShader(graphic.D3DStuff.pd3dDevice);
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
	newObject->D3DInfo.VertexShaderFileName = vertexFile;
	newObject->D3DInfo.PixelShaderFileName = pixelFile;
	newObject->D3DInfo.GeometryShaderFileName = geometryFile;
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
