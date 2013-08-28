#include <Windows.h>
#include <exception>
#include <sstream>
#include <Converter.h>

#include "Window.h"


int WINAPI wWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow )
{
	UNREFERENCED_PARAMETER(hInstance);
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	UNREFERENCED_PARAMETER(nCmdShow);
	
	try
	{
		Window::GetInstance().Init();
		Window::GetInstance().Run();
	}
	catch(std::exception ex)
	{
		std::wstringstream wss;
		wss << "Exception: Something went wrong" << std::endl
			<< ex.what();

		OutputDebugStringA( CHL::ToString(wss.str()).c_str() );
		MessageBox( NULL, wss.str().c_str(), L"Exception", MB_ICONERROR );
		return EXIT_FAILURE;
	}
	catch( ... )
	{
		OutputDebugStringA( "Something went wrong" );
		MessageBoxA( NULL, "An unknown exception has been caught" , "Exception", MB_ICONERROR );
		return EXIT_FAILURE;
	}

	return 1;
}