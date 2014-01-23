#include "CubeScreenShot.h"
#include "GraphicManager.h"
#include <Keys.h>
#include <Object.h>
#include <3DMath.h>
#include "Scene.h"
#include <Logger.h>

CubeScreenShot::CubeScreenShot()
{
	this->D3DInfo.pDepthMapDSV = 0;
	this->D3DInfo.pColorMapRTV[0] = 0;
	this->D3DInfo.pColorMapRTV[1] = 0;
	this->D3DInfo.pColorMapRTV[2] = 0;
	this->D3DInfo.pColorMapRTV[3] = 0;
	this->D3DInfo.pColorMapRTV[4] = 0;
	this->D3DInfo.pColorMapRTV[5] = 0;
	this->pScreenTexture = 0;
}

void CubeScreenShot::Init()
{
	GraphicManager& graphic = GraphicManager::GetInstance();
	auto& d3dStuff = graphic.D3DStuff;

	ID3D11Texture2D* colorMap = 0;

	D3D11_TEXTURE2D_DESC texDesc;
	ZeroMemory(&texDesc, sizeof(texDesc));

	texDesc.Width = this->D3DInfo.width;
	texDesc.Height = this->D3DInfo.height;
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
	if(FAILED(hr))
		Logger::LogError("Failed at creating the texture 2d for the BasicScreenShot");

	// Null description means to create a view to all mipmap levels
	// using the format the texture was created with.
	D3D11_RENDER_TARGET_VIEW_DESC rtvDesc;
	rtvDesc.Format = texDesc.Format;
	rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2DARRAY;
	rtvDesc.Texture2DArray.ArraySize = 1;
	rtvDesc.Texture2DArray.MipSlice = 0;

	for(int i = 0; i < 6; ++i)
	{
		rtvDesc.Texture2DArray.FirstArraySlice = i;
		hr = d3dStuff.pd3dDevice->CreateRenderTargetView(colorMap, &rtvDesc, &this->D3DInfo.pColorMapRTV[i]);

		if(FAILED(hr))
			Logger::LogError("Failed at creating render target view");
	}
	
	// Create a shader resource view to the cube map.
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	srvDesc.Format = texDesc.Format;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURECUBE;
	srvDesc.TextureCube.MostDetailedMip = 0;
	srvDesc.TextureCube.MipLevels = 1;

	hr = d3dStuff.pd3dDevice->CreateShaderResourceView(colorMap, &srvDesc, &(this->pScreenTexture));
	if(FAILED(hr))
		Logger::LogError("Failed at creating shader resource view");

	// View saves a reference to the texture so we can release our reference.
	colorMap->Release();

	ID3D11Texture2D* depthMap = 0;
	ZeroMemory(&texDesc, sizeof(texDesc));

	texDesc.Width = this->D3DInfo.width;
	texDesc.Height = this->D3DInfo.height;
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

	hr = d3dStuff.pd3dDevice->CreateDepthStencilView(depthMap, &dsvDesc, &this->D3DInfo.pDepthMapDSV);
	if(FAILED(hr))
		Logger::LogError("Failed at creating shader resource view");

	this->D3DInfo.Viewport.TopLeftX = 0.0f;
	this->D3DInfo.Viewport.TopLeftY = 0.0f;
	this->D3DInfo.Viewport.Width = (FLOAT)this->D3DInfo.width;
	this->D3DInfo.Viewport.Height = (FLOAT)this->D3DInfo.height;
	this->D3DInfo.Viewport.MinDepth = 0.0f;
	this->D3DInfo.Viewport.MaxDepth = 1.0f;
}
void CubeScreenShot::Release()
{
	if(this->D3DInfo.pDepthMapDSV != 0){ this->D3DInfo.pDepthMapDSV->Release(); }
	if(this->pScreenTexture != 0){ this->pScreenTexture->Release(); }
	for(std::size_t i = 0; i < 6; ++i)
	{
		if(this->D3DInfo.pColorMapRTV[0] != 0){ this->D3DInfo.pColorMapRTV[0]->Release(); }
		this->D3DInfo.pColorMapRTV[0] = 0;
	}
	this->D3DInfo.pDepthMapDSV = 0;
	this->pScreenTexture = 0;
}
void CubeScreenShot::Update(double realTime, double deltaTime)
{

}
void CubeScreenShot::Snap(std::hash_map<std::string, SP_INFO>& objects)
{
	GraphicManager& graphic = GraphicManager::GetInstance();

	std::hash_map<std::string, SP_INFO>::iterator cameraIter = objects.find(this->D3DInfo.cameraID);
	std::shared_ptr<CameraINFO> cameraObj;
	if(cameraIter != objects.cend()) { cameraObj = std::dynamic_pointer_cast<CameraINFO>(cameraIter->second); }

	for(std::size_t i = 0; i < 6; ++i)
	{
		SceneInfo si = this->SetupScene(objects, i, cameraObj);
		this->SetupSnapShot(objects, i, si);
		this->TakeScreenSnapShot(objects, i, si);
	}
	this->CleanupSnapShot(objects);
}

