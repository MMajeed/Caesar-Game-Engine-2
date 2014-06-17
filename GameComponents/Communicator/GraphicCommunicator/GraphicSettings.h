#ifndef __GraphicSettings__
#define __GraphicSettings__

#include "Linker.h"
#include <Message.h>
#include <Vector.h>
#include <string>

namespace GraphicSettings
{
	GraphicCommunicatorDLL_API void SetScreenTexture(std::string textureID);
	GraphicCommunicatorDLL_API void Resize(unsigned int widthInput, unsigned int heightInput);
	GraphicCommunicatorDLL_API void ChangeWindowsText(std::string s);
	GraphicCommunicatorDLL_API void MoveWindow(unsigned int x, unsigned int y);
	GraphicCommunicatorDLL_API void ResizeWindow(unsigned int height, unsigned int width);
	GraphicCommunicatorDLL_API void ResizeClient(unsigned int height, unsigned int width);
	GraphicCommunicatorDLL_API void DisableResize();
	GraphicCommunicatorDLL_API void EnableResize();
	GraphicCommunicatorDLL_API void FullScreen();
	GraphicCommunicatorDLL_API void LeaveFullScreen();
	GraphicCommunicatorDLL_API bool IsFullScreen();
	GraphicCommunicatorDLL_API void GetWindowsClientSize(unsigned int& height, unsigned int& width);
	GraphicCommunicatorDLL_API void GetWindowsWindowSize(unsigned int& height, unsigned int& width);
	GraphicCommunicatorDLL_API void GetWindowsLocation(unsigned int& x, unsigned int& y);
	GraphicCommunicatorDLL_API void GetPosRelativeToClient(int& x, int& y);
}

#endif //__GraphicSettings__