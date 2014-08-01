//#ifndef __DepthScreenShot__
//#define __DepthScreenShot__
//
//#include "ScreenShot.h"
//#include <Vector.h>
//#include "SceneInfo.h"
//
//class GraphicComponentDLL_API DepthScreenShot : public ScreenShot
//{
//protected:
//	DepthScreenShot();
//public:
//	void Init();
//	void Release();
//	void Update(double realTime, double deltaTime);
//	void Snap(std::hash_map<std::string, SP_INFO>& objects);
//
//	void SetupSnapShot(std::hash_map<std::string, SP_INFO>& objects, const SceneInfo& si);
//	void TakeScreenSnapShot(std::hash_map<std::string, SP_INFO>& objects, const SceneInfo& si);
//	void CleanupSnapShot(std::hash_map<std::string, SP_INFO>& objects, const SceneInfo& si);
//
//	static std::shared_ptr<DepthScreenShot> Spawn(unsigned int width, unsigned int height, const std::string& cameraID);
//	std::shared_ptr<ScreenShot> clone() const;
//
//	struct
//	{
//		ID3D11DepthStencilView*	pDepthMapDSV;
//		D3D11_VIEWPORT          Viewport;
//		unsigned int			width;
//		unsigned int			height;
//		std::string				cameraID;
//	} D3DInfo;
//};
//
//
//#endif //__DepthScreenShot__
