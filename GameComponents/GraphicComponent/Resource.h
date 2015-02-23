#ifndef __Resource__
#define __Resource__

#include "Linker.h"
#include <unordered_map>
#include <string>
#include "GraphicModel.h"
#include "BasicTexture.h"
#include "ScreenCapture.h"
#include "VertexShader.h"
#include "GeometryShader.h"
#include "PixelShader.h"

namespace Resource
{

	extern GraphicComponentDLL_API std::unordered_map<std::string, std::shared_ptr<GraphicModel>> GraphicModelList;
	extern GraphicComponentDLL_API std::unordered_map<std::string, std::shared_ptr<BasicTexture>> TextureList;
	extern GraphicComponentDLL_API std::unordered_map<std::string, std::shared_ptr<ScreenCapture>> ScreenCaptureList;
	extern GraphicComponentDLL_API std::unordered_map<std::string, std::shared_ptr<VertexShader>> VertexShaderList;
	extern GraphicComponentDLL_API std::unordered_map<std::string, std::shared_ptr<GeometryShader>> GeometryShaderList;
	extern GraphicComponentDLL_API std::unordered_map<std::string, std::shared_ptr<PixelShader>> PixelShaderList;


	// DirectX stuff
	struct D3D
	{
		D3D_DRIVER_TYPE							driverType;
		D3D_FEATURE_LEVEL						featureLevel;
		D3D11_VIEWPORT							vp;
		COMSharedPtr<ID3D11Device>				pd3dDevice;
		COMSharedPtr<ID3D11DeviceContext>		pImmediateContext;
		COMSharedPtr<IDXGISwapChain>			pSwapChain;
		COMSharedPtr<ID3D11RenderTargetView>	pRenderTargetView;
		COMSharedPtr<ID3D11Texture2D>			pDepthStencilBuffer;
		COMSharedPtr<ID3D11DepthStencilState>	pDepthStencilState;
		COMSharedPtr<ID3D11DepthStencilState>	pDepthDisabledStencilState;
		COMSharedPtr<ID3D11DepthStencilView>	pDepthStencilView;
		bool									IsInitialized;
		int										VSync;
	};

	// Windows stuff
	struct Win
	{
		HINSTANCE	hInst;
		HWND		hWnd;
		UINT		width;
		UINT		height;
	};


	extern GraphicComponentDLL_API D3D D3DStuff;

	extern GraphicComponentDLL_API Win window;

	extern GraphicComponentDLL_API std::string DefaultCamera;
	extern GraphicComponentDLL_API std::string DefaultDrawSettings;
};

#endif //__Resource__