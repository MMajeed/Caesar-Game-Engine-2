#ifndef __SPOTLIGHT__
#define __SPOTLIGHT__

#include <Singleton.h>
#include <D3D11.h>
#include <Matrix.h>
#include "TypedefObject.h"
#include "Buffers.h"

class SpotLight : public CHL::Singelton<SpotLight>
{
public:
	SpotLight();
	virtual void GenerateShadowTexture(TypedefObject::ObjectInfo& light,
									   TypedefObject::ObjectVector& objects);
	virtual cBuffer::CLightDesc GetLightDesc(TypedefObject::ObjectInfo& lightInfo);

	virtual CHL::Matrix4x4 GetViewMatrix(TypedefObject::ObjectInfo& light);
	virtual CHL::Matrix4x4 GetPrespectiveMatrix(TypedefObject::ObjectInfo& light);

	ID3D11ShaderResourceView* mDepthMapSRV;
	ID3D11DepthStencilView* mDepthMapDSV;
	D3D11_VIEWPORT mViewport;

protected:
	virtual void Draw(TypedefObject::ObjectVector& objects);
};

#endif //__SPOTLIGHT__