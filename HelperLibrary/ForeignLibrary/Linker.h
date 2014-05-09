#ifndef __ForeignLibraryGUARD_linklib__
#define __ForeignLibraryGUARD_linklib__

	#define ForeignLibraryLibFileName "ForeignLibrary"  FileBuildType ".lib"

	#if defined(STATIC)
		#pragma comment (lib, ForeignLibraryLibFileName)
		#define ForeignLibraryDLL_API 
	#elif defined(DLL)	
		#ifdef ForeignLibraryDLL_EXPORTS
			#define ForeignLibraryDLL_API __declspec(dllexport) 
		#else	
			#pragma comment (lib, ForeignLibraryLibFileName)
			#define ForeignLibraryDLL_API //__declspec(dllimport) 
		#endif	
	#endif
	
#endif