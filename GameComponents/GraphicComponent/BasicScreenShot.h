#ifndef __BasicScreenShot__
#define __BasicScreenShot__

#include "ScreenShot.h"
#include <Vector.h>
#include "SceneInfo.h"

class BasicScreenShot : public ScreenShot
{
protected:
	BasicScreenShot();
public:
	void Init();
	void Release();
	void Update(double realTime, double deltaTime);
	void Snap(std::hash_map<std::string, SP_INFO>& objects);

	void SetupSnapShot(std::hash_map<std::string, SP_INFO>& objects, const SceneInfo& si);
	void TakeScreenSnapShot(std::hash_map<std::string, SP_INFO>& objects, const SceneInfo& si);
	void CleanupSnapShot(std::hash_map<std::string, SP_INFO>& objects, const SceneInfo& si);

	static std::shared_ptr<BasicScreenShot> Spawn(unsigned int width, unsigned int height, const std::string& cameraID);
	std::shared_ptr<ScreenShot> clone() const;
	
	struct
	{
		ID3D11RenderTargetView*	pColorMapRTV;
		ID3D11DepthStencilView*	pDepthMapDSV;
		D3D11_VIEWPORT          Viewport;
		unsigned int			width;
		unsigned int			height;
		std::string				cameraID;
	} D3DInfo;
};


#endif //__iScreenShot__
