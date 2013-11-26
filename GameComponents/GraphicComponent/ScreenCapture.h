#ifndef __ScreenCapture__
#define __ScreenCapture__

#include "Linker.h"
#include <string>
#include <INFO.h>
#include <hash_map>
#include <memory>
#include <D3D11.h>

class ScreenCapture
{
public:
	ScreenCapture(const std::string& inputID) : ID(inputID){}

	virtual void Init()                                     = 0;
	virtual void Destory()                                  = 0;
	virtual void Update(double realTime, double deltaTime)  = 0;
	virtual void Snap(std::hash_map<std::string, SP_INFO>& objects)	= 0;
	virtual std::shared_ptr<ScreenCapture> clone() const    = 0;
	virtual ~ScreenCapture(){}

	ID3D11ShaderResourceView* GetScreenTexture()
	{
		this->pScreenTexture->AddRef();
		return this->pScreenTexture;
	}
	ID3D11ShaderResourceView*	pScreenTexture;
	
	const std::string ID;
};


#endif //__iScreenCapture__
