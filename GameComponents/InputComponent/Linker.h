#ifndef __InputComponentGUARD_linklib__
#define __InputComponentGUARD_linklib__

	#define InputComponentLibFileName "InputComponent"  FileBuildType ".lib"

	#if defined(STATIC)
		#pragma comment (lib, InputComponentLibFileName)
		#define InputComponentDLL_API 
	#elif defined(DLL)	
		#ifdef InputComponentDLL_EXPORTS
			#define InputComponentDLL_API __declspec(dllexport) 
		#else	
			#pragma comment (lib, InputComponentLibFileName)
			#define InputComponentDLL_API __declspec(dllimport) 
		#endif	
	#endif
	
#endif