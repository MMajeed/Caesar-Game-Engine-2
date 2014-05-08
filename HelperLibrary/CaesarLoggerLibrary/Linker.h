#ifndef __CaesarLoggerLibraryGUARD_linklib__
#define __CaesarLoggerLibraryGUARD_linklib__

	#define CaesarLoggerLibraryLibFileName "CaesarLoggerLibrary"  FileBuildType ".lib"

	#if defined(STATIC)
		#pragma comment (lib, CaesarLoggerLibraryLibFileName)
		#define CaesarLoggerLibraryDLL_API 
	#elif defined(DLL)	
		#ifdef CaesarLoggerLibraryDLL_EXPORTS
			#define CaesarLoggerLibraryDLL_API __declspec(dllexport) 
		#else	
			#pragma comment (lib, CaesarLoggerLibraryLibFileName)
			#define CaesarLoggerLibraryDLL_API __declspec(dllimport) 
		#endif	
	#endif
	
#endif