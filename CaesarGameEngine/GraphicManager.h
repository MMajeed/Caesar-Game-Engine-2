#ifndef __GraphicManager__
#define __GraphicManager__

#include <boost/numeric/ublas/vector.hpp>
#include <d3d11.h>

#include <Singleton.h>
#include <MapQueryable.h>

#include "Interface.h"

class GraphicManager : public Interface, public CHL::Singelton<GraphicManager>
{
public:
	GraphicManager();

	virtual void Init();
	virtual void Update(double realTime, double deltaTime);
	virtual void Work();
	virtual void Shutdown();
	
	virtual void SetupSampler();
	virtual void ClearScreen();
	virtual void DrawObjects();
	virtual void Present();

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
		D3D11_VIEWPORT vp;
	} direct3d;

	boost::numeric::ublas::vector<double> ClearColour;

protected:
	virtual void InitDevice();
};

#endif //__GraphicManager__