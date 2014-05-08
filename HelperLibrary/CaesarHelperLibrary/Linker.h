#ifndef __CaesarHelperLibraryGUARD_linklib__
#define __CaesarHelperLibraryGUARD_linklib__

	#define CaesarHelperLibraryLibFileName "CaesarHelperLibrary"  FileBuildType ".lib"

	#if defined(STATIC)
		#pragma comment (lib, CaesarHelperLibraryLibFileName)
		#define CaesarHelperLibraryDLL_API 
	#elif defined(DLL)	
		#ifdef CaesarHelperLibraryDLL_EXPORTS
			#define CaesarHelperLibraryDLL_API __declspec(dllexport) 
		#else	
			#pragma comment (lib, CaesarHelperLibraryLibFileName)
			#define CaesarHelperLibraryDLL_API __declspec(dllimport) 
		#endif	
	#endif
	
#endif