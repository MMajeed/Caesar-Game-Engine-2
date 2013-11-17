#ifndef __GraphicManager__
#define __GraphicManager__

#include "Linker.h"

#include <Vector.h>
#include <Matrix.h>
#include <d3d11.h>
#include <Singleton.h>
#include <vector>
#include <Object.h>
#include <Interface.h>
#include "Drawable.h"
#include "Texture.h"
#include "ScreenCapture.h"
#include "ContinuousScreenShot.h"
#include "TypedefObject.h"

class GraphicManager : public Interface, public CHL::Singelton<GraphicManager>
{
protected:
	GraphicManager();
public:
	virtual void Init();
	virtual void Update(double realTime, double deltaTime);
	virtual void Work();
	virtual void Shutdown();
	
	virtual void RunAllCapture(TypedefObject::ObjectVector& objects);
	virtual void SetupLight(TypedefObject::ObjectVector& objects);
	virtual void SetupScene(TypedefObject::ObjectVector& objects);
	virtual void SetupConstantBuffer(TypedefObject::ObjectVector& objects);
	virtual void ClearScreen(TypedefObject::ObjectVector& objects);
	virtual void DrawObjects(TypedefObject::ObjectVector& objects);
	virtual void Present(TypedefObject::ObjectVector& objects);

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
		ID3D11DepthStencilView*		pDepthStencilView;
		D3D11_VIEWPORT				vp;
		ID3D11Buffer*				pCBInfo;
		ID3D11Buffer*				pCBLight;
		bool						IsInitialized;
	} D3DStuff;


	std::hash_map<std::string, std::shared_ptr<Drawable>> objectDrawables;
	void InsertObjectDrawable(std::shared_ptr<Drawable> obj);
	const std::hash_map<std::string, std::shared_ptr<Drawable>> AllObjectDrawables();

	std::hash_map<std::string, std::shared_ptr<Texture>> textures;
	void InsertTexture(std::shared_ptr<Texture> obj);
	const std::hash_map<std::string, std::shared_ptr<Texture>> AllTexture();

	std::hash_map<std::string, std::shared_ptr<ScreenCapture>> ScreenCaptures;
	void InsertScreenCapture(std::shared_ptr<ScreenCapture> obj);
	const std::hash_map<std::string, std::shared_ptr<ScreenCapture>> AllScreenCapture();
	
	std::hash_map<std::string, std::shared_ptr<ContinuousScreenShot>> ContinuousScreenCaptures;
	void InsertContinuousScreenCapture(std::shared_ptr<ContinuousScreenShot> obj);
	const std::hash_map<std::string, std::shared_ptr<ContinuousScreenShot>> AllContinuousScreenCapture();

	
	virtual void InitDevice();


	struct 
	{
		CHL::Vec4 ClearColour;
		CHL::Vec4 Eye;
		CHL::Matrix4x4 CamerMatrix;
		CHL::Matrix4x4 PrespectiveMatrix;

		std::string CameraKeyID;
		std::string PrespectiveKeyID;
	} SceneInfo;


	friend CHL::Singelton<GraphicManager>;
};

#endif //__GraphicManager__