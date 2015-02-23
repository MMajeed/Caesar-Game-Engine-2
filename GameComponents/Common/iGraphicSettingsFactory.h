#ifndef __iGraphicSettingsFactory__
#define __iGraphicSettingsFactory__

#include "Linker.h"
#include <Model.h>
#include <memory>
#include <string>

class CommonDLL_API iGraphicSettingsFactory
{
public:
	virtual void SetMainCamera(std::string cameraID) = 0;
	virtual void SetMainDrawSettings(std::string drawSettingsID) = 0;
	virtual void ChangeWindowsText(std::string s) = 0;
	virtual void MoveWindow(unsigned int x, unsigned int y) = 0;
	virtual void ResizeWindow(unsigned int height, unsigned int width) = 0;
	virtual void ResizeClient(unsigned int height, unsigned int width) = 0;
	virtual void ResizeRender(unsigned int height, unsigned int width) = 0;
	virtual void DisableResize() = 0;
	virtual void EnableResize() = 0;
	virtual void FullScreen() = 0;
	virtual void LeaveFullScreen() = 0;
	virtual bool IsFullScreen() = 0;
	virtual void GetClientSize(unsigned int& height, unsigned int& width) = 0;
	virtual void GetWindowSize(unsigned int& height, unsigned int& width) = 0;
	virtual void GetRenderSize(unsigned int& height, unsigned int& width) = 0;
	virtual void GetWindowsLocation(unsigned int& x, unsigned int& y) = 0;
	virtual void GetPosRelativeToClient(int& x, int& y) = 0;
	virtual void VSync(bool v) = 0;
};

#endif //__iGraphicSettingsFactory__