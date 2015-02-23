#include "GraphicManager.h"

#include <EntityList.h>
#include "3DMath.h"
#include "XNAConverter.h"
#include "DX11Helper.h"
#include <algorithm>
#include <CameraEntity.h>
#include <ObjectEntity.h>
#include "Scene.h"
#include <Logger.h>
#include <sstream>
#include "Resource.h"

GraphicManager::GraphicManager()
{
	Resource::D3DStuff.IsInitialized = false;
	Resource::D3DStuff.VSync = 0;
}

void GraphicManager::Init()
{
	this->InitWindow();
	this->InitD3D();
}

void GraphicManager::Work(double realTime, double deltaTime)
{
	MSG msg = {0};
	BOOL result = PeekMessage(&msg, Resource::window.hWnd, 0, 0, PM_REMOVE);
	if(result == TRUE)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	
	this->ProcessDrawing();
}

void GraphicManager::Shutdown()
{

}

void GraphicManager::ProcessDrawing()
{
	Scene::UpdateObjectEntities();
	Scene::UpdateDrawSettingsEntities();
	Scene::UpdateCameraEntities();

	const std::unordered_map<std::string, std::shared_ptr<GraphicObjectEntity>>& objects = Scene::GetAllObjectEntities();

	this->RunAllCapture(objects);

	auto camera = Scene::GetCamera(Resource::DefaultCamera, (unsigned int)Resource::D3DStuff.vp.Width, (unsigned int)Resource::D3DStuff.vp.Height);
	auto drawSettings = Scene::GetDrawSettings(Resource::DefaultDrawSettings);
	
	Scene::ClearScreen(camera, drawSettings);
	Scene::DrawObjects(camera, drawSettings, objects);

	// Present the information rendered to the back buffer to the front buffer (the screen)
	Resource::D3DStuff.pSwapChain->Present(Resource::D3DStuff.VSync, 0);
}

void GraphicManager::RunAllCapture(const std::unordered_map<std::string, std::shared_ptr<GraphicObjectEntity>>& list)
{
	const auto& screenCapturesMap = Resource::ScreenCaptureList;
	std::vector<std::shared_ptr<ScreenCapture>> screenCapturesVector;
	for(auto it = screenCapturesMap.begin(); it != screenCapturesMap.end(); ++it) 
	{
		screenCapturesVector.push_back(it->second);
	}

	std::sort(screenCapturesVector.begin(), screenCapturesVector.end(),
			  [](const std::shared_ptr<ScreenCapture>& lhs, const std::shared_ptr<ScreenCapture>& rhs) -> bool
				{
					return lhs->Priority < rhs->Priority;
				});

	for(auto iter = screenCapturesVector.begin();
		iter != screenCapturesVector.end();
		++iter)
	{
		(*iter)->Snap(list);
	}
}

void GraphicManager::InitWindow()
{
	Logger::AddErrorLogger(MesageBoxError);

	Resource::window.hInst = GetModuleHandle(NULL);
	Resource::window.height = 712;
	Resource::window.width = 1080;

	// Register class
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = GraphicManager::WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = Resource::window.hInst;
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = L"DirectX11Basic";
	wcex.hIconSm = LoadIcon(wcex.hInstance, (LPCTSTR)IDI_APPLICATION);
	// Try a "register" this type of window... so that we can create it later
	if(!RegisterClassEx(&wcex))
	{
		Logger::LogError("Failed at registering Window");
	}

	// Create window
	Resource::window.hInst = Resource::window.hInst;
	RECT rc = {0, 0, Resource::window.width, Resource::window.height};
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
	Resource::window.hWnd = 0;
	Resource::window.hWnd = CreateWindow(L"DirectX11Basic", L"Caesar Game Engine", WS_OVERLAPPEDWINDOW,
									 CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, NULL, NULL, Resource::window.hInst,
									 NULL);

	// Try to create the window...
	if(!(Resource::window.hWnd))
	{
		Logger::LogError("Failed at creating window");
	}

	ShowWindow(Resource::window.hWnd, SW_SHOWNORMAL);
}
void GraphicManager::InitD3D()
{
	this->InitDevice();
	this->InitRenderTarget();
	this->InitDepthStencilView();
	this->InitDepthStencilStates();
	this->InitViewPort();

	Resource::D3DStuff.IsInitialized = true;
}

