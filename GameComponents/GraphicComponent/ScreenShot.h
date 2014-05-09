#ifndef __ScreenShot__
#define __ScreenShot__

#include "Linker.h"
#include <string>
#include <INFO.h>
#include <hash_map>
#include <memory>
#include <D3D11.h>

class GraphicComponentDLL_API ScreenShot
{
protected:
	ScreenShot(){}
public:
	virtual void Init()                                             = 0;
	virtual void Release()                                          = 0;
	virtual void Snap(std::hash_map<std::string, SP_INFO>& objects)	= 0;
	virtual std::shared_ptr<ScreenShot> clone() const            = 0;
	virtual ~ScreenShot(){}

	ID3D11ShaderResourceView* GetScreenTexture()
	{
		this->pScreenTexture->AddRef();
		return this->pScreenTexture;
	}
	ID3D11ShaderResourceView*	pScreenTexture;
};


#endif //__iScreenShot__
