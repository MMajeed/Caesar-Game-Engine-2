#ifndef __GraphicManager__
#define __GraphicManager__

#include "Linker.h"

#include "BasicTexture.h"
#include "ScreenShot.h"
#include "ScreenCapture.h"
#include "COMSharedPtr.h"
#include <Vector.h>
#include <d3d11.h>
#include <Singleton.h>
#include <vector>
#include <Object.h>
#include <Interface.h>
#include <Entity.h>
#include <unordered_map>

class GraphicComponentDLL_API GraphicManager : public Interface, public CHL::Singleton<GraphicManager>
{
protected:
	GraphicManager();
	GraphicManager(const GraphicManager& that) = delete;
	GraphicManager& operator=(const GraphicManager&) = delete;
	friend CHL::Singleton<GraphicManager>;
public:
	virtual void Init();
	virtual void Work(double realTime, double deltaTime);
	virtual void Shutdown();
	
	virtual void ProcessDrawing();
	virtual void RunAllCapture(const std::unordered_map<std::string, std::shared_ptr<GraphicObjectEntity>>& list);

	virtual void InitWindow();
	virtual void InitD3D();

protected:
	virtual void InitDevice();
	virtual void InitRenderTarget();
	virtual void InitDepthStencilView();
	virtual void InitDepthStencilStates();
	virtual void InitViewPort();

public:
	virtual void ResizeWindow(unsigned int width, unsigned int height);
	virtual void ResizeClient(unsigned int width, unsigned int height);
	virtual void ResizeRender(unsigned int width, unsigned int height);
	
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	static void MesageBoxError(std::string s);

};

#endif //__GraphicManager__