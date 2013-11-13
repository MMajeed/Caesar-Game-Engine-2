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
	this->D3DInfo.pConstantBuffer = 0;
	this->D3DInfo.pInputLayout = 0;
	this->D3DInfo.pVertexShader = 0;
	this->D3DInfo.pPixelShader = 0;
	this->D3DInfo.pRastersizerState = 0;
	this->D3DInfo.cullMode = D3D11_CULL_BACK;
	this->D3DInfo.fillMode = D3D11_FILL_SOLID;
	this->D3DInfo.bAntialiasedLine = true;
	this->D3DInfo.bMultisampleEnable = true;
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
}

void BasicDrawable::Destory()
{
	this->D3DInfo.pVertexBuffer->Release();
	this->D3DInfo.pIndexBuffer->Release();
	this->D3DInfo.pConstantBuffer->Release();
	this->D3DInfo.pInputLayout->Release();
	this->D3DInfo.pVertexShader->Release();
	this->D3DInfo.pPixelShader->Release();
	this->D3DInfo.pRastersizerState->Release();
}

void BasicDrawable::Update(double realTime, double deltaTime)
{

}

void BasicDrawable::Draw(TypedefObject::ObjectInfo& object)
{
	this->SetupDrawConstantBuffer(object);
	this->SetupDrawVertexBuffer(object);
	this->SetupDrawInputVertexShader(object);
	this->SetupDrawPixelShader(object);
	this->SetupDrawRasterizeShader(object);
	this->DrawObject(object);
	this->CleanupAfterDraw(object);
}

