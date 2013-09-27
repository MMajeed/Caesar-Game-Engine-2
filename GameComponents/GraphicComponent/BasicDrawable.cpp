#include "BasicDrawable.h"

#include <boost/numeric/ublas/io.hpp>
#include <Converter.h>

#include "GraphicManager.h"
#include "DX11Helper.h"
#include "Buffers.h"
#include <XNAToUblas.h>
#include <Keys.h>
#include <MathOperations.h>

BasicDrawable::BasicDrawable()
{
	this->D3DInfo.pVertexBuffer = 0;
	this->D3DInfo.pIndexBuffer = 0;
	this->D3DInfo.pConstantBuffer = 0;
	this->D3DInfo.pInputLayout = 0;
	this->D3DInfo.pVertexShader = 0;
	this->D3DInfo.pPixelShader = 0;
	this->D3DInfo.pRastersizerState = 0;
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

void BasicDrawable::Update(float delta)
{

}

void BasicDrawable::Draw(const CHL::MapQ<std::string, std::string>& object)
{
	this->SetupDrawConstantBuffer(object);
	this->SetupDrawVertexBuffer(object);
	this->SetupDrawInputVertexShader(object);
	this->SetupDrawPixelShader(object);
	this->SetupDrawRasterizeShader(object);
	this->DrawObject(object);
	this->CleanupAfterDraw(object);
}

void BasicDrawable::SetupDrawConstantBuffer(const CHL::MapQ<std::string, std::string>& object)
{
	boost::numeric::ublas::vector<double> location;	boost::numeric::ublas::vector<double> diffuse;
	boost::numeric::ublas::vector<double> rotation;	boost::numeric::ublas::vector<double> ambient;
	boost::numeric::ublas::vector<double> scale;	boost::numeric::ublas::vector<double> spec;

	this->GetInfo(object, location, rotation, scale, diffuse, ambient, spec);	

	boost::numeric::ublas::matrix<double> mObjectFinal = MathOperations::ObjectCalculation(location, rotation, scale);

	boost::numeric::ublas::matrix<double> mFinal(4,4);
	mFinal = boost::numeric::ublas::prod(GraphicManager::GetInstance().CamerMatrix, mObjectFinal);
	mFinal = boost::numeric::ublas::prod(GraphicManager::GetInstance().PrespectiveMatrix, mFinal);

	XMFLOAT4X4 finalMatrix = XNAToUblas::Convert4x4(mFinal);
	XMFLOAT4X4 worldMatrix = XNAToUblas::Convert4x4(mObjectFinal);

	cBuffer::cbObject cbCEF;
	
	cbCEF.world = XMLoadFloat4x4(&worldMatrix);
	cbCEF.worldViewProj = XMLoadFloat4x4(&finalMatrix);
	cbCEF.colour.diffuse = XNAToUblas::ConvertVec4(diffuse);
	cbCEF.colour.ambient = XNAToUblas::ConvertVec4(ambient);
	cbCEF.colour.spec = XNAToUblas::ConvertVec4(spec);

	ID3D11DeviceContext* pImmediateContext = GraphicManager::GetInstance().direct3d.pImmediateContext;

	pImmediateContext->UpdateSubresource( this->D3DInfo.pConstantBuffer, 0, NULL, &cbCEF, 0, 0 );
	pImmediateContext->VSSetConstantBuffers( 0, 1, &(this->D3DInfo.pConstantBuffer) );
	pImmediateContext->PSSetConstantBuffers( 0, 1, &(this->D3DInfo.pConstantBuffer) );
}
void BasicDrawable::SetupDrawVertexBuffer(const CHL::MapQ<std::string, std::string>& object)
{	
	ID3D11DeviceContext* pImmediateContext = GraphicManager::GetInstance().direct3d.pImmediateContext;

	UINT stride = sizeof( Vertex );
	UINT offset = 0;
	pImmediateContext->IASetVertexBuffers( 0, 1, &this->D3DInfo.pVertexBuffer, &stride, &offset );
	pImmediateContext->IASetIndexBuffer( this->D3DInfo.pIndexBuffer, DXGI_FORMAT_R16_UINT, 0 );
	pImmediateContext->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );	
}
void BasicDrawable::SetupDrawInputVertexShader(const CHL::MapQ<std::string, std::string>& object)
{
	ID3D11DeviceContext* pImmediateContext = GraphicManager::GetInstance().direct3d.pImmediateContext;

	// Set the input layout
	pImmediateContext->IASetInputLayout( this->D3DInfo.pInputLayout );
	pImmediateContext->VSSetShader( this->D3DInfo.pVertexShader, NULL, 0 );
}
void BasicDrawable::SetupDrawPixelShader(const CHL::MapQ<std::string, std::string>& object)
{
	ID3D11DeviceContext* pImmediateContext = GraphicManager::GetInstance().direct3d.pImmediateContext;
	
	pImmediateContext->PSSetShader( this->D3DInfo.pPixelShader, NULL, 0 );	
}
void BasicDrawable::SetupDrawRasterizeShader(const CHL::MapQ<std::string, std::string>& object)
{
	ID3D11DeviceContext* pImmediateContext = GraphicManager::GetInstance().direct3d.pImmediateContext;
	
	pImmediateContext->RSSetState(this->D3DInfo.pRastersizerState);
}
void BasicDrawable::DrawObject(const CHL::MapQ<std::string, std::string>& object)
{
	ID3D11DeviceContext* pImmediateContext = GraphicManager::GetInstance().direct3d.pImmediateContext;

	pImmediateContext->DrawIndexed( this->D3DInfo.indices.size(), 0, 0 );
}
void BasicDrawable::CleanupAfterDraw(const CHL::MapQ<std::string, std::string>& object)	
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
void BasicDrawable::InitRastersizerState(ID3D11Device* device, D3D11_CULL_MODE cullMode, D3D11_FILL_MODE fillMode, bool bAntialiasedLine, bool bMultisampleEnable)
{
	std::wstring error;
	if(!DX11Helper::LoadRasterizerState(cullMode, fillMode, bAntialiasedLine, bMultisampleEnable, device, &(this->D3DInfo.pRastersizerState), error))
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

std::shared_ptr<BasicDrawable> BasicDrawable::Spawn(const std::vector<Vertex>& vectorVertices,
													const std::vector<WORD>&	vectorIndices,
													D3DShaderInfo				vertexFile,
													D3DShaderInfo				pixelFile )
{
	std::shared_ptr<BasicDrawable> newObject(new BasicDrawable);

	newObject->D3DInfo.vertices = vectorVertices;
	newObject->D3DInfo.indices = vectorIndices;
	newObject->D3DInfo.VertexShaderInfo = vertexFile;
	newObject->D3DInfo.PixelShaderInfo = pixelFile;

	newObject->Init();

	return newObject;
}

std::shared_ptr<Drawable> BasicDrawable::clone() const
{
	std::shared_ptr<BasicDrawable> newObject(new BasicDrawable);

	return std::dynamic_pointer_cast<Drawable>(newObject);
}

void BasicDrawable::GetInfo(const CHL::MapQ<std::string, std::string>& object,
							boost::numeric::ublas::vector<double>& location,
							boost::numeric::ublas::vector<double>& rotation,
							boost::numeric::ublas::vector<double>& scale,
							boost::numeric::ublas::vector<double>& diffuse,
							boost::numeric::ublas::vector<double>& ambient,
							boost::numeric::ublas::vector<double>& spec)
{
	location.resize(4);
	if(object.find(Keys::LOCATION) != object.end())
	{
		location = CHL::sstringConverter<boost::numeric::ublas::vector<double>, std::string>(object.find(Keys::LOCATION)->second);
	}
	else
	{
		location(0) = 0.0f; location(1) = 0.0f; location(2) = 0.0f; location(3) = 1.0f; 
	}

	rotation.resize(4);
	if(object.find(Keys::ROTATION) != object.end())
	{
		rotation = CHL::sstringConverter<boost::numeric::ublas::vector<double>, std::string>(object.find(Keys::ROTATION)->second);
	}
	else
	{
		rotation(0) = 0.0f; rotation(1) = 0.0f; rotation(2) = 0.0f; rotation(3) = 0.0f; 
	}

	scale.resize(4);
	if(object.find(Keys::SCALE) != object.end())
	{
		scale = CHL::sstringConverter<boost::numeric::ublas::vector<double>, std::string>(object.find(Keys::SCALE)->second);
	}
	else
	{
		scale(0) = 1.0f; scale(1) = 1.0f; scale(2) = 1.0f; scale(3) = 1.0f; 
	}

	diffuse.resize(4);
	ambient.resize(4);
	spec.resize(4);
	if(object.find(Keys::COLOUR) != object.end())
	{
		diffuse = CHL::sstringConverter<boost::numeric::ublas::vector<double>, std::string>(object.find(Keys::COLOUR)->second);
		ambient = CHL::sstringConverter<boost::numeric::ublas::vector<double>, std::string>(object.find(Keys::COLOUR)->second);
		spec = CHL::sstringConverter<boost::numeric::ublas::vector<double>, std::string>(object.find(Keys::COLOUR)->second);
	}
	else
	{
		diffuse(0) = 1.0f; diffuse(1) = 1.0f; diffuse(2) = 1.0f; diffuse(3) = 1.0f; 
		ambient(0) = 1.0f; ambient(1) = 1.0f; ambient(2) = 1.0f; ambient(3) = 1.0f; 
		spec(0) = 1.0f; spec(1) = 1.0f; spec(2) = 1.0f; spec(3) = 1.0f; 
	}
}