void GraphicManager::InitDevice()
{
	unsigned int& Width = Resource::window.width;
	unsigned int& Height = Resource::window.height;
	HWND& hwnd = Resource::window.hWnd;

	HRESULT hr = S_OK;

	UINT createDeviceFlags = 0;
#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE,
	};
	UINT numDriverTypes = ARRAYSIZE(driverTypes);

	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
	};
	UINT numFeatureLevels = ARRAYSIZE(featureLevels);

	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 1;
	sd.BufferDesc.Width = Width;
	sd.BufferDesc.Height = Height;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = hwnd;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;

	ID3D11Device* pd3dDevice = nullptr;
	ID3D11DeviceContext* pImmediateContext = nullptr;
	IDXGISwapChain* pSwapChain = nullptr;
	for(UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
	{
		Resource::D3DStuff.driverType = driverTypes[driverTypeIndex];
		hr = D3D11CreateDeviceAndSwapChain(NULL, Resource::D3DStuff.driverType, NULL, createDeviceFlags, featureLevels, numFeatureLevels,
										   D3D11_SDK_VERSION, &sd, &pSwapChain, &pd3dDevice, &Resource::D3DStuff.featureLevel, &pImmediateContext);
		if(SUCCEEDED(hr))
			break;
	}
	Resource::D3DStuff.pd3dDevice = pd3dDevice;
	Resource::D3DStuff.pImmediateContext = pImmediateContext;
	Resource::D3DStuff.pSwapChain = pSwapChain;
}
void GraphicManager::InitRenderTarget()
{
	HRESULT hr = S_OK;

	// Create a render target view
	ID3D11Texture2D* pBackBuffer = NULL;
	hr = Resource::D3DStuff.pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	if(FAILED(hr)){ Logger::LogError("Failed at creating back buffer"); }

	ID3D11RenderTargetView*	pRenderTargetView = nullptr;
	hr = Resource::D3DStuff.pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &pRenderTargetView);
	pBackBuffer->Release();
	if(FAILED(hr)){ Logger::LogError("Failed at creating Render Target view"); }
	Resource::D3DStuff.pRenderTargetView = pRenderTargetView;
}
void GraphicManager::InitDepthStencilView()
{
	unsigned int& Width = Resource::window.width;
	unsigned int& Height = Resource::window.height;
	HRESULT hr = S_OK;

	// Set up depth & stencil buffer
	// Initialize the description of the depth buffer.
	D3D11_TEXTURE2D_DESC depthBufferDesc;
	ZeroMemory(&depthBufferDesc, sizeof(depthBufferDesc));

	// Set up the description of the depth buffer.
	depthBufferDesc.Width = Width;
	depthBufferDesc.Height = Height;
	depthBufferDesc.MipLevels = 1;
	depthBufferDesc.ArraySize = 1;
	depthBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthBufferDesc.SampleDesc.Count = 1;
	depthBufferDesc.SampleDesc.Quality = 0;
	depthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthBufferDesc.CPUAccessFlags = 0;
	depthBufferDesc.MiscFlags = 0;

	// Create the texture for the depth buffer using the filled out description.
	ID3D11Texture2D* pDepthStencilBuffer = nullptr;
	hr = Resource::D3DStuff.pd3dDevice->CreateTexture2D(&depthBufferDesc, NULL, &pDepthStencilBuffer);
	if(FAILED(hr)){ Logger::LogError("Failed at creating dept buffer"); }
	Resource::D3DStuff.pDepthStencilBuffer = pDepthStencilBuffer;

	// Initialize the depth stencil view.
	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
	ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));
	// Set up the depth stencil view description.
	depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Texture2D.MipSlice = 0;

	// Create the depth stencil view.
	ID3D11DepthStencilView* pDepthStencilView = nullptr;
	hr = Resource::D3DStuff.pd3dDevice->CreateDepthStencilView(Resource::D3DStuff.pDepthStencilBuffer, &depthStencilViewDesc, &pDepthStencilView);
	if(FAILED(hr)){ Logger::LogError("Failed at creating depth stencil view"); }
	Resource::D3DStuff.pDepthStencilView = pDepthStencilView;

}
void GraphicManager::InitDepthStencilStates()
{	
	HRESULT hr = S_OK;

	// Initialize the description of the stencil state.
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
	ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));
	depthStencilDesc.DepthEnable = true;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;
	depthStencilDesc.StencilEnable = true;
	depthStencilDesc.StencilReadMask = 0xFF;
	depthStencilDesc.StencilWriteMask = 0xFF;
	depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	// Create the depth stencil state.
	ID3D11DepthStencilState* pDepthStencilState = nullptr;
	hr = Resource::D3DStuff.pd3dDevice->CreateDepthStencilState(&depthStencilDesc, &pDepthStencilState);
	if(FAILED(hr)) { Logger::LogError("Failed at creating Dept stencil State"); }
	Resource::D3DStuff.pDepthStencilState = pDepthStencilState;

	// Set up the depth stencil view description.
	D3D11_DEPTH_STENCIL_DESC depthDisabledStencilDesc;
	ZeroMemory(&depthDisabledStencilDesc, sizeof(depthDisabledStencilDesc));
	depthDisabledStencilDesc.DepthEnable = false;
	depthDisabledStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthDisabledStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;
	depthDisabledStencilDesc.StencilEnable = true;
	depthDisabledStencilDesc.StencilReadMask = 0xFF;
	depthDisabledStencilDesc.StencilWriteMask = 0xFF;
	depthDisabledStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthDisabledStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	depthDisabledStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthDisabledStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	depthDisabledStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthDisabledStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	depthDisabledStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthDisabledStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	// Create the depth stencil view.
	ID3D11DepthStencilState* pDepthDisabledStencilState = nullptr;
	hr = Resource::D3DStuff.pd3dDevice->CreateDepthStencilState(&depthDisabledStencilDesc, &pDepthDisabledStencilState);
	if(FAILED(hr)){	Logger::LogError("Failed at creating no depth state");}
	Resource::D3DStuff.pDepthDisabledStencilState = pDepthDisabledStencilState;
}
void GraphicManager::InitViewPort()
{
	unsigned int& Width = Resource::window.width;
	unsigned int& Height = Resource::window.height;

	// Setup the viewport
	Resource::D3DStuff.vp.Width = (FLOAT)Width;
	Resource::D3DStuff.vp.Height = (FLOAT)Height;
	Resource::D3DStuff.vp.MinDepth = 0.0f;
	Resource::D3DStuff.vp.MaxDepth = 1.0f;
	Resource::D3DStuff.vp.TopLeftX = 0;
	Resource::D3DStuff.vp.TopLeftY = 0;
	Resource::D3DStuff.pImmediateContext->RSSetViewports(1, &(Resource::D3DStuff.vp));
}