void BasicDrawable::SetupDrawConstantBuffer(const TypedefObject::ObjectInfo& object)
{
	CHL::Vec4 location;	CHL::Vec4 diffuse;
	CHL::Vec4 rotation;	CHL::Vec4 ambient;
	CHL::Vec4 scale;	CHL::Vec4 spec;

	this->GetInfo(object, location, rotation, scale, diffuse, ambient, spec);	

	CHL::Matrix4x4 mObjectFinal = CHL::ObjectCalculation(location, rotation, scale);

	XMFLOAT4X4 worldMatrix = CHL::Convert4x4(mObjectFinal);
	XMFLOAT4X4 prespectiveMatrix = CHL::Convert4x4(GraphicManager::GetInstance().PrespectiveMatrix);
	XMFLOAT4X4 viewMatrix = CHL::Convert4x4(GraphicManager::GetInstance().CamerMatrix);
	
	XMMATRIX finalMatrix = XMLoadFloat4x4(&prespectiveMatrix) * XMLoadFloat4x4(&viewMatrix) * XMLoadFloat4x4(&worldMatrix);

	cBuffer::cbObject cbCEF;
	
	cbCEF.world = XMLoadFloat4x4(&worldMatrix);
	cbCEF.worldViewProj = finalMatrix;
	cbCEF.colour.diffuse = CHL::ConvertVec4(diffuse);
	cbCEF.colour.ambient = CHL::ConvertVec4(ambient);
	cbCEF.colour.specular = CHL::ConvertVec4(spec);

	ID3D11DeviceContext* pImmediateContext = GraphicManager::GetInstance().direct3d.pImmediateContext;

	pImmediateContext->UpdateSubresource( this->D3DInfo.pConstantBuffer, 0, NULL, &cbCEF, 0, 0 );
	pImmediateContext->VSSetConstantBuffers( 0, 1, &(this->D3DInfo.pConstantBuffer) );
	pImmediateContext->PSSetConstantBuffers( 0, 1, &(this->D3DInfo.pConstantBuffer) );
}
void BasicDrawable::SetupDrawVertexBuffer(const TypedefObject::ObjectInfo& object)
{	
	ID3D11DeviceContext* pImmediateContext = GraphicManager::GetInstance().direct3d.pImmediateContext;

	UINT stride = sizeof( Vertex );
	UINT offset = 0;
	pImmediateContext->IASetVertexBuffers( 0, 1, &this->D3DInfo.pVertexBuffer, &stride, &offset );
	pImmediateContext->IASetIndexBuffer( this->D3DInfo.pIndexBuffer, DXGI_FORMAT_R16_UINT, 0 );
	pImmediateContext->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );	
}
void BasicDrawable::SetupDrawInputVertexShader(const TypedefObject::ObjectInfo& object)
{
	ID3D11DeviceContext* pImmediateContext = GraphicManager::GetInstance().direct3d.pImmediateContext;

	// Set the input layout
	pImmediateContext->IASetInputLayout( this->D3DInfo.pInputLayout );
	pImmediateContext->VSSetShader( this->D3DInfo.pVertexShader, NULL, 0 );
}
void BasicDrawable::SetupDrawPixelShader(const TypedefObject::ObjectInfo& object)
{
	ID3D11DeviceContext* pImmediateContext = GraphicManager::GetInstance().direct3d.pImmediateContext;
	
	pImmediateContext->PSSetShader( this->D3DInfo.pPixelShader, NULL, 0 );	
}
void BasicDrawable::SetupDrawRasterizeShader(const TypedefObject::ObjectInfo& object)
{
	ID3D11DeviceContext* pImmediateContext = GraphicManager::GetInstance().direct3d.pImmediateContext;
	
	pImmediateContext->RSSetState(this->D3DInfo.pRastersizerState);
}
void BasicDrawable::DrawObject(const TypedefObject::ObjectInfo& object)
{
	ID3D11DeviceContext* pImmediateContext = GraphicManager::GetInstance().direct3d.pImmediateContext;

	pImmediateContext->DrawIndexed( this->D3DInfo.indices.size(), 0, 0 );
}
void BasicDrawable::CleanupAfterDraw(const TypedefObject::ObjectInfo& object)	
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

	if(!DX11Helper::LoadIndexBuffer<WORD>(device, &(this->D3DInfo.indices.front()), this->D3DInfo.indices.size(), &(this->D3DInfo.pIndexBuffer), error ))
	{
		throw std::exception(CHL::ToString(error).c_str());
	}
}
void BasicDrawable::InitInputLayout(ID3D11Device* device)
{
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 16, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 32, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	UINT numElements = ARRAYSIZE( layout );

	DX11Helper::LoadInputLayoutFile(this->D3DInfo.VertexShaderInfo.FileName, 
									device, layout, numElements, &(this->D3DInfo.pInputLayout));
}
void BasicDrawable::InitVertexShader(ID3D11Device* device)
{
	DX11Helper::LoadVertexShaderFile(this->D3DInfo.VertexShaderInfo.FileName, 
										device, &(this->D3DInfo.pVertexShader));
}
void BasicDrawable::InitPixelShader(ID3D11Device* device)
{
	DX11Helper::LoadPixelShaderFile(this->D3DInfo.PixelShaderInfo.FileName, 
										device, &(this->D3DInfo.pPixelShader));
}
void BasicDrawable::InitRastersizerState(ID3D11Device* device)
{
	std::wstring error;
	if (!DX11Helper::LoadRasterizerState(this->D3DInfo.cullMode, 
										 this->D3DInfo.fillMode,
										 this->D3DInfo.bAntialiasedLine,
										 this->D3DInfo.bMultisampleEnable, 
										 device, &(this->D3DInfo.pRastersizerState), error))
	{
		throw std::exception(CHL::ToString(error).c_str());
	}
}
void BasicDrawable::InitConstantBuffer(ID3D11Device* device)
{
	std::wstring error;
	if(!DX11Helper::LoadBuffer<cBuffer::cbObject>(device, &(this->D3DInfo.pConstantBuffer), error))
	{
		throw std::exception(CHL::ToString(error).c_str());
	}
}

void BasicDrawable::ChangeRasterizerState(D3D11_CULL_MODE cullMode, D3D11_FILL_MODE fillMode, bool bAntialiasedLine, bool bMultisampleEnable)
{
	this->D3DInfo.cullMode           = cullMode;
	this->D3DInfo.fillMode           = fillMode;
	this->D3DInfo.bAntialiasedLine   = bAntialiasedLine;
	this->D3DInfo.bMultisampleEnable = bMultisampleEnable;

	if (this->D3DInfo.pRastersizerState)
	{
		this->D3DInfo.pRastersizerState->Release();
	}

	ID3D11Device* pDevice = GraphicManager::GetInstance().direct3d.pd3dDevice;
	this->InitRastersizerState(pDevice);
}

