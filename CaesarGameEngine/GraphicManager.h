#ifndef __GraphicManager__
#define __GraphicManager__

#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <d3d11.h>

#include <Singleton.h>
#include <Queryable.h>

#include "Interface.h"
#include "Drawable.h"

class GraphicManager : public Interface, public CHL::Singelton<GraphicManager>
{
protected:
	GraphicManager();
public:
	virtual void Init();
	virtual void Update(double realTime, double deltaTime);
	virtual void Work();
	virtual void Shutdown();
	
	virtual void SetupCameraNPrespective();
	virtual void ClearScreen();
	virtual void DrawObjects();
	virtual void Present();

	void Insert(std::shared_ptr<Drawable> obj);
	const CHL::VectorQ<std::shared_ptr<Drawable>> AllObjects();

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

	
protected:
	CHL::VectorQ<std::shared_ptr<Drawable>> objects;

	virtual void InitDevice();
public:
	boost::numeric::ublas::vector<double> ClearColour;

	boost::numeric::ublas::matrix<double> CamerMatrix;
	boost::numeric::ublas::matrix<double> PrespectiveMatrix;

	friend CHL::Singelton<GraphicManager>;
};

#endif //__GraphicManager__