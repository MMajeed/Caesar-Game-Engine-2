#ifndef __Window__
#define __Window__

#include <Singleton.h>
#include <Windows.h>
#include <vector>

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

	// timer stuff
	struct
	{
		double 	  	AbsoluteTime;
		long long	FrameCount;
		double 	  	FrameRate;		
		double 	  	SinceLastRun;
	} timer;

	static LRESULT CALLBACK WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam );

protected:
	std::vector<Interface*> vInterfaces;
	enum { FRAMERATE_UPDATE_TIMER = 1 };
};

#endif //__Window__