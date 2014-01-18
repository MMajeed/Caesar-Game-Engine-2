#ifndef __GraphicSettings__
#define __GraphicSettings__

#include "Linker.h"
#include <Message.h>
#include <Vector.h>
#include <string>

namespace GraphicSettings
{
	void Resize(unsigned int widthInput, unsigned int heightInput);
	void ChangeWindowsText(std::string s);
	void MoveWindow(unsigned int x, unsigned int y);
	void ResizeWindow(unsigned int height, unsigned int width);
	void ResizeClient(unsigned int height, unsigned int width);
	void DisableResize();
	void EnableResize();
	void FullScreen();
	void LeaveFullScreen();
	bool IsFullScreen();
	void GetWindowsClientSize(unsigned int& height, unsigned int& width);
	void GetWindowsWindowSize(unsigned int& height, unsigned int& width);
	void GetWindowsLocation(unsigned int& x, unsigned int& y);
	void GetPosRelativeToClient(int& x, int& y);
}

#endif //__GraphicSettings__