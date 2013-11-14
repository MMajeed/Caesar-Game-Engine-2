#ifndef __DepthScreenCapture__
#define __DepthScreenCapture__

#include "ScreenCapture.h"

class DepthScreenCapture : public ScreenCapture
{
public:
	DepthScreenCapture(const std::string& inputID);

	void Init();
	void Destory();
	void Update(double realTime, double deltaTime);
	void Snap(TypedefObject::ObjectVector& objects, std::string cameraID, std::string prespectiveID);

	void SetupSnapShot(TypedefObject::ObjectVector& objects);
	void TakeSnapShot(TypedefObject::ObjectVector& objects);
	void CleanupSnapShot(TypedefObject::ObjectVector& objects);

	static std::shared_ptr<DepthScreenCapture> Spawn(std::string id, unsigned int width, unsigned int height);
	std::shared_ptr<ScreenCapture> clone() const;

	struct
	{
		ID3D11DepthStencilView*		pDepthMapDSV;
		D3D11_VIEWPORT              Viewport;
		unsigned int				width;
		unsigned int				height;
	} D3DInfo;
};


#endif //__DepthScreenCapture__
