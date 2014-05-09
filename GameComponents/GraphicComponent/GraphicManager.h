#ifndef __GraphicManager__
#define __GraphicManager__

#include "Linker.h"

#include <Vector.h>
#include <Vector.h>
#include <d3d11.h>
#include <Singleton.h>
#include <vector>
#include <Object.h>
#include <Interface.h>
#include "Drawable.h"
#include "BasicTexture.h"
#include "ScreenShot.h"
#include "ScreenCapture.h"
#include <INFO.h>
#include <hash_map>

class GraphicComponentDLL_API GraphicManager : public Interface, public CHL::Singleton<GraphicManager>
{
protected:
	GraphicManager();
	GraphicManager(const GraphicManager& that) = delete;
	GraphicManager& operator=(const GraphicManager&) = delete;
	friend CHL::Singleton<GraphicManager>;
public:
	virtual void Init();
	virtual void Work(double realTime, double deltaTime);
	virtual void Shutdown();
	
	virtual void ProcessDrawing();
	virtual void RunAllCapture(std::hash_map<std::string, SP_INFO>& objects);

	virtual void InitWindow();
	virtual void InitDevice();

	// DirectX stuff
	struct
	{
		D3D_DRIVER_TYPE				driverType;
		D3D_FEATURE_LEVEL			featureLevel;
		ID3D11Device*				pd3dDevice;
		ID3D11DeviceContext*		pImmediateContext;
		IDXGISwapChain*				pSwapChain;
		ID3D11RenderTargetView*		pRenderTargetView;
		ID3D11Texture2D*			pDepthStencilBuffer;
		ID3D11DepthStencilState*	pDepthStencilState;
		ID3D11DepthStencilState*	pDepthDisabledStencilState;
		ID3D11DepthStencilView*		pDepthStencilView;
		D3D11_VIEWPORT				vp;
		ID3D11Buffer*				pCBObject;
		ID3D11Buffer*				pCBInfo;
		ID3D11Buffer*				pCBLight;
		ID3D11Buffer*				pCBShadow;
		ID3D11BlendState*			pTransperency;
		bool						IsInitialized;
	} D3DStuff;

	// Windows stuff
	struct
	{
		HINSTANCE	hInst;
		HWND		hWnd;
		UINT		width;
		UINT		height;
	} window;

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	static void MesageBoxError(std::string s);

	std::hash_map<std::string, std::shared_ptr<Drawable>> objectDrawables;
	void InsertObjectDrawable(const std::string& ID, std::shared_ptr<Drawable> obj);
	void RemoveObjectDrawable(const std::string& ID);
	const std::hash_map<std::string, std::shared_ptr<Drawable>> AllObjectDrawables();
	
	std::hash_map<std::string, std::shared_ptr<BasicTexture>> textures;
	void InsertTexture(const std::string& ID, std::shared_ptr<BasicTexture> obj);
	void RemoveTexture(const std::string& ID);
	const std::hash_map<std::string, std::shared_ptr<BasicTexture>> AllTexture();

	std::hash_map<std::string, std::shared_ptr<ScreenCapture>> ScreenCaptures;
	void InsertScreenCapture(const std::string& ID, std::shared_ptr<ScreenCapture> obj);
	void RemoveScreenCapture(const std::string& ID);
	const std::hash_map<std::string, std::shared_ptr<ScreenCapture>> AllScreenCapture();
};

#endif //__GraphicManager__