void GraphicManager::MesageBoxError(std::string s)
{
	std::wstringstream wss;
	wss << "Exception: Something went wrong: " << std::endl
		<< s.c_str();
	std::wstring wStringError = wss.str();

	MessageBox(NULL, wStringError.c_str(), L"Exception", MB_ICONERROR);
}

LRESULT CALLBACK GraphicManager::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	GraphicManager& graphic = GraphicManager::GetInstance();

	switch(message)
	{
		case WM_DESTROY:
			PostQuitMessage(0);
			std::exit(0);
			break;
		case WM_SIZE:
		{
			int width = 0;
			int height = 0;
			RECT rect;
			if(GetClientRect(hWnd, &rect))
			{
				width = rect.right - rect.left;
				height = rect.bottom - rect.top;
			}
			if(width != 0 || height != 0)
			{
				Resource::window.width = width;
				Resource::window.height = height;
			}
			break;
		}
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

void GraphicManager::ResizeWindow(unsigned int width, unsigned int height)
{
	SetWindowPos(Resource::window.hWnd, 0, 0, 0, width, height, SWP_NOMOVE | SWP_NOZORDER);
}
void GraphicManager::ResizeClient(unsigned int width, unsigned int height)
{
	RECT rcClient, rcWind;
	POINT ptDiff;
	GetClientRect(Resource::window.hWnd, &rcClient);
	GetWindowRect(Resource::window.hWnd, &rcWind);
	ptDiff.x = (rcWind.right - rcWind.left) - rcClient.right;
	ptDiff.y = (rcWind.bottom - rcWind.top) - rcClient.bottom;

	SetWindowPos(Resource::window.hWnd, 0, 0, 0, width + ptDiff.x, height + ptDiff.y, SWP_NOMOVE | SWP_NOZORDER);

}
void GraphicManager::ResizeRender(unsigned int width, unsigned int height)
{
	GraphicManager& graphic = GraphicManager::GetInstance();

	if(Resource::D3DStuff.IsInitialized == true)
	{
		Resource::D3DStuff.pRenderTargetView.reset();
		Resource::D3DStuff.pDepthStencilBuffer.reset();
		Resource::D3DStuff.pDepthStencilView.reset();

		if(width == 0){ width = Resource::window.width; }
		if(height == 0){ height = Resource::window.height; }

		// Resize the swap chain and recreate the render target view.
		HRESULT hr = Resource::D3DStuff.pSwapChain->ResizeBuffers(0, 0, 0, DXGI_FORMAT_UNKNOWN, 0);
		if(FAILED(hr)){ Logger::LogError("Failed at resizing swap chain buffer"); }

		ID3D11Texture2D* pBuffer = NULL;
		hr = Resource::D3DStuff.pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pBuffer);
		if(FAILED(hr)){ Logger::LogError("Failed at creating back buffer"); }

		ID3D11RenderTargetView*	pRenderTargetView = nullptr;
		hr = Resource::D3DStuff.pd3dDevice->CreateRenderTargetView(pBuffer, NULL, &pRenderTargetView);
		pBuffer->Release();
		if(FAILED(hr)){ Logger::LogError("Failed at creating Render Target view"); }
		Resource::D3DStuff.pRenderTargetView = pRenderTargetView;

		// Create the depth/stencil buffer and view.
		D3D11_TEXTURE2D_DESC depthBufferDesc;
		ZeroMemory(&depthBufferDesc, sizeof(depthBufferDesc));

		// Set up the description of the depth buffer.
		depthBufferDesc.Width = width;
		depthBufferDesc.Height = height;
		depthBufferDesc.MipLevels = 1;
		depthBufferDesc.ArraySize = 1;
		depthBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		depthBufferDesc.SampleDesc.Count = 1;
		depthBufferDesc.SampleDesc.Quality = 0;
		depthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		depthBufferDesc.CPUAccessFlags = 0;
		depthBufferDesc.MiscFlags = 0;

		ID3D11Texture2D* pDepthStencilBuffer = nullptr;
		// Create the texture for the depth buffer using the filled out description.
		hr = Resource::D3DStuff.pd3dDevice->CreateTexture2D(&depthBufferDesc, NULL, &pDepthStencilBuffer);
		if(FAILED(hr)) { Logger::LogError("Failed at creating dept buffer"); }
		Resource::D3DStuff.pDepthStencilBuffer = pDepthStencilBuffer;

		D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
		// Initialize the depth stencil view.
		ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));

		// Set up the depth stencil view description.
		depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		depthStencilViewDesc.Texture2D.MipSlice = 0;

		ID3D11DepthStencilView* pDepthStencilView = nullptr;
		// Create the depth stencil view.
		hr = Resource::D3DStuff.pd3dDevice->CreateDepthStencilView(Resource::D3DStuff.pDepthStencilBuffer, &depthStencilViewDesc, &pDepthStencilView);
		if(FAILED(hr)) { Logger::LogError("Failed at creating depth stencil view"); }
		Resource::D3DStuff.pDepthStencilView = pDepthStencilView;

		Resource::D3DStuff.pImmediateContext->OMSetRenderTargets(1, &pRenderTargetView, pDepthStencilView);


		// Set the viewport transform.

		// Setup the viewport
		Resource::D3DStuff.vp.Width = (FLOAT)width;
		Resource::D3DStuff.vp.Height = (FLOAT)height;
		Resource::D3DStuff.vp.MinDepth = 0.0f;
		Resource::D3DStuff.vp.MaxDepth = 1.0f;
		Resource::D3DStuff.vp.TopLeftX = 0;
		Resource::D3DStuff.vp.TopLeftY = 0;
		Resource::D3DStuff.pImmediateContext->RSSetViewports(1, &(Resource::D3DStuff.vp));
	}
}
