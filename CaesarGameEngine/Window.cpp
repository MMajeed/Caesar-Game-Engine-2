#include <exception>
#include <sstream>
#include <iomanip>
#include <memory>
#include <chrono>
#include "Window.h"
#include <InputCommunicator\InputCommunicator.h>
#include <GraphicCommunicator\GraphicCommunicator.h>
#include <ScriptCommunicator\ScriptCommunicator.h>
#include <InfoCommunicator\InfoCommunicator.h>
#include <InputCommunicator\UpdateKey.h>
#include <InfoCommunicator\AddObjectMessage.h>
#include <Keys.h>
#include <Converter.h>
#include <Error.h>

Window::Window()
{
}

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

	this->vInterfaces["Graphic"] = GraphicCommunicator::GetComponent();
	this->vInterfaces["Lua"] = ScriptCommunicator::GetComponent();
	this->vInterfaces["Info Manager"] = InfoCommunicator::GetComponent();
	this->vInterfaces["Input Manager"] = InputCommunicator::GetComponent();

	CHL::MapQ<std::string, std::shared_ptr<Object>> camera;

	camera[Keys::Class] =  GenericObject<std::string>::CreateNew(Keys::ClassType::WindowInfo);
	camera[Keys::HEIGHT] =  GenericObject<int>::CreateNew(this->window.height);
	camera[Keys::WIDTH] =  GenericObject<int>::CreateNew(this->window.width);
	camera[Keys::HWND] =  GenericObject<HWND>::CreateNew(this->window.hWnd);

	std::shared_ptr<AddObjectMessage> msg(new AddObjectMessage(camera));

	InfoCommunicator::SubmitMessage(msg);	
	InfoCommunicator::GetComponent()->ProccessMessages();

	msg->WaitTillProcccesed();

	for(auto iter = this->vInterfaces.begin();
		iter != this->vInterfaces.end();
		++iter)
	{
		iter->second->Init();
	}
}

void Window::Run()
{
	SetTimer( this->window.hWnd, FRAMERATE_UPDATE_TIMER, 100, NULL );
	
	for(auto iter = this->vInterfaces.begin();
		iter != this->vInterfaces.end();
		++iter)
	{
		std::shared_ptr<std::thread> thread
			= std::shared_ptr<std::thread>(new std::thread(std::bind(&Interface::Run, iter->second)));
		
		this->vThreads.push_back(thread);
	}


	
	LARGE_INTEGER timerBase = { 0 };
	LARGE_INTEGER timerNow = { 0 };
	LARGE_INTEGER timerFrequency = { 0 };
	if( !QueryPerformanceCounter( &timerBase ) )
			throw std::exception( "QueryPerformanceCounter() failed to read the high-performance timer." );
	if( !QueryPerformanceFrequency( &timerFrequency ) ) 
			throw std::exception( "QueryPerformanceFrequency() failed to create a high-performance timer." );
		double tickInterval = static_cast<double>( timerFrequency.QuadPart );

	// Main message loop
	MSG msg = {0};
	while( WM_QUIT != msg.message )
	{
		if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
		{
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}		
		
		
		if( !QueryPerformanceCounter( &timerNow ) )
			throw std::exception( "QueryPerformanceCounter() failed to update the high-performance timer." );
		long long elapsedCount = timerNow.QuadPart - timerBase.QuadPart;
		this->window.AbsoluteTime = elapsedCount / tickInterval;

		
		std::this_thread::sleep_for(std::chrono::milliseconds((int)(15)));

		Error::GetInstance().Check();
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
	case WM_KEYDOWN:
	{
		std::shared_ptr<UpdateKey> keyMessage(new UpdateKey( (unsigned int)wParam, true));
		InputCommunicator::SubmitMessage(keyMessage);
		break;
	}
	case WM_KEYUP:
	{
		std::shared_ptr<UpdateKey> keyMessage(new UpdateKey( (unsigned int)wParam, false));
		InputCommunicator::SubmitMessage(keyMessage);
		break;
	}
	case WM_TIMER:
	{
		switch( wParam )
		{
			/* Update the frame rate and its string representation. */
			case FRAMERATE_UPDATE_TIMER:
			{
				std::wostringstream fr;
				fr << std::setprecision(2) << std::fixed ;
				for(auto interFaceIter = Window::GetInstance().vInterfaces.begin();
					interFaceIter != Window::GetInstance().vInterfaces.end();
					++interFaceIter)
				{
					double frameTimer = interFaceIter->second->timer.FrameCount / Window::GetInstance().window.AbsoluteTime;
						
					fr << interFaceIter->first.c_str() << " : ";
					fr << frameTimer << ". ";
				}
					
				SetWindowTextW( hWnd, fr.str().c_str() );

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