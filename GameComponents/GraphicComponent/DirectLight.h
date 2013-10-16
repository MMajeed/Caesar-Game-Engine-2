#ifndef __DIRECTLIGHT__
#define __DIRECTLIGHT__

#include <Singleton.h>
#include <D3D11.h>
#include <boost/numeric/ublas/matrix.hpp>
#include "TypedefObject.h"
#include "Buffers.h"

class DirectLight : public CHL::Singelton<DirectLight>
{
public:
	DirectLight();
	virtual void GenerateShadowTexture(TypedefObject::ObjectInfo& light,
									   TypedefObject::ObjectVector& objects);
	virtual cBuffer::CLightDesc GetLightDesc(TypedefObject::ObjectInfo& lightInfo);

	virtual boost::numeric::ublas::matrix<double> GetViewMatrix(TypedefObject::ObjectInfo& light);
	virtual boost::numeric::ublas::matrix<double> GetPrespectiveMatrix(TypedefObject::ObjectInfo& light);

	ID3D11ShaderResourceView* mDepthMapSRV;
	ID3D11DepthStencilView* mDepthMapDSV;
	D3D11_VIEWPORT mViewport;

protected:
	virtual void Draw(TypedefObject::ObjectVector& objects);
};

#endif //__DIRECTLIGHT__