#ifndef __GraphicSettings__
#define __GraphicSettings__

#include "Linker.h"
#include <string>

namespace GraphicSettings
{
	GraphicCommunicatorDLL_API void SetMainCamera(std::string cameraID);
	GraphicCommunicatorDLL_API void ChangeWindowsText(std::string s);
	GraphicCommunicatorDLL_API void MoveWindow(unsigned int x, unsigned int y);
	GraphicCommunicatorDLL_API void ResizeWindow(unsigned int height, unsigned int width);
	GraphicCommunicatorDLL_API void ResizeClient(unsigned int height, unsigned int width);
	GraphicCommunicatorDLL_API void ResizeRender(unsigned int height, unsigned int width);
	GraphicCommunicatorDLL_API void DisableResize();
	GraphicCommunicatorDLL_API void EnableResize();
	GraphicCommunicatorDLL_API void FullScreen();
	GraphicCommunicatorDLL_API void LeaveFullScreen();
	GraphicCommunicatorDLL_API bool IsFullScreen();
	GraphicCommunicatorDLL_API void GetClientSize(unsigned int& height, unsigned int& width);
	GraphicCommunicatorDLL_API void GetWindowSize(unsigned int& height, unsigned int& width);
	GraphicCommunicatorDLL_API void GetRenderSize(unsigned int& height, unsigned int& width);
	GraphicCommunicatorDLL_API void GetWindowsLocation(unsigned int& x, unsigned int& y);
	GraphicCommunicatorDLL_API void GetPosRelativeToClient(int& x, int& y);
	GraphicCommunicatorDLL_API void VSync(bool v);
}

#endif //__GraphicSettings__