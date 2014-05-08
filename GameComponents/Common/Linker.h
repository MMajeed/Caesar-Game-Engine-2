#ifndef __CommonGUARD_linklib__
#define __CommonGUARD_linklib__

	#define CommonLibFileName "Common"  FileBuildType ".lib"

	#if defined(STATIC)
		#pragma comment (lib, CommonLibFileName)
		#define CommonDLL_API 
	#elif defined(DLL)	
		#ifdef CommonDLL_EXPORTS
			#define CommonDLL_API __declspec(dllexport) 
		#else	
			#pragma comment (lib, CommonLibFileName)
			#define CommonDLL_API __declspec(dllimport) 
		#endif	
	#endif
	
#endif