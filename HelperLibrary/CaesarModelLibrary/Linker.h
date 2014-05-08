#ifndef __CaesarModelLibraryGUARD_linklib__
#define __CaesarModelLibraryGUARD_linklib__

	#define CaesarModelLibraryLibFileName "CaesarModelLibrary"  FileBuildType ".lib"

	#if defined(STATIC)
		#pragma comment (lib, CaesarModelLibraryLibFileName)
		#define CaesarModelLibraryDLL_API 
	#elif defined(DLL)	
		#ifdef CaesarModelLibraryDLL_EXPORTS
			#define CaesarModelLibraryDLL_API __declspec(dllexport) 
		#else	
			#pragma comment (lib, CaesarModelLibraryLibFileName)
			#define CaesarModelLibraryDLL_API __declspec(dllimport) 
		#endif	
	#endif
	
#endif