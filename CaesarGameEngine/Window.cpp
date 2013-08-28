#include <exception>
#include <sstream>
#include <iomanip>

#include "Window.h"
#include "GraphicManager.h"
#include "LuaManager.h"
#include "ObjectManager.h"

void Window::Init()
{
	this->window.hInst = GetModuleHandle(NULL);
	this->window.height = 1024;
	this->window.width = 768; 

	// Register class
    WNDCLASSEX wcex;
    wcex.cbSize = sizeof( WNDCLASSEX );
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = Window::WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
	wcex.hInstance = this->window.hInst;
    wcex.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wcex.hCursor = LoadCursor( NULL, IDC_ARROW );
    wcex.hbrBackground = ( HBRUSH )( COLOR_WINDOW + 1 );
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = L"DirectX11Basic";
    wcex.hIconSm = LoadIcon( wcex.hInstance, ( LPCTSTR )IDI_APPLICATION );
	// Try a "register" this type of window... so that we can create it later
    if( !RegisterClassEx( &wcex ) )
	{
        throw std::exception("Failed at registering Window");
	}

    // Create window
    this->window.hInst = this->window.hInst;
    RECT rc = { 0, 0, this->window.height, this->window.width };
    AdjustWindowRect( &rc, WS_OVERLAPPEDWINDOW, FALSE );
	this->window.hWnd = 0;
    this->window.hWnd = CreateWindow( L"DirectX11Basic", L"Caesar Game Engine", WS_OVERLAPPEDWINDOW,
                           CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, NULL, NULL, this->window.hInst,
                           NULL );

	// Try to create the window...
    if( !(this->window.hWnd) )
	{
        throw std::exception("Failed at creating window");
	}

    ShowWindow( this->window.hWnd, 10 );

	this->vInterfaces.push_back(&GraphicManager::GetInstance());
	this->vInterfaces.push_back(&LuaManager::GetInstance());
	this->vInterfaces.push_back(&ObjectManager::GetInstance());
}

void Window::Run()
{
	SetTimer( this->window.hWnd, FRAMERATE_UPDATE_TIMER, 100, NULL );

	// setup the frame timer
	LARGE_INTEGER timerFrequency = { 0 };
	LARGE_INTEGER timerBase = { 0 };
	LARGE_INTEGER timerLast = { 0 };
	LARGE_INTEGER timerNow = { 0 };
	if( !QueryPerformanceFrequency( &timerFrequency ) ) 
		throw std::exception( "QueryPerformanceFrequency() failed to create a high-performance timer." );
	double tickInterval = static_cast<double>( timerFrequency.QuadPart );

	if( !QueryPerformanceCounter( &timerBase ) )
		throw std::exception( "QueryPerformanceCounter() failed to read the high-performance timer." );
	timerLast = timerBase;
	this->timer.FrameCount = 0;

	// Main message loop
	MSG msg = {0};
	while( WM_QUIT != msg.message )
	{
		if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
		{
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}
		else
		{
			// update timer
			if( !QueryPerformanceCounter( &timerNow ) )
				throw std::exception( "QueryPerformanceCounter() failed to update the high-performance timer." );
			long long elapsedCount = timerNow.QuadPart - timerBase.QuadPart;
			long long elapsedFrameCount = timerNow.QuadPart - timerLast.QuadPart;
			timer.AbsoluteTime = elapsedCount / tickInterval;
			double frameTime = elapsedFrameCount / tickInterval;
			this->timer.SinceLastRun += frameTime;

			double deltaTime = this->timer.SinceLastRun;

			const double MIN_TIMESTEP = 0.001f;
			if ( deltaTime > MIN_TIMESTEP )
			{
				deltaTime = MIN_TIMESTEP;
			}

			for(auto iter = this->vInterfaces.begin();
				iter != this->vInterfaces.end();
				++iter)
			{
				(*iter)->Update(frameTime, deltaTime);
			}
			
			if(this->timer.SinceLastRun > 0.012)
			{
				for(auto iter = this->vInterfaces.begin();
					iter != this->vInterfaces.end();
					++iter)
				{
					(*iter)->Run();
				}

				// render
				this->timer.SinceLastRun = 0.0;
			}

			// update fps
			timerLast = timerNow;
			++(timer.FrameCount);
		}
	}

	KillTimer( this->window.hWnd, FRAMERATE_UPDATE_TIMER );
}

void Window::Shutdown()
{

}

LRESULT CALLBACK Window::WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	switch( message )
	{
	case WM_DESTROY:
		PostQuitMessage( 0 );
		break;
	case WM_TIMER:
		{
			switch( wParam )
			{
				case FRAMERATE_UPDATE_TIMER:
				/* Update the frame rate and its string representation. */
				{
					Window::GetInstance().timer.FrameRate = Window::GetInstance().timer.FrameCount / Window::GetInstance().timer.AbsoluteTime;
					std::wostringstream fr;
					fr << std::setprecision(2) << std::fixed << Window::GetInstance().timer.FrameRate;

					std::wostringstream caption;
					caption << "Framerate: " << fr.str() << " ";

					SetWindowTextW( hWnd, caption.str().c_str() );
					break;
				}
			}
			return 0;
		}

	default:
		return DefWindowProc( hWnd, message, wParam, lParam );
	}

	return 0;
}