#include "CubeScreenShot.h"

#include "GraphicManager.h"
#include "Scene.h"
#include <EntityList.h>
#include <Object.h>
#include <Logger.h>

CubeScreenShot::CubeScreenShot()
{
}

void CubeScreenShot::Init()
{
	GraphicManager& graphic = GraphicManager::GetInstance();
	auto& d3dStuff = graphic.D3DStuff;

	ID3D11Texture2D* colorMap = 0;

	D3D11_TEXTURE2D_DESC texDesc;
	ZeroMemory(&texDesc, sizeof(texDesc));

	texDesc.Width = this->width;
	texDesc.Height = this->height;
	texDesc.MipLevels = 0;
	texDesc.ArraySize = 6;
	texDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	texDesc.SampleDesc.Count = 1;
	texDesc.SampleDesc.Quality = 0;
	texDesc.Usage = D3D11_USAGE_DEFAULT;
	texDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	texDesc.CPUAccessFlags = 0;
	texDesc.MiscFlags = D3D11_RESOURCE_MISC_GENERATE_MIPS | D3D11_RESOURCE_MISC_TEXTURECUBE;

	HRESULT hr;
	hr = d3dStuff.pd3dDevice->CreateTexture2D(&texDesc, 0, &colorMap);
	if(FAILED(hr)){ Logger::LogError("Failed at creating the texture 2d for the BasicScreenShot"); }

	// Null description means to create a view to all mipmap levels
	// using the format the texture was created with.
	D3D11_RENDER_TARGET_VIEW_DESC rtvDesc;
	rtvDesc.Format = texDesc.Format;
	rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2DARRAY;
	rtvDesc.Texture2DArray.ArraySize = 1;
	rtvDesc.Texture2DArray.MipSlice = 0;

	for(int i = 0; i < 6; ++i)
	{
		ID3D11RenderTargetView* pTempColorMapRTV;
		rtvDesc.Texture2DArray.FirstArraySlice = i;
		hr = d3dStuff.pd3dDevice->CreateRenderTargetView(colorMap, &rtvDesc, &pTempColorMapRTV);

		if(FAILED(hr)){ Logger::LogError("Failed at creating render target view"); }
		this->pColorMapRTV[i] = pTempColorMapRTV;
	}
	
	// Create a shader resource view to the cube map.
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	srvDesc.Format = texDesc.Format;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURECUBE;
	srvDesc.TextureCube.MostDetailedMip = 0;
	srvDesc.TextureCube.MipLevels = 1;

	ID3D11ShaderResourceView* pTempScreenTexture;
	hr = d3dStuff.pd3dDevice->CreateShaderResourceView(colorMap, &srvDesc, &pTempScreenTexture);
	if(FAILED(hr)){ Logger::LogError("Failed at creating shader resource view"); }
	this->pScreenTexture = pTempScreenTexture;

	// View saves a reference to the texture so we can release our reference.
	colorMap->Release();

	ID3D11Texture2D* depthMap = 0;
	ZeroMemory(&texDesc, sizeof(texDesc));

	texDesc.Width = this->width;
	texDesc.Height = this->height;
	texDesc.MipLevels = 1;
	texDesc.ArraySize = 1;
	texDesc.Format = DXGI_FORMAT_R32_TYPELESS;
	texDesc.SampleDesc.Count = 1;
	texDesc.SampleDesc.Quality = 0;
	texDesc.Usage = D3D11_USAGE_DEFAULT;
	texDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;

	texDesc.CPUAccessFlags = 0;
	texDesc.MiscFlags = 0;

	hr = d3dStuff.pd3dDevice->CreateTexture2D(&texDesc, 0, &depthMap);
	if(FAILED(hr))
		Logger::LogError("Failed at creating shader resource view");

	D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc;

	ZeroMemory(&dsvDesc, sizeof(dsvDesc));
	dsvDesc.Format = DXGI_FORMAT_D32_FLOAT;
	dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	dsvDesc.Texture2D.MipSlice = 0;

	ID3D11DepthStencilView* pTempDepthMapDSV;
	hr = d3dStuff.pd3dDevice->CreateDepthStencilView(depthMap, &dsvDesc, &pTempDepthMapDSV);
	if(FAILED(hr)){ Logger::LogError("Failed at creating shader resource view"); }
	this->pDepthMapDSV = pTempDepthMapDSV;

	this->Viewport.TopLeftX = 0.0f;
	this->Viewport.TopLeftY = 0.0f;
	this->Viewport.Width = (FLOAT)this->width;
	this->Viewport.Height = (FLOAT)this->height;
	this->Viewport.MinDepth = 0.0f;
	this->Viewport.MaxDepth = 1.0f;
}
void CubeScreenShot::Snap()
{
	const std::hash_map<std::string, std::shared_ptr<GraphicObjectEntity>>& objects = Scene::GetAllObjectEntities();
	this->Snap(objects);
}
void CubeScreenShot::Snap(const std::hash_map<std::string, std::shared_ptr<GraphicObjectEntity>>& list)
{
	GraphicManager& graphic = GraphicManager::GetInstance();

	std::weak_ptr<CameraEntity> wpCE;
	CameraEntities::Find(this->cameraID, wpCE);
	
	std::shared_ptr<CameraEntity> spCE = wpCE.lock();
	if(spCE){ spCE->Clone(); } // Clone a new one so that we can edit it
	else{ spCE = CameraEntity::Spawn(); } // didn't find one, so making one

	for(std::size_t i = 0; i < 6; ++i)
	{
		GraphicCameraEntity si = this->SetupScene(i, spCE);
		this->SetupSnapShot(i, si, list);
		this->TakeScreenSnapShot(i, si, list);
		this->CleanupSnapShot(i, si, list);
	}
}