std::shared_ptr<BasicDrawable> BasicDrawable::Spawn(const std::string& inputID,
													const std::vector<Vertex>& vectorVertices,
													const std::vector<WORD>&	vectorIndices,
													D3DShaderInfo				vertexFile,
													D3DShaderInfo				pixelFile,
													D3D11_CULL_MODE				cullMode,
													D3D11_FILL_MODE				fillMode,
													bool						bAntialiasedLine,
													bool						bMultisampleEnable)
{
	std::shared_ptr<BasicDrawable> newObject(new BasicDrawable(inputID));

	newObject->D3DInfo.vertices = vectorVertices;
	newObject->D3DInfo.indices = vectorIndices;
	newObject->D3DInfo.VertexShaderInfo = vertexFile;
	newObject->D3DInfo.PixelShaderInfo = pixelFile;
	newObject->D3DInfo.cullMode = cullMode;
	newObject->D3DInfo.fillMode = fillMode;
	newObject->D3DInfo.bAntialiasedLine = bAntialiasedLine;
	newObject->D3DInfo.bMultisampleEnable = bMultisampleEnable;

	newObject->Init();

	return newObject;
}

std::shared_ptr<Drawable> BasicDrawable::clone() const
{
	std::shared_ptr<BasicDrawable> newObject(new BasicDrawable(""));

	return std::dynamic_pointer_cast<Drawable>(newObject);
}

void BasicDrawable::GetInfo(const TypedefObject::ObjectInfo& object,
							CHL::Vec4& location,
							CHL::Vec4& rotation,
							CHL::Vec4& scale,
							CHL::Vec4& diffuse,
							CHL::Vec4& ambient,
							CHL::Vec4& spec)
{	
	TypedefObject::ObjectInfo::const_iterator iterKey;
	iterKey = object.find(Keys::ObjectInfo::LOCATION);
	if(iterKey != object.end())
	{
		location = GenericObj<CHL::Vec4>::GetValue(iterKey->second);
	}
	else
	{
		location(0) = 0.0f; location(1) = 0.0f; location(2) = 0.0f; location(3) = 1.0f; 
	}

	
	iterKey = object.find(Keys::ObjectInfo::ROTATION);
	if(iterKey != object.end())
	{
		rotation = GenericObj<CHL::Vec4>::GetValue(iterKey->second);
	}
	else
	{
		rotation(0) = 0.0f; rotation(1) = 0.0f; rotation(2) = 0.0f; rotation(3) = 0.0f; 
	}

	iterKey = object.find(Keys::ObjectInfo::SCALE);
	if(iterKey != object.end())
	{
		scale = GenericObj<CHL::Vec4>::GetValue(iterKey->second);
	}
	else
	{
		scale(0) = 1.0f; scale(1) = 1.0f; scale(2) = 1.0f; scale(3) = 1.0f; 
	}

	iterKey = object.find(Keys::ObjectInfo::DIFFUSE);
	if(iterKey != object.end())
	{
		diffuse = GenericObj<CHL::Vec4>::GetValue(iterKey->second);
	}
	else
	{
		diffuse(0) = 1.0f; diffuse(1) = 1.0f; diffuse(2) = 1.0f; diffuse(3) = 1.0f; 
	}

	iterKey = object.find(Keys::ObjectInfo::AMBIENT);
	if(iterKey != object.end())
	{
		ambient = GenericObj<CHL::Vec4>::GetValue(iterKey->second);
	}
	else
	{
		ambient(0) = 1.0f; ambient(1) = 1.0f; ambient(2) = 1.0f; ambient(3) = 1.0f; 
	}

	iterKey = object.find(Keys::ObjectInfo::SPECULAR);
	if(iterKey != object.end())
	{
		spec = GenericObj<CHL::Vec4>::GetValue(iterKey->second);
	}
	else
	{
		spec(0) = 1.0f; spec(1) = 1.0f; spec(2) = 1.0f; spec(3) = 1.0f; 
	}
}