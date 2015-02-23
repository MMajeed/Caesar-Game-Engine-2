#ifndef __GraphicSettingsFactory__
#define __GraphicSettingsFactory__

#include "Linker.h"
#include <iGraphicSettingsFactory.h>

class GraphicComponentDLL_API GraphicSettingsFactory : public iGraphicSettingsFactory
{
public:
	virtual void SetMainCamera(std::string cameraID);
	virtual void SetMainDrawSettings(std::string drawSettingsID);
	virtual void ChangeWindowsText(std::string s);
	virtual void MoveWindow(unsigned int x, unsigned int y);
	virtual void ResizeWindow(unsigned int height, unsigned int width);
	virtual void ResizeClient(unsigned int height, unsigned int width);
	virtual void ResizeRender(unsigned int height, unsigned int width);
	virtual void DisableResize();
	virtual void EnableResize();
	virtual void FullScreen();
	virtual void LeaveFullScreen();
	virtual bool IsFullScreen();
	virtual void GetClientSize(unsigned int& height, unsigned int& width);
	virtual void GetWindowSize(unsigned int& height, unsigned int& width);
	virtual void GetRenderSize(unsigned int& height, unsigned int& width);
	virtual void GetWindowsLocation(unsigned int& x, unsigned int& y);
	virtual void GetPosRelativeToClient(int& x, int& y);
	virtual void VSync(bool v);
};

#endif //__GraphicSettingsFactory__