GraphicCameraEntity CubeScreenShot::SetupScene(std::size_t side, std::shared_ptr<CameraEntity>& cam)
{
	// This call needs to be called six times, for each direction of the camera.
	// You set the back buffer to be the particular direction in the cube map
	// (note that each direction is pre-defined: 
	//	0 ==> +X	//	1 ==> -X
	//	2 ==> +Y	//	3 ==> -Y
	//	4 ==> +Z	//	5 ==> -Y
	static enum enumCamDirection
	{
		X_POS = 0,
		X_NEG,	// = 1
		Y_POS,	// = 2
		Y_NEG,	// = 3
		Z_POS,	// = 4
		Z_NEG	// = 5 
	};

	CML::Vec4 vTM;
	CML::Vec4 vUp;
	double pitch = 0.0;	double yaw = 0.0;	double roll = 0.0;
	double fovAngle = 0.0;
	// Draw the scene with the exception of the center sphere to this cube map face.
	switch(side)
	{
		case X_POS:		// 0
			vUp = {0.0, 1.0, 0.0, 0.0};
			vTM = {1.0, 0.0, 0.0, 0.0};
			break;
		case X_NEG:		// 1	
			vUp = {0.0, 1.0, 0.0, 0.0};
			vTM = {-1.0, 0.0, 0.0, 0.0};
			break;
		case Y_POS:		// 2
			vUp = {0.0, 0.0, 1.0, 0.0};
			vTM = {0.0, 0.01, 0.0, 0.0};
			yaw = 3.14f;
			break;
		case Y_NEG:		// 3
			vUp = {0.0, 0.0, 1.0, 0.0};
			vTM = {0.0, -0.01, 0.0, 0.0};
			break;
		case Z_POS:		// 4
			vUp = {0.0, 1.0, 0.0, 0.0};
			vTM = {0.0, 0.0, 0.01, 0.0};
			break;
		case Z_NEG:		// 5
			vUp = {0.0, 1.0, 0.0, 0.0};
			vTM = {0.0, 0.0, -0.01, 0.0};
			break;
	}
	cam->SetTargetMagnitude(vTM);
	cam->SetUp(vUp);
	cam->SetPitch(pitch);
	cam->SetYaw(yaw);
	cam->SetRoll(roll);
	cam->SetFovAngleY(1.5707963267948966192313216916398);
	
	return GraphicCameraEntity(cam, this->width, this->height);
}
void CubeScreenShot::SetupSnapShot(std::size_t side, const GraphicCameraEntity& Camera, const std::hash_map<std::string, std::shared_ptr<GraphicObjectEntity>>& list)
{
	GraphicManager& graphic = GraphicManager::GetInstance();
	auto& d3dStuff = graphic.D3DStuff;

	auto c = Camera.GetClearColor();
	d3dStuff.pImmediateContext->ClearRenderTargetView(this->pColorMapRTV[side], c.data());
	d3dStuff.pImmediateContext->ClearDepthStencilView(this->pDepthMapDSV, D3D11_CLEAR_DEPTH, 1.0f, 0);

	ID3D11RenderTargetView* renderTargets[1] = {this->pColorMapRTV[side]};
	d3dStuff.pImmediateContext->OMSetRenderTargets(1, renderTargets, this->pDepthMapDSV);
	d3dStuff.pImmediateContext->RSSetViewports(1, &this->Viewport);
}
void CubeScreenShot::TakeScreenSnapShot(std::size_t side, const GraphicCameraEntity& Camera, const std::hash_map<std::string, std::shared_ptr<GraphicObjectEntity>>& list)
{
	GraphicManager& graphic = GraphicManager::GetInstance();

	Scene::DrawObjects(Camera, list);
}
void CubeScreenShot::CleanupSnapShot(std::size_t side, const GraphicCameraEntity& Camera, const std::hash_map<std::string, std::shared_ptr<GraphicObjectEntity>>& list)
{
	GraphicManager& graphic = GraphicManager::GetInstance();
	auto& d3dStuff = graphic.D3DStuff;

	d3dStuff.pImmediateContext->GenerateMips(this->pScreenTexture);
}

std::shared_ptr<CubeScreenShot> CubeScreenShot::Spawn(unsigned int width, unsigned int height, const std::string& cameraID)
{
	std::shared_ptr<CubeScreenShot> newObject(new CubeScreenShot());
	newObject->cameraID = cameraID;
	newObject->width = width;
	newObject->height = height;

	newObject->Init();

	return newObject;
}

std::shared_ptr<ScreenShot> CubeScreenShot::clone() const
{
	std::shared_ptr<CubeScreenShot> newObject(new CubeScreenShot(*this));
	newObject->Init();

	return newObject;
}