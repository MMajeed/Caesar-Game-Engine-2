#include <Windows.h>
#include <exception>
#include <sstream>
#include <Converter.h>

#include "Window.h"

int main()
{
	try
	{
		Window::GetInstance().Init();
		Window::GetInstance().Run();
	}
	catch(const std::exception& ex)
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