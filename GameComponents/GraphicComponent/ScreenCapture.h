#ifndef __ScreenCapture__
#define __ScreenCapture__

#include "Linker.h"
#include <string>
#include "TypedefObject.h"
#include <memory>
#include <D3D11.h>

class ScreenCapture
{
public:
	ScreenCapture(const std::string& inputID) : ID(inputID){}

	virtual void Init()                                     = 0;
	virtual void Destory()                                  = 0;
	virtual void Update(double realTime, double deltaTime)  = 0;
	virtual void Snap(TypedefObject::ObjectVector& objects,
					  std::string cameraID = "",
					  std::string prespectiveID = "")		= 0;
	virtual std::shared_ptr<ScreenCapture> clone() const    = 0;
	virtual ~ScreenCapture(){}

	struct
	{
		ID3D11ShaderResourceView*	pColorMapSRV;
		ID3D11RenderTargetView*		pColorMapRTV;
		D3D11_VIEWPORT              Viewport;
		unsigned int				width;
		unsigned int				height;
	} D3DInfo;

	const std::string ID;
};


#endif //__iScreenCapture__
