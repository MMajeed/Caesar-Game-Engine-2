#ifndef __BasicScreenShot__
#define __BasicScreenShot__

#include "ScreenShot.h"
#include <Matrix.h>

class BasicScreenShot : public ScreenShot
{
public:
	BasicScreenShot(const std::string& inputID);

	void Init();
	void Release();
	void Update(double realTime, double deltaTime);
	void Snap(std::hash_map<std::string, SP_INFO>& objects);

	void SetupScene(std::hash_map<std::string, SP_INFO>& objects);
	void SetupSnapShot(std::hash_map<std::string, SP_INFO>& objects);
	void TakeScreenSnapShot(std::hash_map<std::string, SP_INFO>& objects);
	void CleanupSnapShot(std::hash_map<std::string, SP_INFO>& objects);

	static std::shared_ptr<BasicScreenShot> Spawn(std::string id, unsigned int width, unsigned int height);
	std::shared_ptr<ScreenShot> clone() const;
	
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


#endif //__iScreenShot__
