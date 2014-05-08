#ifndef __CaesarMathLibraryGUARD_linklib__
#define __CaesarMathLibraryGUARD_linklib__

	#define CaesarMathLibraryLibFileName "CaesarMathLibrary"  FileBuildType ".lib"

	#if defined(STATIC)
		#pragma comment (lib, CaesarMathLibraryLibFileName)
		#define CaesarMathLibraryDLL_API 
	#elif defined(DLL)	
		#ifdef CaesarMathLibraryDLL_EXPORTS
			#define CaesarMathLibraryDLL_API __declspec(dllexport) 
		#else	
			#pragma comment (lib, CaesarMathLibraryLibFileName)
			#define CaesarMathLibraryDLL_API __declspec(dllimport) 
		#endif	
	#endif
	
#endif