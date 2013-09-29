#ifndef __GraphicManager__
#define __GraphicManager__

#include "Linker.h"

#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <d3d11.h>
#include <Singleton.h>
#include <Queryable.h>
#include <Object.h>
#include <Interface.h>
#include "Drawable.h"
#include "Texture.h"

class GraphicManager : public Interface, public CHL::Singelton<GraphicManager>
{
protected:
	GraphicManager();
public:
	virtual void Init();
	virtual void Update(double realTime, double deltaTime);
	virtual void Work();
	virtual void Shutdown();
	
	virtual void SetupCameraNPrespective(const CHL::VectorQ<CHL::MapQ<std::string, std::shared_ptr<Object>>>& objects);
	virtual void SetupConstantBuffer(const CHL::VectorQ<CHL::MapQ<std::string, std::shared_ptr<Object>>>& objects);
	virtual void ClearScreen(const CHL::VectorQ<CHL::MapQ<std::string, std::shared_ptr<Object>>>& objects);
	virtual void DrawObjects(const CHL::VectorQ<CHL::MapQ<std::string, std::shared_ptr<Object>>>& objects);
	virtual void Present(const CHL::VectorQ<CHL::MapQ<std::string, std::shared_ptr<Object>>>& objects);

	void InsertObjectDrawable(std::shared_ptr<Drawable> obj);
	const CHL::MapQ<std::string, std::shared_ptr<Drawable>> AllObjectDrawables();

	void InsertTexture(std::shared_ptr<Texture> obj);
	const CHL::MapQ<std::string, std::shared_ptr<Texture>> AllTexture();

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
	} direct3d;

	
protected:
	CHL::MapQ<std::string, std::shared_ptr<Drawable>> objectDrawables;
	CHL::MapQ<std::string, std::shared_ptr<Texture>> textures;

	virtual void InitDevice();
public:
	boost::numeric::ublas::vector<double> ClearColour;

	boost::numeric::ublas::matrix<double> CamerMatrix;
	boost::numeric::ublas::matrix<double> PrespectiveMatrix;

	friend CHL::Singelton<GraphicManager>;
};

#endif //__GraphicManager__