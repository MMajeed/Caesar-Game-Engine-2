#ifndef __SPOTLIGHTSHADOW__
#define __SPOTLIGHTSHADOW__

#include "Shadow.h"
#include <Singleton.h>
#include <D3D11.h>
#include <boost/numeric/ublas/matrix.hpp>

class SpotLightShadow : public Shadow, public CHL::Singelton<SpotLightShadow>
{
public:
	virtual void Init();
	virtual void GenerateShadowTexture(TypedefObject::ObjectInfo& light,
									   TypedefObject::ObjectVector& objects);

	virtual boost::numeric::ublas::matrix<double> GetViewMatrix(TypedefObject::ObjectInfo& light);
	virtual boost::numeric::ublas::matrix<double> GetPrespectiveMatrix(TypedefObject::ObjectInfo& light);

	ID3D11ShaderResourceView* mDepthMapSRV;
	ID3D11DepthStencilView* mDepthMapDSV;

	D3D11_VIEWPORT mViewport;
protected:
	virtual void Draw(TypedefObject::ObjectVector& objects);
};

#endif //__SPOTLIGHTSHADOW__