SceneInfo CubeScreenShot::SetupScene(std::hash_map<std::string, SP_INFO>& objects, std::size_t side, const std::shared_ptr<CameraINFO>& cam)
{
	GraphicManager& graphic = GraphicManager::GetInstance();

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

	CHL::Vec4 vEye = cam->Eye;
	CHL::Vec4 vTM;
	CHL::Vec4 vUp;
	double pitch = 0.0;	double yaw = 0.0;	double roll = 0.0;

	// Draw the scene with the exception of the center sphere to this cube map face.
	switch(side)
	{
	case X_POS:		// 0
		vUp = {0.0, 1.0, 0.0, 0.0};
		vTM = {0.01, 0.0, 0.0, 0.0};
		break;
	case X_NEG:		// 1	
		vUp = {0.0, 1.0, 0.0, 0.0};
		vTM = {-0.01, 0.0, 0.0, 0.0};
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

	double FovAngleY = 1.5707963267948966192313216916398;
	double height = this->D3DInfo.height; 
	double width = this->D3DInfo.width;
	double nearZ = cam->NearZ;
	double farZ = cam->FarZ;
	SceneInfo returnValue;
	returnValue.CamerMatrix = CHL::ViewCalculation(vEye, vTM, vUp, pitch, yaw, roll);
	returnValue.Eye = vEye;
	if(FovAngleY > 0.0)
		returnValue.ProjectionMatrix = CHL::PerspectiveFovLHCalculation(FovAngleY, (double)width / (double)height, nearZ, farZ);
	else
		returnValue.ProjectionMatrix = CHL::OrthographicLHCalculation(width, height, nearZ, farZ);

	returnValue.TwoDimMatrix = CHL::OrthographicLHCalculation(width, height, nearZ, farZ);

	Scene::SetupSceneExtraInfo(cam, this->D3DInfo.width, this->D3DInfo.height, returnValue);

	return returnValue;
}
void CubeScreenShot::SetupSnapShot(std::hash_map<std::string, SP_INFO>& objects, std::size_t side, const SceneInfo& si)
{
	GraphicManager& graphic = GraphicManager::GetInstance();
	auto& d3dStuff = graphic.D3DStuff;

	ID3D11RenderTargetView* renderTargets[1] = {this->D3DInfo.pColorMapRTV[side]};
	d3dStuff.pImmediateContext->OMSetRenderTargets(1, renderTargets, this->D3DInfo.pDepthMapDSV);

	d3dStuff.pImmediateContext->RSSetViewports(1, &this->D3DInfo.Viewport);

	float black[4] = {(float)si.ClearColour(0), (float)si.ClearColour(1), (float)si.ClearColour(2), 1.0f};
	d3dStuff.pImmediateContext->ClearRenderTargetView(this->D3DInfo.pColorMapRTV[side], black);
	d3dStuff.pImmediateContext->ClearDepthStencilView(this->D3DInfo.pDepthMapDSV, D3D11_CLEAR_DEPTH, 1.0f, 0);
}
void CubeScreenShot::TakeScreenSnapShot(std::hash_map<std::string, SP_INFO>& objects, std::size_t side, const SceneInfo& si)
{
	GraphicManager& graphic = GraphicManager::GetInstance();

	Scene::SetupConstantBuffer(si);
	Scene::SetupGlobalTexture(si);
	auto vecObj = Scene::FilterScene(objects, si);
	Scene::DrawObjects(vecObj, si);

	graphic.D3DStuff.pImmediateContext->GenerateMips(this->pScreenTexture);
}
void CubeScreenShot::CleanupSnapShot(std::hash_map<std::string, SP_INFO>& objects)
{
	GraphicManager& graphic = GraphicManager::GetInstance();
	auto& d3dStuff = graphic.D3DStuff;

	d3dStuff.pImmediateContext->RSSetViewports(1, &d3dStuff.vp);

	d3dStuff.pImmediateContext->OMSetRenderTargets(1, &(d3dStuff.pRenderTargetView), d3dStuff.pDepthStencilView);
}

std::shared_ptr<CubeScreenShot> CubeScreenShot::Spawn(unsigned int width, unsigned int height, const std::string& cameraID)
{
	std::shared_ptr<CubeScreenShot> newObject(new CubeScreenShot());
	newObject->D3DInfo.cameraID = cameraID;
	newObject->D3DInfo.width = width;
	newObject->D3DInfo.height = height;

	newObject->Init();

	return newObject;
}

std::shared_ptr<ScreenShot> CubeScreenShot::clone() const
{
	std::shared_ptr<CubeScreenShot> newObject(new CubeScreenShot(*this));
	newObject->Init();

	return newObject;
}