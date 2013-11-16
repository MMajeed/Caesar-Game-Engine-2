#ifndef __BasicScreenCapture__
#define __BasicScreenCapture__

#include "ScreenCapture.h"
#include <Matrix.h>

class BasicScreenCapture : public ScreenCapture
{
public:
	BasicScreenCapture(const std::string& inputID);

	void Init();
	void Destory();
	void Update(double realTime, double deltaTime);
	void Snap(TypedefObject::ObjectVector& objects);

	void SetupScene(TypedefObject::ObjectVector& objects);
	void SetupSnapShot(TypedefObject::ObjectVector& objects);
	void TakeScreenSnapShot(TypedefObject::ObjectVector& objects);
	void CleanupSnapShot(TypedefObject::ObjectVector& objects);

	static std::shared_ptr<BasicScreenCapture> Spawn(std::string id, unsigned int width, unsigned int height);
	std::shared_ptr<ScreenCapture> clone() const;
	
	struct
	{
		ID3D11RenderTargetView*	pColorMapRTV;
		ID3D11DepthStencilView*	pDepthMapDSV;
		D3D11_VIEWPORT          Viewport;
		unsigned int			width;
		unsigned int			height;
		CHL::Matrix4x4			prespectiveMatrix;
		CHL::Matrix4x4			cameraMatrix;
	} D3DInfo;
};


#endif //__iScreenCapture__
