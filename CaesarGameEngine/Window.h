#ifndef __Window__
#define __Window__

#include <Singleton.h>
#include <Windows.h>
#include <vector>
#include <boost/thread/thread.hpp>
#include <memory>

class Interface;

class Window : public CHL::Singelton<Window>
{
public:
	Window();

	virtual void Init();
	virtual void Run();	
	virtual void Shutdown();

	// Windows stuff
	struct
	{
		HINSTANCE	hInst;
		HWND		hWnd;
		UINT		width;
		UINT		height;
	} window;

	static LRESULT CALLBACK WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam );

protected:
	std::vector<Interface*> vInterfaces;
	std::vector<std::shared_ptr<boost::thread>> vThreads;
	enum { FRAMERATE_UPDATE_TIMER = 1 };
};

#endif //__Window__